/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:56:17 by raamorim          #+#    #+#             */
/*   Updated: 2025/06/06 15:40:26 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	add_to_env(char ***env, char *str)
{
	int		i;
	char	**new_env;

	i = 0;
	while ((*env) && (*env)[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	i = 0;
	while ((*env) && (*env)[i])
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
}

void	sort_env(char **args)
{
	int		i;
	char	*temp;
	int		sorted;
	int		len;

	sorted = 0;
	while (!sorted)
	{
		i = 0;
		sorted = 1;
		while (args[i])
		{
			len = ft_strlen(args[i]);
			if (ft_strncmp(args[i], args[i + 1], len) > 0)
			{
				temp = args[i];
				args[i] = args[i + 1];
				args[i + 1] = temp;
				sorted = 0;
			}
			i++;
		}
		len--;
	}
}

char	**create_sorted_env_copy(char **env)
{
	int		i;
	char	**copy;

	i = 0;
	while (env && env[i])
		i++;
	copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (env && env[i])
	{
		copy[i] = ft_strdup(env[i]);
		i++;
	}
	copy[i] = NULL;
	sort_env(copy);
	return (copy);
}

static void	print_sorted_env(char **env)
{
	int		i;
	char	**copy;

	copy = create_sorted_env_copy(env);
	if (!copy)
		return ;
	i = 0;
	while (copy[i])
	{
		printf("declare -x %s\n", copy[i]);
		free(copy[i]);
		i++;
	}
	free(copy);
}

void	ft_export(t_info *info)
{
	int	i;
	int	exit_status;

	exit_status = 0;
	i = 1;
	check_redirections(info);
	check_operators(info);
	if (!info->cmd_tree->args[i])
		return (print_sorted_env(info->export_env));
	while (info->cmd_tree->args[i])
	{
		if (!check_valid_input(info->cmd_tree->args[i], &exit_status))
		{
			i++;
			continue ;
		}
		if (check_equal_plus(info->cmd_tree->args[i]))
			handle_plus_assignment(info, info->cmd_tree->args[i]);
		else if (check_equal_sign(info->cmd_tree->args[i]))
			handle_regular_assignment(info, info->cmd_tree->args[i]);
		else if (!check_env(&info->export_env, info->cmd_tree->args[i]))
			add_to_env(&info->export_env, info->cmd_tree->args[i]);
		i++;
	}
	update_status(info, exit_status);
}
