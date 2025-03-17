/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:43:04 by raamorim          #+#    #+#             */
/*   Updated: 2025/03/17 11:56:40 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

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

static t_tree	*creat_op_node(char **tokens, int *index)
{
	t_tree	*node;
	char	**left_tokens;
	char	**right_tokens;
	int		total;

	if (!tokens)
		return (NULL);
	total = 0;
	while (tokens[total])
		total++;
	left_tokens = NULL;
	right_tokens = NULL;
	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->type = find_type(tokens, *index);
	printf("Creating operator node. Operator: %s, Type: ", tokens[*index]);
	print_node_type(node->type);
	printf("\n");
	node->args = malloc(sizeof(char *) * 2);
	if (!node->args)
	{
		free(node);
		return (NULL);
	}
	node->args[0] = ft_strdup(tokens[*index]);
	node->args[1] = NULL;
	printf("Operator '%s' copied to args\n", node->args[0]);
	left_tokens = sub_tokens(tokens, 0, *index);
	printf("Left tokens for operator '%s':\n", tokens[*index]);
	for (int i = 0; left_tokens[i] != NULL; i++)
		printf("  %s\n", left_tokens[i]);
	node->left = parse_tokens(left_tokens);
	free_arr(left_tokens);
	right_tokens = sub_tokens(tokens, *index + 1, total);
	printf("Right tokens for operator '%s':\n", tokens[*index]);
	for (int i = 0; right_tokens[i] != NULL; i++)
		printf("  %s\n", right_tokens[i]);
	node->right = parse_tokens(right_tokens);
	free_arr(right_tokens);
	return (node);
}

static t_tree	*create_node(char **tokens)
{
	t_tree	*node;
	int		total;
	int		i;

	if (!tokens)
		return (NULL);
	total = 0;
	i = -1;
	while (tokens[total])
		total++;
	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->type = CMD;
	node->args = malloc(sizeof(char *) * (total + 1));
	if (!node->args)
		return (free(node), NULL);
	while (++i < total)
		node->args[i] = ft_strdup(tokens[i]);
	node->args[total] = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_tree	*parse_tokens(char **tokens)
{
	int		op_index;
	int		total;
	t_tree	*node;

	op_index = -1;
	total = 0;
	node = NULL;
	if (!tokens)
		return (NULL);
	while (tokens[total])
		total++;
	op_index = search_ops(tokens);
	if (op_index != -1)
		node = creat_op_node(tokens, &op_index);
	else
		node = create_node(tokens);
	return (node);
}
