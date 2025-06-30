/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:30:03 by rafael            #+#    #+#             */
/*   Updated: 2025/06/30 18:42:11 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redir(char **redirs, char *cmd)
{
	int	i;

	if (!cmd || !redirs || !*redirs)
		return (1);
	i = 0;
	while (redirs[i])
	{
		if (ft_strncmp(cmd, redirs[i], ft_strlen(redirs[i])) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	exec_redirs(t_tree *node, t_info *info, int *i)
{
	if (ft_strncmp(node->args[*i], "<", 2) == 0)
	{
		if (handle_input_redirection(node->io, info) == -1)
			ft_exit2(info);
	}
	else if (ft_strncmp(node->args[*i], ">", 2) == 0)
	{
		if (handle_output_redirection(node->io, info) == -1)
			ft_exit2(info);
	}
	else if (ft_strncmp(node->args[*i], ">>", 3) == 0)
	{
		if (handle_append_redirection(node->io, info) == -1)
			ft_exit2(info);
	}
}

bool	has_redirection(t_tree *node)
{
	int	i;

	if (!node || !node->args)
		return (false);
	i = 0;
	while (node->args[i])
	{
		if (ft_strncmp(node->args[i], "<", 2) == 0 || ft_strncmp(node->args[i],
				">", 2) == 0 || ft_strncmp(node->args[i], ">>", 3) == 0)
		{
			return (true);
		}
		i++;
	}
	return (false);
}
