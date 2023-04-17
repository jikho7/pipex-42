/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:08:46 by jdefayes          #+#    #+#             */
/*   Updated: 2023/04/17 23:00:21 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av, char **envp)
{
	(void)envp;
	int status;
	int pid2;
	int pid1;
	t_pipe data;

	if(pipe(data.fd_pipe) == -1)
		return (0); 	// (perror("Pipe: "));
	pid1 = fork();
	if(pid1 == -1)
		return(0);		// (perror("Fork: "));
	if (pid1 == 0)
	{
		child_process_1(data, "ls");
	}
	else
	{
		// enfant 2, cmd 2
		int pidcurrent = getpid();
		int pidp = getppid();
		printf("child 2: current: %d, parent: %d\n", pidcurrent, pidp);
		pid2 = fork();
		if(pid2 == -1)
			return(0);		// (perror("Fork: "));
		if (pid2 == 0)
		{
			child_process_2(data, "ls", ac, &av[0]);
		}
				// parent
		waitpid(-1, &status , 0);
		waitpid(-1, &status , 0);
		return (0);
	}

}

