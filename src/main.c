/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:00:55 by raamorim          #+#    #+#             */
/*   Updated: 2025/02/11 15:51:42 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shellinho.h"

void	start(t_info *info)
{
	char	*input;

	while (1)
	{
		input = readline("shellinho$> ");
		if (!input)
		{
			rl_clear_history();
			return ;
		}
		if (*input)
			add_history(input); // add to history promt
		if (info->args)
		{
			free_arr(info->args);
			if (info->flags)
				free(info->flags);
			info->args = NULL;
		}
		parse(input, info);
		if (!info->args || !info->args[0])
		{
			free(input);
			continue ; // avoid NULL pointers
		}
		child_process(info);
		free(input);
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **env)
{
	t_info	info;

	// int i = 0;
	(void)argc;
	(void)argv;
	print_banner();
	init(&info, env);
	start(&info);
	free_arr(info.args);
	return (0);
}
