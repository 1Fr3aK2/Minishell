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

#include "../../includes/minishell.h"

static int	word_len_custom(const char *str)
{
	int	len;

	if (!str)
		return (0);
	if (is_operator(str))
		return (is_operator(str));
	len = 0;
	while (str[len] && !is_space(str[len]) && !is_operator(&str[len]))
		len++;
	return (len);
}

static int	counte_word(const char *str)
{
	int	i;
	int	words;
	int	op_len;

	if (!str)
		return (-1);
	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			i++;
		if (!str[i])
			break ;
		op_len = is_operator(&str[i]);
		if (op_len)
			i += op_len;
		else
			while (str[i] && !is_space(str[i]) && !is_operator(&str[i]))
				i++;
		words++;
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
	word_len = word_len_custom(str);
	word = (char *)malloc(word_len + 1);
	if (!word)
		return (NULL);
	while (++i < word_len)
		word[i] = str[i];
	word[i] = '\0';
	return (word);
}

char	**custom_ft_split(char const *s)
{
	char	**dest;
	int		i;
	int		len;

	i = 0;
	if (!s)
		return (NULL);
	dest = (char **)malloc((counte_word(s) + 1) * sizeof(char *));
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
			len = word_len_custom(s);
			s += len;
		}
	}
	dest[i] = 0;
	return (dest);
}
