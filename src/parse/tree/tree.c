/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:43:04 by raamorim          #+#    #+#             */
/*   Updated: 2025/07/06 21:48:25 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	**sub_tokens(char **tokens, int start, int end)
{
	char	**sub;
	int		i;
	int		count;

	count = end - start;
	sub = malloc(sizeof(char *) * (count + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < count)
	{
		sub[i] = ft_strdup(tokens[start + i]);
		i++;
	}
	sub[count] = NULL;
	return (sub);
}

static int	handle_syntax_error(t_tree *node, char **tokens, t_info *info)
{
	if (info->error_msg == false)
		print_syntax_error_token(node, tokens, info);
	update_status(info, 2);
	if (node->right)
		free_tree(node->right);
	if (node->left)
		free_tree(node->left);
	if (node->args)
	{
		free(node->args[0]);
		free(node->args);
	}
	if (node->io)
	{
		free(node->io->file);
		free(node->io->redirections);
		free(node->io);
	}
	free(node);
	free_arr(tokens);
	return (1);
}

static t_tree	*init_node(char *token)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->io = malloc(sizeof(t_io));
	if (!node->io)
	{
		free(node);
		return (NULL);
	}
	init_io(node->io);
	node->args = malloc(sizeof(char *) * 2);
	if (!node->args)
	{
		free(node->io);
		free(node);
		return (NULL);
	}
	node->args[0] = ft_strdup(token);
	node->args[1] = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_tree	*creat_op_node(char **tokens, int *index, t_info *info)
{
	t_tree	*node;
	char	**left;
	char	**right;
	int		total;

	if (!tokens)
		return (NULL);
	total = 0;
	while (tokens[total])
		total++;
	node = init_node(tokens[*index]);
	if (!node)
		return (NULL);
	node->type = find_type(tokens, *index);
	left = sub_tokens(tokens, 0, *index);
	node->left = parse_tokens(left, info);
	free_arr(left);
	if (!node->left || !node->left->args || !node->left->args[0])
		return (handle_syntax_error(node, NULL, info), NULL);
	right = sub_tokens(tokens, *index + 1, total);
	node->right = parse_tokens(right, info);
	if (!node->right || !node->right->args || !node->right->args[0])
		return (handle_syntax_error(node, right, info), NULL);
	free_arr(right);
	return (node);
}

t_tree	*create_node(char **tokens)
{
	t_tree	*node;

	if (!tokens)
		return (NULL);
	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->io = alloc_io();
	if (!node->io)
	{
		free(node);
		return (NULL);
	}
	node->type = CMD;
	node->args = dup_args(tokens);
	if (!node->args)
	{
		free(node->io);
		free(node);
		return (NULL);
	}
	node->left = NULL;
	node->right = NULL;
	return (node);
}
