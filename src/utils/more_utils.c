/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:01:35 by dsteiger          #+#    #+#             */
/*   Updated: 2025/06/06 15:48:02 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_io_file(t_io *io, char *filename)
{
	if (io->file)
	{
		free(io->file);
		io->file = NULL;
	}
	io->file = ft_strdup(filename);
	if (!io->file)
		return ;
}

void	remove_redir_tokens(char **args, int i)
{
	int	j;

	if (args[i])
	{
		free(args[i]);
		args[i] = NULL;
	}
	if (args[i + 1])
	{
		free(args[i + 1]);
		args[i + 1] = NULL;
	}
	j = i + 2;
	while (args[j])
	{
		args[i++] = args[j++];
	}
	args[i] = NULL;
}

int	is_valid_append_token(const char *token)
{
	int	count;

	count = 0;
	while (token[count] == '>')
		count++;
	return (count == 2);
}

/* void	handle_sigpipe(int sig)
{
	(void)sig;
	close_fds(0);
	exit(141);
}
 */
void	close_heredoc_fds(t_tree *node)
{
	if (!node)
		return ;
	if (node->io && node->io->heredoc_fd != -1)
	{
		close(node->io->heredoc_fd);
		node->io->heredoc_fd = -1;
	}
	close_heredoc_fds(node->left);
	close_heredoc_fds(node->right);
}
