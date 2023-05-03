/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:08:51 by jdefayes          #+#    #+#             */
/*   Updated: 2023/05/03 18:31:42 by jdefayes         ###   ########.fr       */
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
# include <fcntl.h>
# include <string.h>

typedef struct s_pipe
{
	int		fd_pipe1[2];
	int		fd_pipe2[2];
	int		pid_main;
	int		fd_in;
	int		fd_out;
	char	*path;
	char	**access;
	char	*last_arg;
	char	*first_arg;
	char	**cmd_arg;
	char	**cmd_arg0;
	char	**cmd_arg1;
	char	*cmd1;
	char	*cmd2;
	char	**envp;
	char	*outfile;
}t_pipe;

int		ft_strlen(const char *s);
char	**ft_split(const char *str, char c, int var);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_path(char **envp);
char	*ft_strjoin(char const *s1, char const *s2);

void	handle_pipes(int (*fd1)[2], int (*fd2)[2]);
char	*get_cmd_path(char *cmd, t_pipe d);
void	control_files(char *infile, char *outfile);
void	child_process_0_2(t_pipe d, char *av, char *first_arg, char *infile);
void	child_process_1_2(t_pipe d, char *av, char *last_arg);
void	write_outfile(t_pipe d);
int		fd_opened(void);
void	putzfrau(t_pipe d);
int		close_fd(void);
int		error(char *msg);
void	perror_msg(char *msg);
int		is_cmd_valid(char *cmd_path, t_pipe d, int process);
#endif
