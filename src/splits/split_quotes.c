/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:23:09 by raamorim          #+#    #+#             */
/*   Updated: 2025/05/05 19:57:11 by rafael           ###   ########.fr       */
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
	int		len = 0;
	char	quote = 0;
	int		in_quotes = 0;
	int		op_len;

	if ((op_len = is_operator(str)))
		return (op_len);
	while (str[len] && (!is_space(str[len]) || in_quotes))
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
		else if (!in_quotes && is_operator(&str[len]))
			break;
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

static int	conta_word(char *str)
{
	int		i = 0;
	int		count = 0;
	char	quote = 0;
	int		in_quotes = 0;
	int		op_len;

	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			i++;
		if (!str[i])
			break;
		if ((op_len = is_operator(&str[i])))
		{
			i += op_len;
			count++;
		}
		else
		{
			while (str[i] && (!is_space(str[i]) || in_quotes))
			{
				if (is_quote(str[i]))
				{
					if (!in_quotes)
					{
						in_quotes = 1;
						quote = str[i];
					}
					else if (str[i] == quote)
						in_quotes = 0;
				}
				else if (!in_quotes && is_operator(&str[i]))
					break;
				i++;
			}
			count++;
		}
	}
	return (count);
}


char	**ft_split_quotes(char *s)
{
	char	**dest;
	int		i = 0;
	int		j = 0;
	int		len;

	dest = (char **)malloc((conta_word(s) + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	while (s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		if (s[i])
		{
			len = get_word_length(s + i);
			if (!word_alloc(dest, s + i, len, j))
				return (free_str(dest, j));
			j++;
			i += len;
		}
	}
	dest[j] = NULL;
	return (dest);
}
