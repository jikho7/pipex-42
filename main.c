/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:08:46 by jdefayes          #+#    #+#             */
/*   Updated: 2023/05/06 15:59:32 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipe	d;
	int		status;

	init(&d, ac, av, envp);
	if (ac <= 4)
	{
		ft_putstr_fd("pipex : Arguement missing\n", 2);
		return (1);
	}
	control_files(d.infile, d.outfile);
	handle_pipes(&d.fd_pipe1, &d.fd_pipe2);
	while (d.i < ac - 3)
	{
		if (d.i % 2 == 0)
			child_process_0_2(d, av[d.j], d.first_cmd);
		else
			child_process_1_2(d, av[d.j], d.last_cmd);
		d.j++;
		d.i++;
	}
	while (d.i-- > 0)
		wait(&status);
	putzfrau(d);
	//fd_opened();
	return (0);
}

