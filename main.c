/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:08:46 by jdefayes          #+#    #+#             */
/*   Updated: 2023/05/06 18:16:02 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_t_pipe(t_pipe *d);

void	ft_free_t_pipe(t_pipe *d)
{
	if (d->access)
		free_double_tab(d->access);
	if (d->cmd_arg == NULL)
		free(d->cmd_arg);
	if(d->envp)
		free_double_tab(d->envp);
	if(d->path)
		free(d->path);
	if(d->last_arg)
		free(d->last_arg);
	if(d->first_arg)
		free(d->first_arg);
	if(d->infile)
		free(d->infile);
	if(d->outfile)
		free(d->outfile);
	if(d->cmd_arg)
		free_double_tab(d->cmd_arg);
	if(d->cmd_arg0)
		free_double_tab(d->cmd_arg0);
	if(d->cmd_arg1)
		free_double_tab(d->cmd_arg1);
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	d;

	d = (t_pipe) {0};
	//ft_free_t_pipe(&d);
	init_struc_pipe(&d, ac, av, envp);
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
			child_process_0_2(&d, av[d.j], d.first_arg);
		else
			child_process_1_2(&d, av[d.j], d.last_arg);
		d.j++;
		d.i++;
	}
	while(d.i-- > 0 )
		wait(NULL);
	//putzfrau(&d);
	ft_free_t_pipe(&d);
	fd_opened();
	return (0);
}

