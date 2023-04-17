/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:47:08 by jdefayes          #+#    #+#             */
/*   Updated: 2023/04/17 22:59:24 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void child_process_1(t_pipe data, char *cmd1)
{
	(void)cmd1;
	int pidcurrent = getpid();
	int pidp = getppid();
	printf("child 1: current: %d, parent: %d\n", pidcurrent, pidp);

	data.fd_in = open("test.txt", O_RDONLY);		// av[1] = "infile"

	// redirection de stdin et stdout
	dup2(data.fd_in, STDIN_FILENO);				// infile, dirige sur stdin
	dup2(data.fd_pipe[1], STDOUT_FILENO);		// entre du tube, dirige sur stdout
	close(data.fd_pipe[0]);
	close(data.fd_in);

	//execve(cmd1);
	exit(0);
}

void child_process_2(t_pipe data, char *cmd2, int ac, char **av)
{
	(void)cmd2;
	int pidcurrent = getpid();
	int pidp = getppid();
	printf("child 2.2: current: %d, parent: %d\n", pidcurrent, pidp);
	data.fd_out = open (av[ac - 1], O_CREAT | O_WRONLY, 0664);	// av[ac - 1] == "outfile"
	dup2(data.fd_out, STDOUT_FILENO);	// outfile, dirige sur stdout
	dup2(data.fd_pipe[0], STDIN_FILENO);		// sortie du tube, dirige sur stdin
	close(data.fd_pipe[1]);
	close(data.fd_out);
	//execve(cmd2);
	exit(0);
}
