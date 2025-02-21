/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:55:03 by raamorim          #+#    #+#             */
/*   Updated: 2025/02/21 14:07:22 by raamorim         ###   ########.fr       */
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
		return (printf("ERROR\n"), NULL);
	new = ft_split_quotes(input);
	if (!new)
		return (free_arr(new), NULL);
	return (new);
}
static char	*handle_dollar(char *str, char **env)
{
	int		i;
	char	*teste;
	char	*new;
	
	i = 0;
	while (str)
	{
		if (str[i] && str[i] == '$')
		{
			teste = get_env(&str[++i], env);
			new = ft_strdup(teste);
			if (!new)
				return (NULL);
			return (new);
		}
		i++;
	}
	return (NULL);
}
static void	check_dollar(t_info *info)
{
	int		i;
	char	*new;

	if (!info)
		return ;
	i = 1;
	while (info->args[i])
	{
		new = handle_dollar(info->args[i], info->my_env);
		if (!new)
			return ;
		if (new && new != info->args[i]	)
		{
			free(info->args[i]);
			info->args[i] = new;
		}
		i++;
	}
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
		check_dollar(info);
		info->flags = ft_strdup(info->args[1]);
	}
}
