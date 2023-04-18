/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:08:51 by jdefayes          #+#    #+#             */
/*   Updated: 2023/04/18 22:06:26 by jdefayes         ###   ########.fr       */
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
	int		pidcurrent1;
	int		pidcurrent2;
	int		fd_in;
	int		fd_out;
	int		status;
	char	*path;
	char	**access;
	char	**cmd_arg1;
	char	**cmd_arg2;
	char	*cmd1;
	char	*cmd2;
	char	**envp;
}t_pipe;

size_t	ft_strlen(const char *s);
char	**ft_split(const char *str, char c);
void child_process_1(t_pipe data);
void child_process_2(t_pipe data, int ac, char **av);
//char	*ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char *get_path(char **envp);
char	*ft_strjoin(char const *s1, char const *s2);

# endif
