/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_leaks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 13:08:41 by jdefayes          #+#    #+#             */
/*   Updated: 2023/05/06 18:12:34 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_double_tab(char **tab)
{
	int	i;
	int size;

	i = 0;
	while(tab[i] != NULL)
		i++;
	size = i;
	i = 0;
	while (i <= size)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	putzfrau(t_pipe *d)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	close(d->fd_in);
	close(d->fd_out);
	while (d->access[size])
		size++;
	while (i < size)
		free(d->access[i++]);
	free(d->access);
}
