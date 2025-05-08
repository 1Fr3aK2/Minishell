/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:28:54 by rafael            #+#    #+#             */
/*   Updated: 2025/05/08 04:20:31 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shellinho.h"

void	format_str(char **str)
{
	char	*value;
	char	*new;
	int		key_len;
	int		total_len;

	if (!str || !*str)
		return ;
	value = ft_strchr(*str, '=');
	if (!value)
		return ;
	key_len = value - *str + 1;
	value++;
	total_len = key_len + ft_strlen(value) + 3;
	new = (char *)malloc(sizeof(char) * total_len);
	if (!new)
		return ;
	ft_strlcpy(new, *str, key_len + 1);
	ft_strlcat(new, "\"", total_len);
	ft_strlcat(new, value, total_len);
	ft_strlcat(new, "\"", total_len);
	free(*str);
	*str = new;
}

bool	check_pos(char *str, char c)
{
	if (!str)
		return (false);
	if ((ft_strchr(str, c) && (ft_strchr(str, c) < ft_strchr(str, '=')))
		|| (ft_strchr(str, c) && !ft_strchr(str, '=')))
		return (true);
	return (false);
}

int	find_index(char **arr, char *str)
{
	int	i;

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

void	create_var(char ***env, char *str)
{
	int		len;
	char	*new_str;
	char	*var_name;
	char	*var_value;

	var_name = reverse_strchr(str, '+');
	var_value = ft_strchr(str, '=');
	if (!var_name || !var_value)
		return ;
	len = ft_strlen(var_name) + ft_strlen(var_value) + 1;
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (free(var_name));
	new_str[0] = '\0';
	ft_strlcpy(new_str, var_name, ft_strlen(var_name) + 1);
	ft_strlcat(new_str, var_value, len + 1);
	format_str(&new_str);
	add_to_env(env, new_str);
	free(new_str);
	free(var_name);
}

bool	check_env(char ***env, char *str)
{
	int		i;
	char	*equal_pos;
	size_t	name_len;

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
