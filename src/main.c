/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:55:41 by raamorim          #+#    #+#             */
/*   Updated: 2025/04/25 03:59:07 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shellinho.h"

unsigned int	exit_status = 0;

void	start(t_info *info)
{
	char	*input;

	while (1)
	{
		input = readline("shellinho$> ");
		if (!input)
		{
			ft_exit(info);
		}
		if (!*input)
		{
			free(input);
			continue ;
		}
		if (*input)
			add_history(input);
		if (info->cmd_tree)
		{
			free_tree(info->cmd_tree);
			info->cmd_tree = NULL;
		}
		parse(input, info);
		if (!info->cmd_tree || !info->cmd_tree->args
			|| !info->cmd_tree->args[0])
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

void	change_shlvl(char ***env, char *name)
{
	int		i;
	char	*value;
	char	*new_val;

	if (!env || !*env)
		return ;
	i = 0;
	value = (ft_itoa(ft_atoi(get_env(name, *env)) + 1)); // value
	new_val = ft_strjoin("SHLVL=", value);
	free(value);
	while ((*env)[i])
	{
		if (ft_strncmp("SHLVL=", (*env)[i], ft_strlen("SHLVL=")) == 0)
		{
			free((*env)[i]);
			(*env)[i] = new_val;
		}
		i++;
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
