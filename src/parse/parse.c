/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:55:03 by raamorim          #+#    #+#             */
/*   Updated: 2025/02/18 23:19:26 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

int	size_woutquotes(char *str)
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

int	handle_quotes(char *str, char *new, int i, int *j)
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

char	**new_input(char *input)
{
	char	**new;

	if (count_quotes(input) == 0)
		return (custom_ft_split(input));
	if (check_quotes(input) == -1)
		return (printf("ERROR\n"), NULL);
	new = ft_split_quotes(input);
	if (!new)
		return (free_arr(new), NULL);
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
		if (info->args)
			free_arr(info->args);
		info->args = new_input(input);
		if (!info->args)
			return ;
		remove_all_quotes(info);
		info->flags = ft_strdup(info->args[1]);
	}
}
