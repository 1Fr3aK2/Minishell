/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:55:41 by raamorim          #+#    #+#             */
/*   Updated: 2025/03/24 17:59:07 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shellinho.h"

unsigned int		exit_status = 0;

void	start(t_info *info)
{
	char	*input;

	while (1)
	{
		input = readline("shellinho$> ");
		if (!input)
		{
			handle_ctrl_d(info);
			rl_clear_history();
			return ;
		}
		if (*input)
			add_history(input);
		if (info->cmd_tree)
		{
			free_tree(info->cmd_tree);
			info->cmd_tree = NULL;
		}
		parse(input, info);
		if (!info->cmd_tree->args || !info->cmd_tree->args[0])
		{
			free(input);
			continue ;
		}
		child_process(info);
		free(input);
	}
	rl_clear_history();
}

void	free_builtins(t_builtins *builtins)
{
	if (!builtins)
		return ;
	free(builtins);
}

int	main(int argc, char **argv, char **env)
{
	t_info	info;

	(void)argc;
	(void)argv;
	init(&info, env);
	set_signals();
	start(&info);
	free_arr(info.my_env);
	free_builtins(info.builtins);
	return (0);
}
