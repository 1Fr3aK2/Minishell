/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:05:59 by raamorim          #+#    #+#             */
/*   Updated: 2025/02/18 15:47:44 by raamorim         ###   ########.fr       */
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
	int		count;
	char	quote;

	if (!input)
		return (-1);
	i = 0;
	count = 0;
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
