/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:55:41 by raamorim          #+#    #+#             */
/*   Updated: 2025/05/14 16:50:46 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shellinho.h"

unsigned int	g_exit_status = 0;

static int	is_input_valid(char *input)
{
	return (input && *input);
}

static int	is_tree_invalid(t_info *info)
{
	return (!info->cmd_tree || !info->cmd_tree->args
		|| !info->cmd_tree->args[0]);
}

static void	reset_tree(t_info *info)
{
	if (info->cmd_tree)
	{
		free_tree(info->cmd_tree);
		info->cmd_tree = NULL;
	}
}

void	start(t_info *info)
{
	char	*input;

	while (1)
	{
		input = readline("shellinho$> ");
		if (!input)
			ft_exit(info);
		if (!is_input_valid(input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		reset_tree(info);
		parse(input, info);
		if (is_tree_invalid(info))
		{
			free(input);
			continue ;
		}
		child_process(info);
		free(input);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_info	info;

	(void)argc;
	(void)argv;
	copy_env(&info.my_env, env);
	change_shlvl(&info.my_env, "SHLVL");
	init(&info);
	set_signals();
	start(&info);
	free_arr(info.my_env);
	free_builtins(info.builtins);
	return (0);
}
