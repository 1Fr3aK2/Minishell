/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:52:23 by raamorim          #+#    #+#             */
/*   Updated: 2025/05/19 13:46:30 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shellinho.h"

static int	set_priority(char *str)
{
	if (!str)
		return (0);
	if (ft_strncmp(str, "||", 3) == 0)
		return (1);
	else if (ft_strncmp(str, "&&", 3) == 0)
		return (2);
	else if (ft_strncmp(str, "|", 2) == 0)
		return (3);
	return (0);
}

int	search_ops(char **tokens)
{
	int	i;
	int	op_index;
	int	priority;
	int	current_priority;

	op_index = -1;
	priority = 0;
	i = 0;
	while (tokens[i])
	{
		current_priority = set_priority(tokens[i]);
		if (current_priority > 0 && (op_index == -1
				|| current_priority <= priority))
		{
			op_index = i;
			priority = current_priority;
		}
		i++;
	}
	return (op_index);
}

t_node_type	find_type(char **tokens, int i)
{
	if (ft_strncmp(tokens[i], "&&", ft_strlen("&&")) == 0)
		return (AND);
	else if (ft_strncmp(tokens[i], "||", ft_strlen("||")) == 0)
		return (OR);
	else if (ft_strncmp(tokens[i], "|", ft_strlen("|")) == 0)
		return (PIPE);
	else
		return (CMD);
}

t_tree	*parse_tokens(char **tokens, t_info *info)
{
	int		op_index;
	int		total;
	t_tree	*node;

	op_index = -1;
	total = 0;
	node = NULL;
	if (!tokens || !tokens[0])
		return (NULL);
	if (has_invalid_redirection(tokens, info))
		return (NULL);
	while (tokens[total])
		total++;
	op_index = search_ops(tokens);
	if (op_index != -1)
		node = creat_op_node(tokens, &op_index, info);
	else
		node = create_node(tokens);
	return (node);
}
