/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:08:51 by jdefayes          #+#    #+#             */
/*   Updated: 2023/04/17 22:56:53 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
#include <fcntl.h>

typedef struct s_pipe
{
	int		fd_pipe[2];
	int		fd_in;
	int		fd_out;
	int		status;
}t_pipe;

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(const char *str, char c);
void child_process_1(t_pipe data, char *cmd1);
void child_process_2(t_pipe data, char *cmd2, int ac, char **av);

# endif
