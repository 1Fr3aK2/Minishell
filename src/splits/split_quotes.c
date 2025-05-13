/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:43:51 by raamorim          #+#    #+#             */
/*   Updated: 2025/05/13 18:29:27 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

static void	update_quotes(char c, int *in_quotes, char *quote)
{
	if (is_quote(c))
	{
		if (!*in_quotes)
		{
			*in_quotes = 1;
			*quote = c;
		}
		else if (c == *quote)
			*in_quotes = 0;
	}
}

static int	get_word_length(char *str)
{
	int		len;
	int		in_quotes;
	char	quote;

	len = 0;
	in_quotes = 0;
	quote = 0;
	if (!str || !str[0])
		return (0);
	if (!in_quotes && is_operator_char(str[0]))
	{
		if (is_double_operator(str))
			return (2);
		return (1);
	}
	while (str[len] && (!is_space(str[len]) && (!is_operator_char(str[len])
				|| in_quotes)))
		update_quotes(str[len++], &in_quotes, &quote);
	return (len);
}

static int	count_tokens(char *s)
{
	int	i;
	int	count;
	int	len;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		if (s[i])
		{
			len = get_word_length(s + i);
			if (len == 0)
				break ;
			i += len;
			count++;
		}
	}
	return (count);
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
	if (!s)
		return (NULL);
	dest = (char **)malloc((count_tokens(s) + 1) * sizeof(char *));
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
			i += get_word_length(s + i);
			j++;
		}
	}
	dest[j] = NULL;
	return (dest);
}
