/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:08:46 by jdefayes          #+#    #+#             */
/*   Updated: 2023/04/18 22:39:36 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av, char **envp)
{
	int pid2;
	int pid1;
	//int i = 0;
	t_pipe data;
	//char *cmd1_path = NULL;
	data.envp = envp;
	data.cmd_arg1 = ft_split(av[2], ' ');
	data.cmd_arg2 = ft_split(av[3], ' ');
	data.cmd1 = av[2];
	data.cmd2 = av[3];
	//printf("CMD1%s\n", data.cmd1);
	//printf("CMD2%s\n", data.cmd2);
	data.path = get_path(envp);
	//printf("path->%s\n", data.path);
	data.access = ft_split(data.path, ':');
	// while(data.access[i])
	// {
	// 	cmd1_path = ft_strjoin(data.access[i], data.cmd1);
	// 	printf("CMD_PATH%s\n", cmd1_path);
	//  	//printf("%s\n", data.access[i]);
	//  	i++;
	// }
	int pidcurrent = getpid();
	printf("parent: current: %d\n", pidcurrent);

	if(pipe(data.fd_pipe) == -1)
		return (0); 	// (perror("Pipe: "));
	pid1 = fork();
	if(pid1 == -1)
		return(0);		// (perror("Fork: "));
	if (pid1 == 0)
	{
		child_process_1(data);
	}
	else
	{
		// enfant 2, cmd 2
		pid2 = fork();
		if(pid2 == -1)
			return(0);		// (perror("Fork: "));
		if (pid2 == 0)
		{
			child_process_2(data, ac, &av[0]);
		}
		// parent
		waitpid(data.pidcurrent1, 0 , 0);
		waitpid(data.pidcurrent2, 0 , 0);
		return (0);
	}

}

