/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:08:46 by jdefayes          #+#    #+#             */
/*   Updated: 2023/05/05 18:25:10 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	perror_msg2(char *msg);

int	main(int ac, char **av, char **envp)
{
	int		i;
	int		j;
	t_pipe	d;

	i = 0;
	j = 2;
	d.envp = envp;
	d.path = get_path(d.envp);
	d.access = ft_split(d.path, ':', 1);
	d.pid_main = getpid();
	d.last_arg = av[ac - 2];
	d.first_arg = av[2];
	d.outfile = av[ac - 1];
	if (ac <= 4)
	{
		ft_putstr_fd("pipex: Arguement missing\n", 2);
		return (1);
	}
	if (ac > 4)
	{
		control_files(av[1], av[ac - 1]);
		handle_pipes(&d.fd_pipe1, &d.fd_pipe2);
		while (i < ac - 3)
		{
			if (i % 2 == 0)
				child_process_0_2(d, av[j], d.first_arg, av[1]);
			else
				child_process_1_2(d, av[j], d.last_arg);
			i++;
			j++;
		}
		while(i > 0 )
		{
			wait(NULL);
			i--;
		}
		putzfrau(d);
	}
}

void	handle_pipes(int (*fd1)[2], int (*fd2)[2])
{
	int	res1;
	int	res2;

	res1 = pipe((*fd1));
	res2 = pipe((*fd2));
	if (res1 == -1)
		perror_msg2("Pipex pipe: ");
	if (res2 == -1)
		perror_msg2("Pipex pipe: ");
}

int	error(char *msg)
{
	//char *msg_sys;
	int size;

	//msg_sys = strerror(errno);
	size = ft_strlen(msg);
	write(2, msg, size);
	exit(1);
}

void	perror_msg(char *msg)
{
	perror(msg);
	//exit(EXIT_FAILURE);
}

void	perror_msg2(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
