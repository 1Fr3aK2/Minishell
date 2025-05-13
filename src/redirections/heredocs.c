/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:01:40 by dsteiger          #+#    #+#             */
/*   Updated: 2025/05/13 20:17:08 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void	handle_heredoc_redirection(t_io *io)
{
	char	*line;
	int		fd[2];
	pid_t	pid;
	int		status;
	//int		tty_fd;

	if (!io || !io->file || pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(fd[0]);
/*  		tty_fd = open("/dev/tty", O_RDONLY);
		if (tty_fd == -1)
			exit(1); */
		while (1)
		{
			//dup2(tty_fd, STDIN_FILENO);
			line = readline("> ");
			if (!line || (ft_strncmp(line, io->file, ft_strlen(io->file)) == 0
					&& ft_strlen(line) == ft_strlen(io->file)))
			{
				free(line);
				break ;
			}
			write(fd[1], line, ft_strlen(line));
			if (line[0] != '\0')
				write(fd[1], "\n", 1);
			free(line);
		}
		close(fd[1]);
		close_fds(0);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		close(fd[1]);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			write(1, "\n", 1);
			g_exit_status = 130;
			close(fd[0]);
			return ;
		}
		signal(SIGINT, handle_sigint);
		if (dup2(fd[0], STDIN_FILENO) == -1)
		{
			close(fd[0]);
			return ;
		}
	}
}

void prepare_heredocs(t_tree *node, t_info *info)
{
	int i;

	if (!node)
		return;
	if (node->type == CMD && node->args)
	{
		i = 0;
		while (node->args[i])
		{
			if (ft_strncmp(node->args[i], "<<", 2) == 0)
			{
				if (!node->args[i + 1])
				{
					ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
					g_exit_status = 2;
					return;
				}
				update_io_file(info->io, node->args[i + 1]);
				handle_heredoc_redirection(info->io);
				remove_redir_tokens(node->args, i);
				i = -1;
			}
			i++;
		}
	}
	prepare_heredocs(node->left, info);
	prepare_heredocs(node->right, info);
}
