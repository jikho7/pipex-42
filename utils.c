/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:40:37 by jdefayes          #+#    #+#             */
/*   Updated: 2023/05/06 14:46:47 by jdefayes         ###   ########.fr       */
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
	//free(cs1);
	//free(cs2);
	return (result);
}

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

