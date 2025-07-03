/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:30:03 by rafael            #+#    #+#             */
/*   Updated: 2025/07/03 04:02:38 by rafael           ###   ########.fr       */
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

int	apply_redirections(t_info *info, int *saved_in, int *saved_out)
{
	if (info->io->fd_in != -1)
	{
		*saved_in = dup(STDIN_FILENO);
		if (*saved_in == -1 || dup2(info->io->fd_in, STDIN_FILENO) == -1)
			return (-1);
		close(info->io->fd_in);
		info->io->fd_in = -1;
	}
	if (info->io->fd_out != -1)
	{
		*saved_out = dup(STDOUT_FILENO);
		if (*saved_out == -1 || dup2(info->io->fd_out, STDOUT_FILENO) == -1)
			return (-1);
		close(info->io->fd_out);
		info->io->fd_out = -1;
	}
	return (0);
}
