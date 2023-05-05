/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:47:08 by jdefayes          #+#    #+#             */
/*   Updated: 2023/05/05 21:11:53 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process_0_2(t_pipe d, char *cmd, char *first_arg, char *infile)
{
	char	*cmd_path;
	int		fork_pid;
	int		fork_ppid;
	int		i;
	int		size;

	i = 0;
	size = 0;
	fork_pid = fork();
	fork_ppid = getppid();
	cmd_path = NULL;
	if (fork_pid < 0)
		perror_msg("pipex fork: ");
	if (fork_pid == 0 && fork_ppid == d.pid_main)
	{
		d.cmd_arg0 = ft_split(cmd, ' ', 0);
		cmd_path = get_cmd_path(d.cmd_arg0[0], d);
		is_cmd_valid(cmd_path, d, 0);
		if (cmd == first_arg)
		{
			d.fd_in = open(infile, O_RDONLY);
			if (d.fd_in < 0)
			{
				close(d.fd_in);
				error_msg(infile);
				exit(EXIT_FAILURE);
				//error("pipex: No such file or directory\n");
			}
			if(dup2(d.fd_in, STDIN_FILENO) == -1 || dup2(d.fd_pipe2[1], STDOUT_FILENO) == -1)
			 	handle_dup_err(d.fd_in, d.fd_pipe2[1], d.cmd_arg0, cmd_path);
			close_pipes(d, 0);
			close(d.fd_in);
			//close(d.fd_pipe2[1]); // test
		}
		else if (cmd == d.last_arg)
		{
			d.fd_out = open (d.outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (d.fd_out < 0)
			{
				close(d.fd_out);
				error_msg(d.outfile);
				exit(EXIT_FAILURE);
				//error("pipex: No such file or directory\n");
			}
			dup2(d.fd_pipe1[0], STDIN_FILENO);
			dup2(d.fd_out, STDOUT_FILENO);
			close_pipes(d, 0);
			// test
			close(d.fd_out);
			//close(d.fd_pipe2[1]); // test

		}
		else
		{
			dup2(d.fd_pipe1[0], STDIN_FILENO);
			dup2(d.fd_pipe2[1], STDOUT_FILENO);
			close_pipes(d, 0);
		}
		execve(cmd_path, d.cmd_arg0, d.envp);
		// test close(d.fd_pipe2[1]);
		perror_msg("pipex execve: ");
	}
	close(d.fd_pipe1[0]);
	close(d.fd_pipe1[1]);
	pipe(d.fd_pipe1);
}

void	child_process_1_2(t_pipe d, char *cmd, char *last_arg)
{
	char	*cmd_path;
	int		fork_pid = fork();
	int		fork_ppid = getppid();
	int		size;
	int		i;

	i = 0;
	size = 0;
	cmd_path = NULL;
	if (fork_pid < 0)
		perror_msg("pipex fork: ");
	if (fork_pid == 0 && fork_ppid == d.pid_main)
	{
		d.cmd_arg1 = ft_split(cmd, ' ', 0);
		cmd_path = get_cmd_path(d.cmd_arg1[0], d);
		is_cmd_valid(cmd_path, d, 1);
		dup2(d.fd_pipe2[0], STDIN_FILENO);
		if (cmd == last_arg)
		{
			d.fd_out = open (d.outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (d.fd_out < 0)
			{
				close(d.fd_out);
				error_msg(d.outfile);
				exit(EXIT_FAILURE);
				//error("pipex: No such file or directory\n");
			}
			dup2(d.fd_out, STDOUT_FILENO);
			close_pipes(d, 1);
			close(d.fd_out);
		}
		else
		{
			dup2(d.fd_pipe1[1], STDOUT_FILENO);
			close_pipes(d, 1);
		}
		execve(cmd_path, d.cmd_arg1, d.envp);
		perror_msg("pipex execve: ");
		exit (2);
	}
	close(d.fd_pipe2[0]);
	close(d.fd_pipe2[1]);
	pipe(d.fd_pipe2);
}

char	*get_cmd_path(char *cmd, t_pipe d)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (d.access[i])
	{
		cmd_path = ft_strjoin(d.access[i], cmd);
		if (access (cmd_path, F_OK) == 0)
			return (cmd_path);
		else
		i++;
	}
	return (NULL);
}

int is_cmd_valid(char *cmd_path, t_pipe d, int process)
{
	int i;


	i = 0;
	if (access(cmd_path, F_OK) == -1)
	{
		if (process == 0)
		{
			// while (d.cmd_arg0[i])
			// 	i++;
			command_not_found(*d.cmd_arg0);
			free_double_tab(d.cmd_arg0, i);
			close(d.fd_pipe2[1]);
		}
		if (process == 1)
		{
			// while (d.cmd_arg1[i])
			// 	i++;
			command_not_found(*d.cmd_arg1);
			free_double_tab(d.cmd_arg1, i);
			close(d.fd_pipe2[0]);
		}
		return(1);
	}
	return (0);
}

void	command_not_found(char *cmd)
{
	char	*msg_err;
	char	*tmp;

	tmp = ft_strjoin("pipex: command not found: ", cmd);
	msg_err = ft_strjoin(tmp, "\n");
	ft_putstr_fd(msg_err, 2);
	free(tmp);
	free(msg_err);
}

void	error_msg(char *file_name)
{
	char	*msg_sys;
	char	*msg_err;
	char	*tmp;

	msg_sys = strerror(errno);
	tmp = ft_strjoin("pipex: ", msg_sys);
	msg_err = ft_strjoin(tmp, ": ");
	free(tmp);
	tmp = NULL;
	tmp = ft_strjoin(msg_err, file_name);
	free(msg_err);
	ft_putstr_fd(tmp, 2);
	ft_putstr_fd("\n", 2);
	free(tmp);
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
}

void	free_double_tab(char **tab, int size)
{
	int	i;
	int sizee;
	(void)size;

	i = 0;
	while(tab[i])
	{
		i++;
	}
	sizee = i;
	i = 0;
	while (i < sizee)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void close_pipes(t_pipe d, int process)
{
	if (process == 0)
	{
		close(d.fd_pipe1[1]);
		close(d.fd_pipe1[0]);
		close(d.fd_pipe2[0]);
	}
	if (process == 1)
	{
		close(d.fd_pipe1[0]);
		close(d.fd_pipe2[1]);
		close(d.fd_pipe1[1]);
		close(d.fd_pipe2[0]);
	}
}

//handle_dup_err(d.fd_in, d.fd_pipe2[1], d.cmd_arg0, cmd_path);
void	handle_dup_err(int fd_f, int fd_p, char **tab_cmd, char *path_cmd)
{
	free(path_cmd);
	free_double_tab(tab_cmd, 1);
	close(fd_f);
	close(fd_p);
	perror("pipex");
	exit(EXIT_FAILURE);
}

void	handle_exec_err(int fd_p, char **tab_cmd, char *path_cmd)
{
	free(path_cmd);
	free_double_tab(tab_cmd, 1);
	close(fd_p);
	perror("pipex");
	exit(EXIT_FAILURE);
}
