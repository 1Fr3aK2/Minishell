/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:52:25 by dsteiger          #+#    #+#             */
/*   Updated: 2025/07/07 18:57:59 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	restore_io(t_io *io)
{
	if (!io)
		return ;
	close_and_reset(&io->heredoc_fd);
	if (io->stdin_backup != -1)
	{
		dup2(io->stdin_backup, STDIN_FILENO);
		close_and_reset(&io->stdin_backup);
	}
	if (io->stdout_backup != -1)
	{
		dup2(io->stdout_backup, STDOUT_FILENO);
		close_and_reset(&io->stdout_backup);
	}
	close_and_reset(&io->fd_in);
	close_and_reset(&io->fd_out);
	io->stdin_is_heredoc = 0;
}

void	restore_redirections(int saved_in, int saved_out)
{
	if (saved_in != -1)
	{
		dup2(saved_in, STDIN_FILENO);
		close(saved_in);
	}
	if (saved_out != -1)
	{
		dup2(saved_out, STDOUT_FILENO);
		close(saved_out);
	}
}

void	handle_redir_error(t_info *info)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
		2);
	info->exit_status = 258;
	exit(258);
}

void	print_heredoc_eof(t_io *io, char *line)
{
	if (ft_strncmp(line, io->file, ft_strlen(io->file)) == 0
		&& ft_strlen(line) == ft_strlen(io->file))
		return ;
	else
		ft_putendl_fd("minishell: warning: here-document delimited by"
			" end-of-file", 2);
}

void	process_line(char *line, t_info *info, int fd)
{
	char	*temp;

	temp = handle_dollar(line, info);
	if (!temp)
		temp = ft_strdup("");
	ft_putendl_fd(temp, fd);
	free(temp);
}
