/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:26:00 by dsteiger          #+#    #+#             */
/*   Updated: 2025/03/31 18:16:02 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

static bool has_equal_sign(char *str)
{
    int i = 0;
    if (!str)
        return false;
    while (str[i])
    {
        if (str[i] == '=')
            return true;
        i++;
    }
    return false;
}

static bool check_env(char **env, char *str)
{
    int i;
    char *new_str;
	
	i = 0;
    if (!env || !*env || !str)
        return false;
    while (env[i])
    {
        if (ft_strncmp(str, env[i], ft_strlen(str) - ft_strlen(ft_strrchr(str, '='))) == 0)
        {
            free(env[i]);
            new_str = ft_strdup(str);
            env[i] = new_str;
            return true;
        }
        i++;
    }
    return false;
}

void add_to_env(char ***env, char *str)
{
    int i;
    char **new_env;
	
	i = 0;
    while ((*env) && (*env)[i])
        i++;
    new_env = (char **)malloc(sizeof(char *) * (i + 2));
    if (!new_env)
        return;
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

char **create_sorted_env_copy(char **env)
{
    int i = 0;
    char **copy;
    while (env && env[i])
        i++;
    copy = (char **)malloc(sizeof(char *) * (i + 1));
    if (!copy)
        return NULL;
    i = 0;
    while (env && env[i])
    {
        copy[i] = ft_strdup(env[i]);
        i++;
    }
    copy[i] = NULL;
    sort_env(copy);
    return copy;
}

static char **copy_myenv(char **my_env, char *str)
{
	int i;
	char **new_env = NULL;
	
	if (!my_env || !str)
		return (NULL);
	i = 0;
	while(my_env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_env)
	{
		return (NULL);
	}
	i = 0;
	while(my_env[i])
	{
		new_env[i] = ft_strdup(my_env[i]);
		if (!new_env[i])
			return (NULL);
		i++;
	}
	new_env[i] = ft_strdup(str);
	if (!new_env[i])
		return (NULL);
	new_env[++i] = NULL;
	while(new_env[i])
	{
		printf("%s\n", new_env[i]);
		i++;
	}
	return (new_env);	
}


void ft_export(t_info *info)
{
    char **sorted_env;
    int i = 1;

    if (info->cmd_tree->args[i] != NULL)
    {
        while (info->cmd_tree->args[i])
        {
            if (has_equal_sign(info->cmd_tree->args[i]))
            {
                if (!check_env(info->my_env, info->cmd_tree->args[i]))
                    add_to_env(&(info->my_env), info->cmd_tree->args[i]);
				info->export_env = copy_myenv(info->my_env, info->cmd_tree->args[i]);
            }
            else
            {
                if (!check_env(info->export_env, info->cmd_tree->args[i]))
                    add_to_env(&(info->export_env), info->cmd_tree->args[i]);
            }
            i++;
        }
    }
    else
    {
        if (info->export_env)
            sorted_env = create_sorted_env_copy(info->export_env);
        else
            sorted_env = create_sorted_env_copy(info->my_env);

        if (!sorted_env)
            return;

        i = 0;
        while (sorted_env[i])
        {
            printf("declare -x %s\n", sorted_env[i]);
            free(sorted_env[i]);
            i++;
        }
        free(sorted_env);
    }
}
