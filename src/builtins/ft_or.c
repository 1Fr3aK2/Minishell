/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:25:15 by rafael            #+#    #+#             */
/*   Updated: 2025/05/19 18:25:30 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void	exec_command_op(t_info *info, t_tree *node)
{
	pid_t	pid;
	int		status;
	int		sig;

	if (check_builtins(info) == 0)
		return ;
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("Fork error\n", 2), (void)0);
	if (pid == 0)
		exec_command(info, node);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		info->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			info->exit_status = 130;
		else if (sig == SIGQUIT)
		{
			info->exit_status = 131;
			write(1, "Quit (core dumped)\n", 19);
		}
	}
}

void	ft_or(t_info *info, t_tree *node)
{
	if (!info || !node)
		return ;
	if (node->type == OR)
	{
		if (node->left && node->right)
		{
			ft_or(info, node->left);
			if (info->exit_status != 0 && info->exit_status != 130)
				ft_or(info, node->right);
		}
		else
		{
			ft_putstr_fd("Shellinho: syntax error\n", 2);
			update_status(info, 2);
			free_tree(node);
		}
	}
	else
		exec_command_op(info, node);
}

void	ft_or_wrapper(t_info *info)
{
	if (!info)
		return ;
	prepare_heredocs(info->cmd_tree, info);
	ft_or(info, info->cmd_tree);
}
