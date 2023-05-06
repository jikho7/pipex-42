/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:40:14 by jdefayes          #+#    #+#             */
/*   Updated: 2023/05/06 17:02:45 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int		delete_word(char **str, int size);
static int		count_words(const char *str, char sign);
static void		write_word(char *dest, const char *from, char sign, int var);
static int		write_split(char **split, const char *str, char sign, int var);

static int	delete_word(char **str, int size)
{
	while (size--)
		free(str[size]);
	return (0);
}

static int	count_words(const char *str, char sign)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == sign)
			i++;
		while (str[i] != sign && str[i] != 0)
			i++;
		if (str[i - 1] != sign)
			count++;
	}
	return (count);
}

static void	write_word(char *dest, const char *word_begin, char sign, int var)
{
	int	i;
	//(void)var;

	i = 0;
	while (word_begin[i] != sign && word_begin[i] != '\0')
	{
		dest[i] = word_begin[i];
		i++;
	}
	if (var == 1)
	{
		dest[i++] = '/';
	}
	dest[i] = '\0';
}

static int	write_split(char **tab_split, const char *str, char sign, int var)
{
	int		i;
	int		j;
	int		word;

	word = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == sign || str[i] == '\0')
			i++;
		else
		{
			j = 0;
			while (str[i + j] != sign && str[i + j] != '\0')
				j++;
			tab_split [word] = (char *)malloc(sizeof(char) * (j + 1));
			if (tab_split[word] == NULL)
				return (delete_word(tab_split, word - 1));
			write_word(tab_split[word], &str[i], sign, var);
			i = i + j;
			word++;
		}
	}
	return (0);
}

char	**ft_split(const char *str, char c, int var)
{
	char	**tab_result;
	int		words;

	words = count_words(str, c);
	tab_result = (char **)malloc(sizeof(char *) * (words + 1));
	if (tab_result == NULL)
		return (NULL);
	tab_result[words] = 0;
	write_split(tab_result, str, c, var);
	return (tab_result);
}
