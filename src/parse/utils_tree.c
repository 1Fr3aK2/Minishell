/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:52:23 by raamorim          #+#    #+#             */
/*   Updated: 2025/04/20 00:02:47 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

/* int	search_ops(char **tokens)
{
	int	i;
	int	i;
	int	op_index;
	int	priority;
	int	current_priority;

	if (!tokens)
		return (-1);
	i = 0;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], "&&", ft_strlen("&&")) == 0)
			return (i);
		else if (ft_strncmp(tokens[i], "||", ft_strlen("||")) == 0)
			return (i);
		else if (ft_strncmp(tokens[i], "|", ft_strlen("|")) == 0)
			return (i);
		i++;
	}
	return (-1);
} */
int	search_ops(char **tokens)
{
	op_index = -1;
	priority = 0;
	i = 0;
	while (tokens[i])
	{
		current_priority = 0;
		if (ft_strncmp(tokens[i], "||", 3) == 0)
			current_priority = 1;
		else if (ft_strncmp(tokens[i], "&&", 3) == 0)
			current_priority = 2;
		else if (ft_strncmp(tokens[i], "|", 2) == 0)
			current_priority = 3;
		else if (ft_strncmp(tokens[i], "&", 2) == 0)
			current_priority = 4;
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
