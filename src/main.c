/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:55:41 by raamorim          #+#    #+#             */
/*   Updated: 2025/03/17 10:36:26 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shellinho.h"

int		command_running = 0;

void	start(t_info *info)
{
	char	*input;

	while (1)
	{
		rl_on_new_line(); // necessario??
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
void	print_banner(void)
{
    printf(GREEN
        "   _____ __  __________    __    _____   ____  ______ \n"
        "  / ___// / / / ____/ /   / /   /  _/ | / / / / / __ \\ \n"
        "  \\__ \\/ /_/ / __/ / /   / /    / //  |/ / /_/ / / / / \n"
        " ___/ / __  / /___/ /___/ /____/ // /|  / __  / /_/ /  \n"
        "/____/_/ /_/_____/_____/_____/___/_/ |_/_/ /_/\\____/   \n"
        "\n" RESET"\n");
}

int	main(int argc, char **argv, char **env)
{
	t_info	info;

	(void)argc;
	(void)argv;
	print_banner();
	init(&info, env);
	set_signals();
	start(&info);
	free_arr(info.my_env);
	free_builtins(info.builtins);
	return (0);
}
