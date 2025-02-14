/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:55:03 by raamorim          #+#    #+#             */
/*   Updated: 2025/02/14 04:43:55 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

bool	is_quote(char c)
{
	return ((c == '\'' || c == '\"'));
}

int	count_quotes(char *input)
{
	int	quotes;
	int	i;

	if (!input)
		return (0);
	i = 0;
	quotes = 0;
	while (input[i])
	{
		if (is_quote(input[i]))
			quotes++;
		i++;
	}
	return (quotes);
}

static int	count_word(char *str)
{
	int		i;
	int		words;
	char	quote;

	i = 0;
	words = 0;
	quote = 0;
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			i++;
		if (is_quote(str[i]))
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == quote)
				i++;
		}
		else
			while (str[i] && !is_space(str[i]) && !is_quote(str[i]))
				i++;
		words++;
	}
	return (words);
}

static char	*word_aloc(char **str)
{
	char	*word;
	int		start;
	char	quote;

	start = 0;
	quote = 0;
	if (is_quote((*str)[start]))
	{
		quote = (*str)[start];
		while ((*str)[++start] && (*str)[start] != quote)
			;
		if ((*str)[start] == quote)
			start++;
	}
	else
		while ((*str)[start] && !is_space((*str)[start]))
			start++;
	word = (char *)malloc(sizeof(char) * (start + 1));
	if (!word)
		return (NULL);
	ft_strncpy(word, *str, start);
	word[start] = '\0';
	*str += start;
	return (word);
}

static void	*free_str(char **dest, int i)
{
	while (i >= 0)
		free(dest[i--]);
	free(dest);
	return (NULL);
}

char	**custome_ft_split(char *s)
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
			dest[i] = word_aloc(&s);
			if (!dest[i++])
				return (free_str(dest, i - 1));
		}
	}
	dest[i] = NULL;
	return (dest);
}

char	**new_input(char *input)
{
	char	**new;

	if (count_quotes(input) % 2 != 0)
		return (printf("ERROR\n"), NULL);
	if (count_quotes(input) == 0)
		return (custom_ft_split(input));
	new = (char **)malloc(sizeof(char *) * (count_word(input) + 1));
	if (!new)
		return (NULL);
	new = custome_ft_split(input);
	if (!new)
		return (NULL);
	return (new);
}

void	parse(char *input, t_info *info)
{
	size_t	size;

	if (!input)
		return ;
	size = ft_strlen(input);
	if (size > 0)
	{
		info->args = new_input(input);
		if (!info->args)
			return ;
		info->flags = ft_strdup(info->args[1]);
	}
}
