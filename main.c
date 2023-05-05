/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:08:46 by jdefayes          #+#    #+#             */
/*   Updated: 2023/05/05 22:19:31 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	perror_msg2(char *msg);
void init(t_pipe *d, int ac, char **av, char **env);

int	main(int ac, char **av, char **envp)
{
	t_pipe	d;

	init(&d, ac, av, envp);
	if (ac <= 4)
	{
		ft_putstr_fd("pipex: Arguement missing\n", 2);
		return (1);
	}
	control_files(av[1], av[ac - 1]);
	handle_pipes(&d.fd_pipe1, &d.fd_pipe2);
	while (d.i < ac - 3)
	{
		if (d.i % 2 == 0)
			child_process_0_2(d, av[d.j], d.first_arg, av[1]);
		else
			child_process_1_2(d, av[d.j], d.last_arg);
		d.j++;
		d.i++;
	}
	while(d.i-- > 0 )
		wait(NULL);
	putzfrau(d);
	return (0);
}

void	handle_pipes(int (*fd1)[2], int (*fd2)[2])
{
	if(pipe(*fd1) == -1 || pipe(*fd2) == -1)
		perror_msg();
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

void	perror_msg(void)
{
	perror("pipex");
	exit(EXIT_FAILURE);
}

void init(t_pipe *d, int ac, char **av, char **env)
{
	d->i = 0;
	d->j = 2;
	d->envp = env;
	d->path = get_path(d->envp);
	d->access = ft_split(d->path, ':', 1);
	d->pid_main = getpid();
	d->last_arg = av[ac - 2];
	d->first_arg = av[2];
	d->outfile = av[ac - 1];
}
