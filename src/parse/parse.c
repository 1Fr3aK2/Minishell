/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:55:03 by raamorim          #+#    #+#             */
/*   Updated: 2025/03/24 15:14:49 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

int	size_woutquotes(char *str)
{
	int		i;
	char	quote;
	int		count;

	if (!str)
		return (-1);
	i = 0;
	quote = 0;
	count = 0;
	if (str[i] && is_quote(str[i]))
	{
		quote = str[i];
		i++;
	}
	while (str[i])
	{
		if (str[i] && str[i] != quote)
		{
			i++;
			count++;
		}
		else if (str[i] && str[i] == quote)
			i++;
	}
	return (count);
}

void	handle_quotes(char *str, char *new, int i, int *j)
{
	static int	in_quotes;
	static char	quote_char;

	if (in_quotes == 0)
	{
		in_quotes = 1;
		quote_char = str[i];
	}
	else if (str[i] == quote_char)
		in_quotes = 0;
	else
		new[(*j)++] = str[i];
}

char	**new_input(char *input)
{
	char	**new;

	if (count_quotes(input) == 0)
		return (custom_ft_split(input));
	if (check_quotes(input) == -1)
		return (printf("ERROR\n"), NULL);
	new = ft_split_quotes(input);
	if (!new)
		return (free_arr(new), NULL);
	return (new);
}

static void	check_dollar(char **args, t_info *info)
{
	int		i;
	char	*new;

	if (!info || !args)
		return ;
	i = 1;
	while (args[i])
	{
		new = handle_dollar(args[i], info->my_env);
		if (!new)
			return ;
		if (ft_strncmp(new, args[i], ft_strlen(args[i])) != 0)
		{
			free(args[i]);
			args[i] = new;
		}
		else
			free(new);
		i++;
	}
}
void print_node_type(t_node_type type)
{
	switch (type)
	{
		case AND:
		printf("AND");
		break;
		case PIPE:
		printf("PIPE");
		break;
		case OR:
		printf("OR");
		break;
		case CMD:
		printf("CMD");
		break;
		default:
		printf("UNKNOWN");
		break;
	}
}

t_tree *build_tree_tokens(char **tokens)
{
	if (!tokens)
		return (NULL);
	return (parse_tokens(tokens));
}

void print_tree(t_tree *node, int level)
{
    if (node == NULL)
        return;

    // Imprimir o nó direito
    print_tree(node->right, level + 1);

    // Imprimir o espaço para representar o nível da árvore
    for (int i = 0; i < level; i++)
        printf("\t");

    // Imprimir o tipo do nó
    printf("Type: ");
    print_node_type(node->type);

    // Imprimir os argumentos do nó, se existirem
    if (node->args != NULL)
    {
        printf(", Args: ");
        for (int i = 0; node->args[i] != NULL; i++)
        {
            printf("%s ", node->args[i]);
        }
    }

    printf("\n");

    // Imprimir o nó esquerdo
    print_tree(node->left, level + 1);
}

void parse(char *input, t_info *info)
{
	char **tokens;
    
	if (!input || !info)
        return;
    tokens = NULL;
	if (info->cmd_tree)
    {
        free_tree(info->cmd_tree);
    }
    tokens = new_input(input);
    if (!tokens)
        return;
    printf("Tokens after split:\n");
    for (int i = 0; tokens[i] != NULL; i++) {
        printf("Token[%d]: %s\n", i, tokens[i]);
    }
    check_dollar(tokens, info);
    remove_all_quotes(tokens);    
    info->cmd_tree = build_tree_tokens(tokens);
    if (info->cmd_tree)
    {
        printf("Binary Tree Structure:\n");
        print_tree(info->cmd_tree, 0);
    }
	info->flags = ft_strdup(info->cmd_tree->args[1]);
    free_arr(tokens);
}
