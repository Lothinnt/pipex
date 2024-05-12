/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothin <lothin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 12:04:52 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/04/30 21:42:42 by lothin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		count++ ;
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
		}
		else
		{
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*copy_word(char const *s, int start, int end)
{
	char	*word;
	int		i;
	int		j;

	i = start;
	j = 0;
	word = (char *)malloc(sizeof(*word) * (end - start + 1));
	if (!word)
		return (NULL);
	while (i < end)
	{
		if (s[i] != '\'')
		{
			word[j] = s[i];
			j++;
		}
		i++;
	}
	word[j] = '\0';
	return (word);
}

int	move_to_next_word(char const *s, int i, char c)
{
	if (s[i] == '\'')
	{
		i++;
		while (s[i] && s[i] != '\'')
			i++;
		i++;
	}
	else
	{
		while (s[i] && s[i] != c && s[i] != '\'')
			i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof(*split) * (count_words(s, c) + 1));
	if (!split)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		i = move_to_next_word(s, i, c);
		if (i > start)
			split[j++] = copy_word(s, start, i);
	}
	split[j] = NULL;
	return (split);
}
