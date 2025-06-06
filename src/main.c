/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:55:41 by raamorim          #+#    #+#             */
/*   Updated: 2025/06/06 00:09:07 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shellinho.h"

static int	is_input_valid(char *input)
{
	int	i;

	if (!input)
		return (0);
	i = 0;
	while (input[i])
	{
		if (!is_space(input[i]))
			return (1);
		i++;
	}
	return (0);
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
		set_signals_interactive();
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
	signal(SIGPIPE, SIG_IGN);
	copy_env(&info.my_env, env);
	change_shlvl(&info.my_env, "SHLVL");
	init(&info);
	start(&info);
	free_arr(info.my_env);
	free_builtins(info.builtins);
	return (0);
}
