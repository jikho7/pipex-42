/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:08:51 by jdefayes          #+#    #+#             */
/*   Updated: 2023/05/07 11:20:41 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
	int		i;
	int		j;
	int		fd_pipe1[2];
	int		fd_pipe2[2];
	int		pid_main;
	int		fd_in;
	int		fd_out;
	char	*path;
	char	**access_tab;
	char	*last_arg;
	char	*first_arg;
	char	**cmd_arg;
	char	**cmd_arg0;
	char	**cmd_arg1;
	char	*cmd1;
	char	*cmd2;
	char	**envp;
	char	*infile;
	char	*outfile;
}t_pipe;

void	perror_msg2(char *msg);
void	init_struc_pipe(t_pipe *d, int ac, char **av, char **env);

int		ft_strlen(const char *s);
char	**ft_split(const char *str, char c, int var);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_path(char **envp);
char	*ft_strjoin(char const *s1, char const *s2);

void	handle_pipes(int (*fd1)[2], int (*fd2)[2]);
char	*get_cmd_path(char *cmd, t_pipe *d);
int		control_files(char *infile, char *outfile);
void	child_process_0_2(t_pipe *d, char *av, char *first_arg);
void	child_process_1_2(t_pipe *d, char *av, char *last_arg);
int		fd_opened(void);
void	putzfrau(t_pipe *d);
int		close_fd(void);
void	perror_msg(void);
int		is_cmd_valid(char *cmd_path, t_pipe *d, int process);

void	command_not_found(char *cmd);
void	ft_putstr_fd(char *s, int fd);
void	error_msg(char *file_name);
void	free_double_tab(char **tab);
void	close_pipes(t_pipe *d, int process);
void	handle_dup_err(int fd_f, int fd_p, char **tab_cmd, int position);
void	handle_exec_err(int fd_p, char **tab_cmd, char *path_cmd);

void	handle_dup_err_middle(int fd_p, char **tab_cmd, char *path_cmd);
void	first_cmd(t_pipe *d, char *cmd_path);
void	last_cmd(t_pipe *d, char *cmd_path, int process);
void	middle_cmd(t_pipe *d, char *cmd_path, int process);
void	handle_dup_err2(int fd_f, t_pipe d, char *path_cmd, int position);
#endif
