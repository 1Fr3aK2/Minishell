/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:55:41 by raamorim          #+#    #+#             */
/*   Updated: 2025/02/20 18:13:09 by raamorim         ###   ########.fr       */
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
			add_history(input);
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
	start(&info);
	free_arr(info.args);
	free_arr(info.my_env);
	free_builtins(info.builtins);
	return (0);
}

// static char *handle_dollar(char *str, char **env)
// {
// 	int i = 0;
// 	char *teste;
// 	while(str)
// 	{
// 		if (str[i] && str[i] == '$')
// 		{
// 			teste = get_env(&str[++i],env);
// 			return(teste);
// 		}
//         i++;
// 	}
// 	return (NULL);	
// }