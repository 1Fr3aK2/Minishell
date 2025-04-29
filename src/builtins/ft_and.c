/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:57:06 by dsteiger          #+#    #+#             */
/*   Updated: 2025/04/29 19:23:27 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void	ft_and_wrapper(t_info *info, t_tree *node)
{
	pid_t	pid;
	int		status;

	if (!info || !node)
		return ;
    if (node->type == AND)
    {
        if (node->left && node->right)
        {
            ft_and_wrapper(info, node->left);
            if (g_exit_status == 0)   
                ft_and_wrapper(info, node->right);
        }
        else
        {
            ft_putstr_fd("Shellinho: syntax error\n", 2);
            g_exit_status = 2;
            free_tree(node);
        }
    }
    else
    {
        if (check_builtins(info) == 0)
            return ;
        pid = fork();
        if (pid == -1)
            return (ft_putstr_fd("Fork error", 2));
        if (pid == 0)
            exec_command(info, node);
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) // verifica se terminou normalmente
            g_exit_status = WEXITSTATUS(status);
    }
}
void	ft_and(t_info *info)
{
	if (!info)
		return ;
	ft_and_wrapper(info, info->cmd_tree);
}