/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:05:59 by raamorim          #+#    #+#             */
/*   Updated: 2025/02/19 13:45:22 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

static int	check_close(char *input, int *i, char quote)
{
	int	closed;
	int	j;

	if (!input)
		return (-1);
	closed = 0;
	j = *i;
	while (input[j])
	{
		if (input[j] == quote)
		{
			closed = !closed;
			*i = ++j;
			return (closed);
		}
		j++;
	}
	return (closed);
}

int	check_quotes(char *input)
{
	int		i;
	char	quote;

	if (!input)
		return (-1);
	i = 0;
	quote = 0;
	while (input[i])
	{
		while (input[i] && !is_quote(input[i]))
			i++;
		if (input[i] && is_quote(input[i]))
		{
			quote = input[i++];
			if (check_close(input, &i, quote) == 0)
				return (-1);
		}
	}
	return (0);
}

static char	*remove_quotes(char *str)
{
	char	*new;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (size_woutquotes(str) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
			handle_quotes(str, new, i, &j);
		else
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

void	remove_all_quotes(t_info *info)
{
	int		i;
	char	*temp;

	if (!info)
		return ;
	i = 0;
	while (info->args[i])
	{
		temp = remove_quotes(info->args[i]);
		if (temp)
		{
			free(info->args[i]);
			info->args[i] = temp;
		}
		i++;
	}
}
