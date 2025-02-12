/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:05:02 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/29 11:37:35 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static int	count_word(const char *str)
{
	int		i;
	int		words;

	if (!str)
		return (-1);
	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			i++;
		if (str[i])
			words++;
		while (str[i] && !is_space(str[i]))
			i++;
	}
	return (words);
}

static char	*word_aloc(const char *str)
{
	char	*word;
	int		word_len;
	int		i;

	if (!str)
		return (NULL);
	i = -1;
	word_len = 0;
	while (str[word_len] && !is_space(str[word_len]))
		word_len++;
	word = (char *)malloc(word_len + 1);
	if (!word)
		return (NULL);
	while (++i < word_len)
		word[i] = str[i];
	word[i] = '\0';
	return (word);
}

static void	*free_str(char **dest, int i)
{
	while (i >= 0)
		free(dest[i--]);
	free(dest);
	return (NULL);
}

char	**custom_ft_split(char const *s)
{
	char	**dest;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	dest = (char **)malloc((count_word(s) + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	while (*s)
	{
		while (*s && is_space(*s))
			s++;
		if (*s)
		{
			dest[i] = word_aloc(s);
			if (!dest[i++])
				return (free_str(dest, i - 1), NULL);
		}
		while (*s && !is_space(*s))
			s++;
	}
	dest[i] = 0;
	return (dest);
}