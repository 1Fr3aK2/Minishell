/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:23:09 by raamorim          #+#    #+#             */
/*   Updated: 2025/05/10 03:41:58 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

static void	*free_str(char **dest, int i)
{
	while (i >= 0)
		free(dest[i--]);
	free(dest);
	return (NULL);
}

static int	get_word_length(char *str)
{
	int			len;
	char		quote;
	static int	in_quotes;

	len = 0;
	quote = 0;
	while (str[len] && (!is_space(str[len]) || in_quotes == 1))
	{
		if (is_quote(str[len]))
		{
			if (!in_quotes)
			{
				in_quotes = 1;
				quote = str[len];
			}
			else if (str[len] == quote)
				in_quotes = 0;
		}
		len++;
	}
	return (len);
}

static int	word_alloc(char **dest, char *s, int len, int j)
{
	if (!dest)
		return (-1);
	dest[j] = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest[j])
		return (0);
	ft_strncpy(dest[j], s, len);
	dest[j][len] = '\0';
	return (1);
}

char	**ft_split_quotes(char *s)
{
	char	**dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dest = (char **)malloc((count_word(s) + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	while (s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		if (s[i])
		{
			if (!word_alloc(dest, s + i, get_word_length(s + i), j))
				return (free_str(dest, j));
			j++;
			i += get_word_length(s + i);
		}
	}
	dest[j] = NULL;
	return (dest);
}