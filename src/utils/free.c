/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:40:05 by dsteiger          #+#    #+#             */
/*   Updated: 2025/06/06 15:40:26 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (node->io)
	{
		if (node->io->file)
			free(node->io->file);
		free(node->io);
	}
	if (node)
		free(node);
	node = NULL;
}

void	free_io_file(t_io *io)
{
	if (io->file)
	{
		free(io->file);
		io->file = NULL;
	}
}

void	free_builtins(t_builtins *builtins)
{
	if (!builtins)
		return ;
	free(builtins);
	builtins = NULL;
}

void	*free_str(char **dest, int i)
{
	while (i >= 0)
		free(dest[i--]);
	free(dest);
	return (NULL);
}
