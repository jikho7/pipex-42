/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:47:08 by jdefayes          #+#    #+#             */
/*   Updated: 2023/04/18 22:17:59 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void child_process_1(t_pipe data)
{
	data.pidcurrent1 = getpid();
	int pidp = getppid();
	char *cmd1_path;
	int i = 0;

	printf("child 1: current: %d, parent: %d\n", data.pidcurrent1, pidp);
	data.fd_in = open("test.txt", O_RDONLY);		// av[1] = "infile"
	dup2(data.fd_in, STDIN_FILENO);				// infile, dirige sur stdin
	dup2(data.fd_pipe[1], STDOUT_FILENO);		// entre du tube, dirige sur stdout
	close(data.fd_pipe[0]);
	close(data.fd_in);
	printf("plop\n");
	while(data.access[i])
	{
		//cmd = ft_join(mypaths[i], ag[2])
		cmd1_path = ft_strjoin(data.access[i], data.cmd1);
		access(cmd1_path, F_OK);
		printf("%s\n", cmd1_path); // protect your ft_join
		execve(data.cmd1, data.cmd_arg1, data.envp);
    	//execve(cmd, mycmdargs, envp);
		//printf("result EXC;%d\n",execve(cmd1_path, data.cmd_arg1, data.envp));
		i++;
	}
}

void child_process_2(t_pipe data, int ac, char **av)
{
	waitpid(data.pidcurrent1, 0, 0);
	data.pidcurrent2 = getpid();
	int pidp = getppid();
	char *cmd2_path;
	int i = 0;
	printf("child 2: current: %d, parent: %d\n", data.pidcurrent2, pidp);

	data.fd_out = open (av[ac - 1], O_CREAT | O_WRONLY, 0664);	// av[ac - 1] == "outfile"

	dup2(data.fd_out, STDOUT_FILENO);	// outfile, dirige sur stdout
	dup2(data.fd_pipe[0], STDIN_FILENO);		// sortie du tube, dirige sur stdin
	close(data.fd_pipe[1]);
	close(data.fd_out);
		while(data.access[i])
	{
		cmd2_path = ft_strjoin(data.access[i], data.cmd2);
		access(cmd2_path, F_OK);
		printf("%s\n", cmd2_path); // protect your ft_join
    	execve(data.cmd2, data.cmd_arg2, data.envp);
		i++;
	}
	//execve(data.path, );
}
