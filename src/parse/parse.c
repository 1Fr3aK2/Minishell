/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:55:03 by raamorim          #+#    #+#             */
/*   Updated: 2025/02/17 14:09:46 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

static int	size_woutquotes(char *str)
{
	int		i;
	char	quote;
	int		count;

	if (!str)
		return (-1);
	i = 0;
	quote = 0;
	count = 0;
	if (str[i] && is_quote(str[i]))
	{
		i++;
		quote = str[i];
	}
	while (str[i])
	{
		if (str[i] && str[i] != quote)
		{
			i++;
			count++;
		}
		else if (str[i] && str[i] == quote)
			i++;
	}
	return (count);
}
static int	handle_quotes(char *str, char *new, int i, int *j)
{
	static int	in_quotes;
	static char	quote_char;

	if (in_quotes == 0)
	{
		in_quotes = 1;
		quote_char = str[i];
	}
	else if (str[i] == quote_char)
		in_quotes = 0;
	else
		new[(*j)++] = str[i];
	return (in_quotes);
}


char	*remove_quotes(char *str)
{
	char	*new;
	int		i;
	int		j;
	int		in_quotes;

	if (!str)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (size_woutquotes(str) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	in_quotes = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
			in_quotes = handle_quotes(str, new, i, &j);
		else
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

char	**new_input(char *input)
{
	char	**new;

	// if (count_quotes(input) % 2 != 0)
	// 	return (printf("ERROR\n"), NULL);
	if (count_quotes(input) == 0)
		return (custom_ft_split(input));
	new = (char **)malloc(sizeof(char *) * (count_word(input) + 1));
	if (!new)
		return (NULL);
	new = ft_split_quotes(input);
	if (!new)
		return (free_arr(new), NULL);
	return (new);
}

void	parse(char *input, t_info *info)
{
	size_t	size;
	int		i;

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
	i = 0;
	while (info->args[i])
	{
		printf("before remove info->args[%d] = %s\n", i, info->args[i]);
		i++;
	}
	printf("\n\n");
	i = 0;
	while (info->args[i])
	{
		info->args[i] = remove_quotes(info->args[i]);
		printf("after remove info->args[%d] = %s\n", i, info->args[i]);
		i++;
	}
}
