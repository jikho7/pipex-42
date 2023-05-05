/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:40:37 by jdefayes          #+#    #+#             */
/*   Updated: 2023/05/05 21:03:29 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*cs1;
	char	*cs2;
	char	*result;
	int		i;
	int		j;

	cs1 = (char *)s1;
	cs2 = (char *)s2;
	i = 0;
	j = 0;
	result = malloc(sizeof(char) * ((ft_strlen(cs1)) + (ft_strlen(cs2)) + 1));
	if (result == NULL)
		return (NULL);
	while (cs1[i])
		result[j++] = cs1[i++];
	result[j] = ' ';
	i = 0;
	while (cs2[i])
		result[j++] = cs2[i++];
	result[j] = '\0';
	return (result);
}

int	control_files(char *infile, char *outfile)
{
	int in;
	int out;
	const char* s;

	s = (const char*)infile;
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

void	putzfrau(t_pipe d)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	close(d.fd_in);
	close(d.fd_out);
	while (d.access[size])
		size++;
	while (i < size)
		free(d.access[i++]);
	free(d.access);
}
/*
int	fd_opened(void)
{
	int	maxfd;
	int	count;
	int	fd;

	count = 0;
	fd = 0;
	maxfd = sysconf(_SC_OPEN_MAX);
	while (fd < maxfd)
	{
		if (fcntl(fd, F_GETFD) != -1)
			count++;
		fd++;
	}
	printf("Nombre de descripteurs de fichiers ouverts : %d\n", count);
	return (0);
}

int	close_fd(void)
{
	int	maxfd = sysconf(_SC_OPEN_MAX);
	int	count;
	int	fd;

	count = 0;
	fd = 0;
	while (fd < maxfd)
	{
		if (fcntl(fd, F_GETFD) != -1)
		{
			close(fd);
		}
		fd++;
	}
	printf("Nombre de descripteurs de fichiers fermes : %d\n", count);
	return (0);
}
*/
