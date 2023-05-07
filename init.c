/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 13:03:36 by jdefayes          #+#    #+#             */
/*   Updated: 2023/05/07 11:57:55 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_struc_pipe(t_pipe *d, int ac, char **av, char **env)
{
	d->i = 0;
	d->j = 2;
	d->envp = env;
	d->path = get_path(d->envp);
	d->last_arg = av[ac - 2];
	d->first_arg = av[2];
	d->infile = av[1];
	d->outfile = av[ac - 1];
}

void	handle_pipes(int (*fd1)[2], int (*fd2)[2])
{
	if (pipe(*fd1) == -1 || pipe(*fd2) == -1)
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
