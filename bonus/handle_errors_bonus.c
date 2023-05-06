/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 13:00:28 by jdefayes          #+#    #+#             */
/*   Updated: 2023/05/06 23:31:15 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_dup_err(int fd_f, int fd_p, char **tab_cmd, int position)
{
	free_double_tab(tab_cmd);
	if (position == 0)
	{
		close(fd_f);
		close(fd_p);
	}
	if (position == 1)
	{
		close(fd_p);
	}
	perror("pipex");
	exit(EXIT_FAILURE);
}

void	handle_dup_err_middle(int fd_p, char **tab_cmd, char *path_cmd)
{
	free(path_cmd);
	free_double_tab(tab_cmd);
	close(fd_p);
	perror("pipex");
	exit(EXIT_FAILURE);
}

void	handle_exec_err(int fd_p, char **tab_cmd, char *path_cmd)
{
	free(path_cmd);
	free_double_tab(tab_cmd);
	close(fd_p);
	perror("pipex");
	exit(EXIT_FAILURE);
}

void	command_not_found(char *cmd)
{
	char	*msg_err;
	char	*tmp;

	tmp = ft_strjoin("pipex: command not found: ", cmd);
	msg_err = ft_strjoin(tmp, "\n");
	ft_putstr_fd(msg_err, 2);
	free(tmp);
	free(msg_err);
}

void	error_msg(char *file_name)
{
	char	*msg_sys;
	char	*msg_err;
	char	*tmp;

	msg_sys = strerror(errno);
	tmp = ft_strjoin("pipex: ", msg_sys);
	msg_err = ft_strjoin(tmp, ": ");
	free(tmp);
	tmp = NULL;
	tmp = ft_strjoin(msg_err, file_name);
	free(msg_err);
	ft_putstr_fd(tmp, 2);
	ft_putstr_fd("\n", 2);
	free(tmp);
}
