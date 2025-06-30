/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:30:03 by rafael            #+#    #+#             */
/*   Updated: 2025/06/30 18:32:41 by rafael           ###   ########.fr       */
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
