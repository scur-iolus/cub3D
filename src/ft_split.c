/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:07:33 by llalba            #+#    #+#             */
/*   Updated: 2022/01/31 17:08:23 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	ft_wordcopy(char *word_cpy, char const *str, size_t *pos, char c)
{
	size_t	j;

	j = 0;
	while (str[*pos] && str[*pos] == c)
		(*pos)++;
	while (str[*pos] && str[*pos] != c)
	{
		word_cpy[j] = str[*pos];
		(*pos)++;
		j++;
	}
	word_cpy[j] = 0;
}

static void	ft_copy(char **dest, char const *str, size_t size, char c)
{
	size_t	curr_word;
	size_t	pos;

	curr_word = 0;
	pos = 0;
	while (curr_word < size)
	{
		ft_wordcopy(dest[curr_word], str, &pos, c);
		curr_word++;
	}
	dest[size] = 0;
}

static size_t	wordlen(size_t *i, char const *str, char c)
{
	size_t	j;

	j = 0;
	while (str[*i] && str[*i] == c)
		(*i)++;
	while (str[*i] && str[*i] != c)
	{
		(*i)++;
		j++;
	}
	return (j);
}

static size_t	count_word(char const *str, char c)
{
	size_t	i;
	size_t	isword;
	size_t	countword;

	i = 0;
	isword = 0;
	countword = 0;
	while (str[i])
	{
		if (str[i] != c && isword == 0)
		{
			isword = 1;
			countword++;
		}
		if (str[i] == c)
			isword = 0;
		i++;
	}
	return (countword);
}

char	**ft_split(char const *str, char c)
{
	size_t	size;
	char	**dest;
	size_t	i;
	size_t	pos;

	if (!str || !(*str))
		return (0);
	size = count_word(str, c);
	dest = (char **)malloc(sizeof(char *) * (size + 1));
	if (!dest)
		return (0);
	i = 0;
	pos = 0;
	while (i < size)
	{
		dest[i] = malloc(sizeof(char) * (wordlen(&pos, str, c) + 1));
		if (!dest[i])
			return (0);
		i++;
	}
	ft_copy(dest, str, size, c);
	return (dest);
}
