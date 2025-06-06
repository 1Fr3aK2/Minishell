/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:54:28 by rafael            #+#    #+#             */
/*   Updated: 2025/06/06 15:40:26 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		quote = str[i];
		i++;
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

void	handle_quotes(char *str, char *new, int i, int *j)
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
}

char	**new_input(char *input)
{
	char	**new;

	if (count_quotes(input) == 0)
		return (custom_ft_split(input));
	if (check_quotes(input) == -1)
		return (ft_putstr_fd("Syntax error (quotes)\n", 2), NULL);
	new = ft_split_quotes(input);
	if (!new)
		return (free_arr(new), NULL);
	return (new);
}

t_io	*alloc_io(void)
{
	t_io	*io;

	io = malloc(sizeof(t_io));
	if (io)
		init_io(io);
	return (io);
}
