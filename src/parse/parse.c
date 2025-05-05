/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:55:03 by raamorim          #+#    #+#             */
/*   Updated: 2025/05/05 02:51:37 by rafael           ###   ########.fr       */
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

static void	check_dollar(char **args, t_info *info)
{
	int		i;
	int		j;
	char	*new;

	if (!info || !info->my_env || !args)
		return ;
	i = 1;
	while (args[i])
	{
		j = 0;
		if (args[i][j] && args[i][j] == '$' && args[i][j + 1] == '\0')
			return ;
		new = handle_dollar(args[i], info->my_env);
		if (!new)
			return ;
		if (ft_strncmp(new, args[i], ft_strlen(args[i])) != 0)
		{
			free(args[i]);
			args[i] = new;
		}
		else
			free(new);
		i++;
	}
}

t_tree	*build_tree_tokens(char **tokens)
{
	if (!tokens)
		return (NULL);
	return (parse_tokens(tokens));
}

void	parse(char *input, t_info *info)
{
	char	**tokens;

	if (!input || !info)
		return ;
	tokens = NULL;
	if (info->cmd_tree)
	{
		free_tree(info->cmd_tree);
		info->cmd_tree = NULL;
	}
	if (info->flags)
	{
		free(info->flags);
		info->flags = NULL;
	}
	tokens = new_input(input);
	if (!tokens)
		return ;
	if (tokens)
	{
		check_dollar(tokens, info);
		remove_all_quotes(tokens);
	}
	info->cmd_tree = build_tree_tokens(tokens);
	if (!info->cmd_tree)
		return (free_arr(tokens));
	if (info->cmd_tree->args && info->cmd_tree->args[1])
		info->flags = ft_strdup(info->cmd_tree->args[1]);
	free_arr(tokens);
}
