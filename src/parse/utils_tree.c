/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:52:23 by raamorim          #+#    #+#             */
/*   Updated: 2025/03/17 11:54:25 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

int	search_ops(char **tokens)
{
	int	i;

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
