/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:49:01 by rafael            #+#    #+#             */
/*   Updated: 2025/07/03 04:36:39 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	dup_and_close_fd(int fd, int std_fd, const char *err_msg)
{
	if (dup2(fd, std_fd) == -1)
	{
		perror(err_msg);
		exit(1);
	}
	close(fd);
}

void	cleanup_and_exit(t_info *info)
{
	info->exit_status = 0;
	ft_exit(info);
}

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

void	storing_backup(t_io *io)
{
	io->stdin_backup = dup(STDIN_FILENO);
	if (io->stdin_backup == -1)
		ft_putstr_fd("dup stdin backup failed", 2);
	io->stdout_backup = dup(STDOUT_FILENO);
	if (io->stdout_backup == -1)
		ft_putstr_fd("dup stdout backup failed", 2);
}
