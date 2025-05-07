/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:55:03 by raamorim          #+#    #+#             */
/*   Updated: 2025/05/07 01:02:29 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

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

static void	reset_info(t_info *info)
{
	if (!info)
		return ;
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
}

void	parse(char *input, t_info *info)
{
	char	**tokens;

	if (!input || !info)
		return ;
	tokens = NULL;
	reset_info(info);
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
