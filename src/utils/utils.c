/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:55:33 by raamorim          #+#    #+#             */
/*   Updated: 2025/04/23 15:40:22 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

/* static void	*my_malloc(size_t size)
{
	int malloc_fail_counter = 0; // Número de chamadas antes de falhar
	if (--malloc_fail_counter <= 0)
	{
		return (NULL); // Força falha de alocação
	}
	return (malloc(size));
}

static void	check_open_fds(void)
{
	int	fd;

	// F_GETFD retorna -1 se o FD não está em uso
	for (fd = 3; fd < 1024; ++fd)
	{
		if (fcntl(fd, F_GETFD) != -1)
		{
			printf("\nFD %d is still open\n", fd);
		}
	}
} */

void	close_fds(int i)
{
	i = 3;
	while (i < FOPEN_MAX)
	{
		close(i);
		i++;
	}
}

void	close_pipe_fds(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	error_exit(char *msg)
{
	if (!msg)
		perror("Error\n");
	else
		perror(msg);
	close_fds(0);
	rl_clear_history();
	exit(EXIT_FAILURE);
}

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}


void	clean(t_info *info)
{
	if (!info)
		return ;
	if (info->cmd_tree->args)
		free_arr(info->cmd_tree->args);
	if (info->flags)
		free(info->flags);
	// if (info->builtins)
	// {
	// 	free_arr(info->builtins->builtins);
	// 	free(info->builtins->f);
	// 	free(info->builtins);
	// }
	close_fds(3);
	rl_clear_history();
}

void	free_tree(t_tree *node)
{
	if (!node)
		return ;
	if (node->args)
		free_arr(node->args);
	if (node->left)
		free_tree(node->left);
	if (node->right)
		free_tree(node->right);
	if (node)
		free(node);
}

void	free_types(t_types *types)
{
	if (!types)
		return ;
	free(types);
}