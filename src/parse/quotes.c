/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:05:59 by raamorim          #+#    #+#             */
/*   Updated: 2025/07/11 17:24:52 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*remove_quotes(char *str)
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

static void	process_quote_removal(char **tokens, int *i, int *skip_next)
{
	char	*temp;

	while (tokens[*i])
	{
		if (*skip_next)
		{
			*skip_next = 0;
			(*i)++;
			continue ;
		}
		if (ft_strncmp(tokens[*i], "<<", 2) == 0 && tokens[*i][2] == '\0')
		{
			*skip_next = 1;
			(*i)++;
			continue ;
		}
		add_space_operators(&tokens[*i]);
		temp = remove_quotes(tokens[*i]);
		if (temp)
		{
			free(tokens[*i]);
			tokens[*i] = temp;
		}
		(*i)++;
	}
}

void	remove_all_quotes(char **tokens)
{
	int	i;
	int	skip_next;

	if (!tokens)
		return ;
	i = 0;
	skip_next = 0;
	process_quote_removal(tokens, &i, &skip_next);
}
