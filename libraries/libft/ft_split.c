/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:51:05 by raamorim          #+#    #+#             */
/*   Updated: 2025/02/05 11:51:05 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description: Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer.

Return value: The array of new strings resulting from the split.
NULL if the allocation fails. */

#include "libft.h"

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

char	**ft_split(char const *s)
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
