/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 13:06:55 by jdefayes          #+#    #+#             */
/*   Updated: 2023/05/06 13:12:09 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, t_pipe d)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (d.access[i])
	{
		cmd_path = ft_strjoin(d.access[i], cmd);
		if (access (cmd_path, F_OK) == 0)
			return (cmd_path);
		else
		i++;
	}
	return (NULL);
}

int is_cmd_valid(char *cmd_path, t_pipe d, int process)
{
	if (access(cmd_path, F_OK) == -1)
	{
		if (process == 0)
		{
			command_not_found(*d.cmd_arg);
			free_double_tab(d.cmd_arg);
			close(d.fd_pipe2[1]);
		}
		if (process == 1)
		{
			command_not_found(*d.cmd_arg);
			free_double_tab(d.cmd_arg);
			close(d.fd_pipe2[0]);
		}
		return(1);
	}
	return (0);
}

int	control_files(char *infile, char *outfile)
{
	int in;
	int out;

	in = open(infile, F_OK);
	out = open(outfile, F_OK);
	if (open(infile, O_RDONLY, 0644) == -1)
	{
		close(in);
		error_msg(infile);
		exit(EXIT_FAILURE);
	}
	if (open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644) == -1)
	{
		close(out);
		error_msg(outfile);
		exit(EXIT_FAILURE);
	}
	close(in);
	close(out);
	return(0);
}

void close_pipes(t_pipe d, int process)
{
	if (process == 1)
	{
		close(d.fd_pipe1[1]);
		close(d.fd_pipe2[0]);
	}
	if (process == 2)
	{
		close(d.fd_pipe1[0]);
		close(d.fd_pipe2[1]);
	}
	if (process == 3)
	{
		close(d.fd_pipe1[0]);
		close(d.fd_pipe1[1]);
	}
	if (process == 4)
	{
		close(d.fd_pipe2[0]);
		close(d.fd_pipe2[1]);
	}
}
