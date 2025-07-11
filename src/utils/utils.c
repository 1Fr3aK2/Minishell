/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:55:33 by raamorim          #+#    #+#             */
/*   Updated: 2025/07/11 04:41:24 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*reverse_strchr(char *str, int c)
{
	char	*pos;
	char	*new;
	int		len;

	if (!str)
		return (NULL);
	pos = ft_strchr(str, c);
	if (!pos)
		return (NULL);
	len = pos - str;
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	ft_strncpy(new, str, len);
	new[len] = '\0';
	return (new);
}

void	change_shlvl(char ***env, char *name)
{
	int		i;
	char	*value;
	char	*new_val;

	if (!env || !*env)
		return ;
	i = 0;
	value = (ft_itoa(ft_atoi(get_env(name, *env)) + 1));
	if (!value)
		return ;
	new_val = ft_strjoin("SHLVL=", value);
	free(value);
	if (!new_val)
		return ;
	while ((*env)[i])
	{
		if (ft_strncmp("SHLVL=", (*env)[i], ft_strlen("SHLVL=")) == 0)
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup(new_val);
		}
		i++;
	}
	free(new_val);
}

void	ft_exit2(t_info *info)
{
	free_tree(info->cmd_tree);
	free_builtins(info->builtins);
	free_arr(info->my_env);
	free_arr(info->export_env);
	free(info->io);
	free(info->redirections);
	rl_clear_history();
	close_fds(0);
	exit(info->exit_status);
}

int	needs_retokenization(char *original, char *expanded)
{
	int	i;

	if (!original || !expanded)
		return (0);
	if (original[0] == '"' || original[0] == '\'')
		return (0);
	i = 0;
	while (original[i])
	{
		if (original[i] == ' ' || original[i] == '\t')
			return (0);
		i++;
	}
	i = 0;
	while (expanded[i])
	{
		if (expanded[i] == ' ' || expanded[i] == '\t')
			return (1);
		i++;
	}
	return (0);
}

int	count_total_tokens(char **args, char **temp, int idx)
{
	int	total;
	int	i;

	total = 0;
	while (temp[total])
		total++;
	i = 0;
	while (args[i])
	{
		if (i != idx)
			total++;
		i++;
	}
	return (total);
}
