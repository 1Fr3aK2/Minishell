/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:55:41 by raamorim          #+#    #+#             */
/*   Updated: 2025/03/12 18:45:35 by dsteiger         ###   ########.fr       */
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
		if (info->args)
		{
			free_arr(info->args);
			// printf("ola1\n");
			if (info->flags)
				free(info->flags);
			info->args = NULL;
		}
		parse(input, info);
		if (!info->args || !info->args[0])
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
	print_banner();
	init(&info, env);
    set_signals();
	start(&info);
	free_arr(info.args);
	free_arr(info.my_env);
	free_builtins(info.builtins);
	return (0);
}
