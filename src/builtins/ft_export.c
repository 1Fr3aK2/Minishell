/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:56:17 by raamorim          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2025/05/05 16:23:29 by rafael           ###   ########.fr       */
=======
/*   Updated: 2025/04/23 17:37:40 by rafael           ###   ########.fr       */
>>>>>>> Stashed changes
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
	int i;
	char *equal_pos;
	size_t name_len;
	
	i = 0;
	if (!env || !*env || !str)
		return (false);
	name_len = 0;
	equal_pos = ft_strchr(str, '=');
	if (equal_pos)
		name_len = equal_pos - str;
	else	
		name_len = ft_strlen(str);
	while ((*env)[i])
	{
		if (ft_strncmp(str, (*env)[i], name_len) == 0
			&& ((*env)[i][name_len] == '=' || (*env)[i][name_len] == '\0'))
		{
			if (equal_pos)
			{
				free((*env)[i]);
				(*env)[i] = ft_strdup(str);
			}
			return (true);
		}
		i++;
	}
	return (false);
}

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

static void format_str(char **str)
{
    char *value;
    char *new;
    int key_len;
	int total_len;

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

static bool check_plus_sign(char *str)
{
	if (!str)
		return (false);
	int i;
	i = 0;
	while(str[i])
	{
		if (str[i] && str[i] == '+')
		{
			if (str[i + 1] && str[i + 1] == '=')
				return (true);
			return (false);
		}
		i++;			
	}
	return (false);
}

bool check_valid_input(char *str, int *exit)
{
	if (!str)
		return (false);
	if (*str == '\0' || *str == '=' || *str == '+'|| ft_isdigit(*str) == 1 || check_pos(str, '-') || check_pos(str, '.')
		|| check_pos(str, ':') || check_pos(str, ',') || check_pos(str, '\\') || check_pos(str, '!') || check_pos(str, '?') || (ft_strchr(str, '+') && !check_plus_sign(str)))
	{
		ft_putstr_fd("shellinho: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		*exit = 1;
		return (false);
	}
	else if (*str == '_' && (*(str + 1) == '\0' || *(str + 1) == '='))
		return (false);
	return (true);
}

char *reverse_strchr(char *str, int c)
{
	char *pos;
	char *new;
	int len;

	if (!str)
		return NULL;
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


int find_index(char **arr, char *str)
{
	int i;

	if (!arr || !str)
		return (-1);
	i = 0;
	while (arr[i])
	{
		if (ft_strncmp(str, arr[i], ft_strlen(str)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void create_var(char ***env, char *str)
{
	int len;
	char *new_str;
	char *var_name;
	char *var_value;

	var_name = reverse_strchr(str, '+');
	var_value = ft_strchr(str, '=');
	if (!var_name || !var_value)
		return ;
	len = ft_strlen(var_name) + ft_strlen(var_value) + 1;
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
	{
		free(var_name);
		return;
	}
	new_str[0] = '\0';
	ft_strlcpy(new_str, var_name, ft_strlen(var_name) + 1);
	ft_strlcat(new_str, var_value, len + 1);
	format_str(&new_str);
	add_to_env(env, new_str);
	free(new_str);
	free(var_name);
}

void add_check(char ***arr, char *str)
{
    char *var_name;
    char *temp;
	char *var_value;
	char *new_var;
    int i;

    var_name = reverse_strchr(str, '+');
	if (!var_name)
		return ;
	var_value = ft_strchr(str, '=');
	if (!var_value)
        return (free(var_name));
	var_value++;
    i = find_index(*arr, var_name);
    if (i == -1)
	{
		create_var(arr, str);
		free(var_name);
		return ;
	}
    temp = ft_strjoin((*arr)[i], var_value);
    if (!temp)
        return (free(var_name));
    free((*arr)[i]);
	new_var = remove_quotes(temp);
	free(temp);
	format_str(&new_var);
    (*arr)[i] = new_var;
    free(var_name);
}


void	ft_export(t_info *info)
{
	char	**sorted_env;
	int		exit;
	int		i;
	
	sorted_env = NULL;
	i = 1;
	exit = 0;
	check_redirections(info);
<<<<<<< Updated upstream
	check_operators(info);
=======
>>>>>>> Stashed changes
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
				if (check_plus_sign(info->cmd_tree->args[i]) == true)
				{
					add_check(&info->my_env, info->cmd_tree->args[i]);
        			add_check(&info->export_env, info->cmd_tree->args[i]);
					i++;
					continue;
				}
    			format_str(&info->cmd_tree->args[i]);
				if (check_env(&info->my_env, info->cmd_tree->args[i]) == false)
    			{
        			add_to_env(&(info->my_env), info->cmd_tree->args[i]);
					if (check_env(&info->export_env, info->cmd_tree->args[i]) == false)
						add_to_env(&(info->export_env), info->cmd_tree->args[i]);
				}
    			else
    			{
        			if (check_env(&info->export_env, info->cmd_tree->args[i]) == false)
						add_to_env(&(info->export_env), info->cmd_tree->args[i]);
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
	g_exit_status = exit;
}

//env nao tem aspas ao contrario de export 