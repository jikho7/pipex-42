/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 13:03:36 by jdefayes          #+#    #+#             */
/*   Updated: 2023/05/06 15:43:37 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void init(t_pipe *d, int ac, char **av, char **env)
{
	d->i = 0;
	d->j = 2;
	d->envp = env;
	fprintf(stderr, "envp ptr: %p\n", d->envp);
	d->path = get_path(d->envp);
	fprintf(stderr, "path ptr: %p\n", d->path);
	d->access = ft_split(d->path, ':', 1);
	fprintf(stderr, "access ptr: %p\n", d->access);
	d->pid_main = getpid();
	d->last_cmd = av[ac - 2];
	fprintf(stderr, "last_cmd ptr: %p\n", d->last_cmd);
	d->first_cmd = av[2];
	fprintf(stderr, "first_cmd ptr: %p\n", d->first_cmd);
	d->infile = av[1];
	fprintf(stderr, "infile ptr: %p\n", d->infile);
	d->outfile = av[ac - 1];
	fprintf(stderr, "outfile ptr: %p\n", d->outfile);
}

void	handle_pipes(int (*fd1)[2], int (*fd2)[2])
{
	if(pipe(*fd1) == -1 || pipe(*fd2) == -1)
		perror_msg();
}

void	perror_msg(void)
{
	perror("pipex");
	exit(EXIT_FAILURE);
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
}


