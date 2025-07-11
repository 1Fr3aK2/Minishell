/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:39:56 by raamorim          #+#    #+#             */
/*   Updated: 2025/07/11 04:45:48 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tree	*build_tree_tokens(char **tokens, t_info *info)
{
	if (!tokens)
		return (NULL);
	return (parse_tokens(tokens, info));
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
	info->error_msg = false;
}

void	remove_empty_tokens(char ***tokens)
{
	char	**new_tokens;
	int		count;

	if (!tokens || !*tokens)
		return ;
	count = count_non_empty(*tokens);
	new_tokens = malloc(sizeof(char *) * (count + 1));
	if (!new_tokens)
		return ;
	copy_non_empty(*tokens, new_tokens);
	free_arr(*tokens);
	*tokens = new_tokens;
}

int	copy_tokens(char **dest, char **src, int start)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[start] = ft_strdup(src[i]);
		if (!dest[start])
			return (-1);
		start++;
		i++;
	}
	return (start);
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
		tokens = check_dollar_and_retokenize(tokens, info);
		remove_all_quotes(tokens);
		remove_empty_tokens(&tokens);
	}
	info->cmd_tree = build_tree_tokens(tokens, info);
	if (!info->cmd_tree)
	{
		if (!tokens[0] || tokens[0][0] == '\0')
			info->exit_status = 0;
		free_arr(tokens);
		return ;
	}
	free_arr(tokens);
}
