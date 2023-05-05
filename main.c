/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:08:46 by jdefayes          #+#    #+#             */
/*   Updated: 2023/05/05 23:49:30 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	perror_msg2(char *msg);
void init(t_pipe *d, int ac, char **av, char **env);

int	main(int ac, char **av, char **envp)
{
	t_pipe	d;
	//int wait_status;
	init(&d, ac, av, envp);
	if (ac <= 4)
	{
		ft_putstr_fd("pipex: Arguement missing\n", 2);
		return (1);
	}
	control_files(d.infile, d.outfile);
	handle_pipes(&d.fd_pipe1, &d.fd_pipe2);
	while (d.i < ac - 3)
	{
		if (d.i % 2 == 0)
			child_process_0_2(d, av[d.j], d.first_arg);
		else
			child_process_1_2(d, av[d.j], d.last_arg);
		d.j++;
		d.i++;
	}
	//waitpid(-1, &wait_status, 0);
	while(d.i-- > 0 )
		wait(NULL);
	putzfrau(d);
	fd_opened();
	return (0);
}

void	handle_pipes(int (*fd1)[2], int (*fd2)[2])
{
	if(pipe(*fd1) == -1 || pipe(*fd2) == -1)
		perror_msg();
}

void	perror_msg(void)
{
	perror("pipexc");
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
	d->infile = av[1];
	d->outfile = av[ac - 1];
}
