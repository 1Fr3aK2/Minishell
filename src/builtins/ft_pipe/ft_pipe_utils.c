/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 02:44:02 by rafael            #+#    #+#             */
/*   Updated: 2025/06/28 16:07:19 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void wait_all(pid_t last_pid, t_info *info) {
    int status;
    pid_t wpid;
    
    dprintf(2, "[DEBUG wait_all] waiting for children (last_pid=%d)\n", last_pid);
    
    // MUDANÇA PRINCIPAL: usar waitpid(-1, ...) em vez de wait()
    // Isso espera por QUALQUER processo filho, não só o primeiro
    while ((wpid = waitpid(-1, &status, 0)) > 0) {
        dprintf(2, "[DEBUG wait_all] got wpid=%d\n", wpid);
        
        if (wpid == last_pid && WIFEXITED(status)) {
            int code = WEXITSTATUS(status);
            dprintf(2, "[DEBUG wait_all] last_pid exited with %d\n", code);
            update_status(info, code);
        }
        else if (wpid == last_pid && WIFSIGNALED(status)) {
            int sig = WTERMSIG(status);
            dprintf(2, "[DEBUG wait_all] last_pid signaled with %d\n", sig);
            if (sig == SIGQUIT) {
                update_status(info, 131);
                write(1, "Quit (core dumped)\n", 19);
            }
            else if (sig == SIGINT)
                update_status(info, 130);
        }
        else {
            dprintf(2, "[DEBUG wait_all] intermediate process %d finished\n", wpid);
        }
    }
    
    dprintf(2, "[DEBUG wait_all] all children finished\n");
}


void	handle_heredoc(t_tree *node)
{
	if (node && node->io && node->io->heredoc_fd != -1)
	{
		if (dup2(node->io->heredoc_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 heredoc");
			exit(1);
		}
		close(node->io->heredoc_fd);
		node->io->heredoc_fd = -1;
	}
}

void	exec_comand_op(t_info *info, t_tree *node)
{
	if (node->type == PIPE)
		ft_pipe(info, node);
	else
		exit(127);
}

void	setup_stdin(t_tree *node, int in)
{
	// Se o nó tem redirecionamento de input próprio, usa esse
	if (node->io && node->io->fd_in != -1)
	{
		dprintf(2, "DEBUG: using node's input redirection fd %d\n", node->io->fd_in);
		if (dup2(node->io->fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2 node input");
			exit(1);
		}
		close(node->io->fd_in);
		node->io->fd_in = -1;
		
		// Se havia um fd do pipe, fecha-o
		if (in != -1)
		{
			dprintf(2, "DEBUG: closing pipe input fd %d (node has own input)\n", in);
			close(in);
		}
	}
	// Se tem heredoc, usa o heredoc
	else if (node->io && node->io->heredoc_fd != -1)
	{
		if (in != -1)
		{
			dprintf(2, "DEBUG: closing input fd %d before heredoc\n", in);
			close(in);
		}
		handle_heredoc(node);
	}
	// Senão, usa o fd do pipe
	else if (in != -1)
	{
		dprintf(2, "DEBUG: duplicating input fd %d to STDIN\n", in);
		if (dup2(in, STDIN_FILENO) == -1)
		{
			perror("dup2 stdin");
			exit(1);
		}
		dprintf(2, "DEBUG: closing input fd %d\n", in);
		close(in);
	}
}

void	execute_node(t_info *info, t_tree *node)
{
	if (node->type == CMD)
	{
		if (is_builtin(info->builtins->builtins, node->args[0]) == 0)
			exec_builtins(node->args, info, node);
		else
			exec_command(info, node);
	}
	else
		exec_comand_op(info, node);
}
