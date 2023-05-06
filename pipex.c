/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:47:08 by jdefayes          #+#    #+#             */
/*   Updated: 2023/05/06 16:04:11 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process_0_2(t_pipe d, char *cmd, char *first_cmd)
{
	char	*cmd_path;
	int		fork_pid;


	fork_pid = fork();
	cmd_path = NULL;
	if (fork_pid == -1)
		perror_msg();
	if (fork_pid == 0)
	{
		close_pipes(d, 1);
		d.cmd_arg0 = ft_split(cmd, ' ', 0);
	//	fprintf(stderr, "cmd_arg0 ptr: %p\n", d.cmd_arg0);
		cmd_path = get_cmd_path(d.cmd_arg0[0], d);
	//	fprintf(stderr, "cmd_path0 ptr: %p\n", cmd_path);
		is_cmd_valid(cmd_path, d, 0);
		if (cmd == first_cmd)
			ft_first_cmd(d, cmd_path);
		else if (cmd == d.last_cmd)
			ft_last_cmd(d, cmd_path, 0);
		else
			middle_cmd(d, cmd_path, 0);
		if(execve(cmd_path, d.cmd_arg0, d.envp) == -1)
			handle_exec_err(d.fd_pipe2[1], d.cmd_arg0, cmd_path);
	}
	close_pipes(d, 3);
	pipe(d.fd_pipe1);
}

void	child_process_1_2(t_pipe d, char *cmd, char *last_cmd)
{
	char	*cmd_path;
	int		fork_pid = fork();

	cmd_path = NULL;
	if (fork_pid == -1)
		perror_msg();
	if (fork_pid == 0)
	{
		close_pipes(d, 2);
		d.cmd_arg1 = ft_split(cmd, ' ', 0);
		cmd_path = get_cmd_path(d.cmd_arg1[0], d);
	//	fprintf(stderr, "cmd_arg1 ptr: %p\n", d.cmd_arg1);
	//	fprintf(stderr, "cmd_path1 ptr: %p\n", cmd_path);
		is_cmd_valid(cmd_path, d, 1);
		if(dup2(d.fd_pipe2[0], STDIN_FILENO) == -1)
			handle_dup_err(0, d.fd_pipe2[0], d.cmd_arg1, cmd_path, 1);
		if (cmd == last_cmd)
			ft_last_cmd(d, cmd_path, 1);
		else
			middle_cmd(d, cmd_path, 1);
		if(execve(cmd_path, d.cmd_arg1, d.envp) == -1)
			handle_exec_err(d.fd_pipe1[1], d.cmd_arg1, cmd_path);
	}
	close_pipes(d, 4);
	pipe(d.fd_pipe2);
}

void ft_first_cmd(t_pipe d, char *cmd_path)
{
	d.fd_in = open(d.infile, O_RDONLY);
	if (d.fd_in < 0)
	{
		close(d.fd_in);
		error_msg(d.infile);
		exit(EXIT_FAILURE);
	}
	if(dup2(d.fd_in, STDIN_FILENO) == -1 || dup2(d.fd_pipe2[1], STDOUT_FILENO) == -1)
	 	handle_dup_err(d.fd_in, d.fd_pipe2[1], d.cmd_arg0, cmd_path, 0);
	close_pipes(d, 2);
	close(d.fd_in);
}

void ft_last_cmd(t_pipe d, char *cmd_path, int process)
{
	d.fd_out = open (d.outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (d.fd_out < 0)
	{
		close(d.fd_out);
		error_msg(d.outfile);
		exit(EXIT_FAILURE);
	}
	if (process == 0)
	{
		if(dup2(d.fd_pipe1[0], STDIN_FILENO) == 1 || dup2(d.fd_out, STDOUT_FILENO) == - 1)
			handle_dup_err(d.fd_out, d.fd_pipe1[0], d.cmd_arg0, cmd_path, 0);
		close_pipes(d, 2);
	}
	if (process == 1)
	{
		if(dup2(d.fd_out, STDOUT_FILENO) == -1)
			handle_dup_err(d.fd_out, d.fd_pipe2[0], d.cmd_arg1, cmd_path, 0);
		close_pipes(d, 1);
	}
	// test
	close(d.fd_out);
	//close(d.fd_pipe2[1]); // test
}

void middle_cmd(t_pipe d, char *cmd_path, int process)
{
	if (process == 0)
	{
		if (dup2(d.fd_pipe1[0], STDIN_FILENO) == -1)
			handle_dup_err(0, d.fd_pipe1[0], d.cmd_arg0, cmd_path, 1);
		if (dup2(d.fd_pipe2[1], STDOUT_FILENO) == -1)
			handle_dup_err(1, d.fd_pipe2[1], d.cmd_arg0, cmd_path, 1);
		close_pipes(d, 2);
	}
	if (process == 1)
	{
		if(dup2(d.fd_pipe1[1], STDOUT_FILENO) == -1)
			handle_dup_err(1, d.fd_pipe1[1], d.cmd_arg1, cmd_path, 1);
		close_pipes(d, 1);
	}
}
