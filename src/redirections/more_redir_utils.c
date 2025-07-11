/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_redir_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:01:40 by dsteiger          #+#    #+#             */
/*   Updated: 2025/07/11 17:16:22 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc_loop(t_io *io, t_info *info, int fd[2])
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			info->exit_status = 130;
			ft_exit(info);
		}
		if (ft_strncmp(line, io->file, ft_strlen(io->file)) == 0
			&& ft_strlen(line) == ft_strlen(io->file))
		{
			print_heredoc_eof(io, line);
			free(line);
			break ;
		}
		if (io->quoted)
			ft_putendl_fd(line, fd[1]);
		else
			process_line(line, info, fd[1]);
		free(line);
	}
}

int	setup_heredoc_io(t_tree *node, t_info *info, int i)
{
	char	*temp;

	if (!node->io)
	{
		node->io = malloc(sizeof(t_io));
		if (!node->io)
			return (-1);
		init_io(node->io);
	}
	update_io_file(node->io, node->args[i + 1]);
	node->io->quoted = has_quotes(node->args[i + 1]);
	temp = remove_quotes(node->args[i + 1]);
	free(node->io->file);
	node->io->file = temp;
	handle_heredoc_redirection(node->io, info);
	return (1);
}
