/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:56:17 by raamorim          #+#    #+#             */
/*   Updated: 2025/04/03 03:40:47 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

static bool	check_equal_sign(char *str)
{
	int	i;

	if (!str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

static bool	check_env(char ***env, char *str)
{
	int		i;
	char	*name;

	i = 0;
	if (!env || !*env || !str)
		return (false);
	while ((*env)[i])
	{
		if (check_equal_sign(str) == true)
		{
			if (ft_strncmp(str, (*env)[i], ft_strlen(str)
					- ft_strlen(ft_strrchr(str, '='))) == 0)
			{
				if (ft_strncmp(str, (*env)[i], ft_strlen(str)) == 0
					&& (ft_strlen(str) == ft_strlen((*env)[i])))
					return (true);
				else
				{
					free((*env)[i]);
					name = ft_strdup(str);
					(*env)[i] = name;
					return (true);
				}
			}
		}
		else
		{
			if (ft_strncmp(str, (*env)[i], ft_strlen(str) == 0))
				return (true);
		}
		i++;
	}
	return (false);
} // dar fix no else export teste=teste || export te . || export te=teste .

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

static char	**copy_myenv(char ***my_env, char *str)
{
	int		i;
	char	**new_env;

	new_env = NULL;
	if (!my_env || !str)
		return (NULL);
	i = 0;
	while ((*my_env)[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while ((*my_env)[i])
	{
		new_env[i] = ft_strdup((*my_env)[i]);
		if (!new_env[i])
			return (NULL);
		i++;
	}
	new_env[i] = NULL;
	while (new_env[i])
	{
		printf("%s\n", new_env[i]);
		i++;
	}
	return (new_env);
}

static void format_str(char **str)
{
    char *value;
    char *new;
    int key_len, total_len;

    if (!str || !*str)
        return;
    value = ft_strchr(*str, '=');
    if (!value)
        return;
    key_len = value - *str + 1;
    value++;
    total_len = key_len + ft_strlen(value) + 3;
    new = (char *)malloc(sizeof(char) * total_len);
    if (!new)
        return;
    ft_strlcpy(new, *str, key_len + 1);
    ft_strlcat(new, "\"", total_len);
    ft_strlcat(new, value, total_len);
    ft_strlcat(new, "\"", total_len);
    free(*str);
    *str = new;
}

static bool check_pos(char *str, char c)
{
	if (!str)
		return (false);	
	if ((ft_strchr(str, c) && (ft_strchr(str, c) < ft_strchr(str, '=')))  
		|| (ft_strchr(str, c) && !ft_strchr(str, '=')))
		return (true);
	return (false);
}

bool check_valid_input(char *str, int *exit)
{
	if (!str)
		return (false);
	if (*str == '\0' || *str == '=' || ft_isdigit(*str) == 1 || check_pos(str, '-') || check_pos(str, '.')
		|| check_pos(str, ':') || check_pos(str, ',') || check_pos(str, '\\') || check_pos(str, '!') || check_pos(str, '?'))
	{
		ft_putstr_fd("shellinho: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		*exit = 1;
		return (false);
	}
	/* else if (*str == '_' && (*str + 1 == '\0' || *str + 1 == '='))
		return (false); */
	return (true);
}
//fix export _=T 
//fazer add export (export teste+=teste) adiciona o que vem a seguir ao igual ao que ja existe
void	ft_export(t_info *info)
{
	char	**sorted_env;
	int		exit;
	int		i;
	
	sorted_env = NULL;
	i = 1;
	exit = 0;
	if (info->cmd_tree->args[i] != NULL)
	{
		while (info->cmd_tree->args[i])
		{
			if (!check_valid_input(info->cmd_tree->args[i], &exit))
			{
	 			i++;
				continue;
			}
			if (check_equal_sign(info->cmd_tree->args[i]) == true)
			{
                format_str(&info->cmd_tree->args[i]);
				if (check_env(&info->my_env, info->cmd_tree->args[i]) == false)
				{
					add_to_env(&(info->my_env), info->cmd_tree->args[i]);
					if (check_env(&info->export_env,
							info->cmd_tree->args[i]) == false)
					{
						free_arr(info->export_env);
						info->export_env = copy_myenv(&info->my_env,
								info->cmd_tree->args[i]);
						if (!info->export_env)
							return ;
					}
				}
				else
				{
					free_arr(info->export_env);
					info->export_env = copy_myenv(&info->my_env,
							info->cmd_tree->args[i]);
					if (!info->export_env)
						return ;
				}
			}
			else
			{
				if (check_env(&info->export_env,
						info->cmd_tree->args[i]) == false)
					add_to_env(&(info->export_env), info->cmd_tree->args[i]);
			}
			i++;
		}
	}
	else
	{
		sorted_env = create_sorted_env_copy(info->export_env);
		if (!sorted_env)
			return ;
		i = 0;
		while (sorted_env[i])
		{
			printf("declare -x %s\n", sorted_env[i]);
			free(sorted_env[i]);
			i++;
		}
		free(sorted_env);
	}
	exit_status = exit;
}
