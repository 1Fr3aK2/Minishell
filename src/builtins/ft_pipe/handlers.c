/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:06:03 by rafael            #+#    #+#             */
/*   Updated: 2025/06/30 19:09:21 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	handle_fork_exec(t_info *info, t_tree *curr, int in, pid_t *last_pid)
{
	*last_pid = fork();
	if (*last_pid == -1)
	{
		perror("fork error");
		if (in != -1)
			close(in);
		return ;
	}
	if (*last_pid == 0)
		child_exec(info, curr, in, -1);
}

void	handle_pipe_loop(t_info *info, t_tree **curr, int *in, pid_t *last_pid)
{
	while (*curr && (*curr)->type == PIPE)
	{
		*last_pid = create_pipe(info, *curr, *in, in);
		if (*last_pid == -1)
		{
			if (*in != -1)
				close(*in);
			return ;
		}
		*curr = (*curr)->right;
	}
}
