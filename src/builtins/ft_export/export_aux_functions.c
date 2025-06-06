/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_aux_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:23:13 by rafael            #+#    #+#             */
/*   Updated: 2025/06/06 15:40:26 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	handle_regular_assignment(t_info *info, char *arg)
{
	char	*dup;

	dup = ft_strdup(arg);
	if (!dup)
		return ;
	format_str(&dup);
	if (!check_env(&info->my_env, dup))
		add_to_env(&info->my_env, dup);
	if (!check_env(&info->export_env, dup))
		add_to_env(&info->export_env, dup);
	free(dup);
}

void	handle_plus_assignment(t_info *info, char *arg)
{
	add_check(&info->my_env, arg);
	add_check(&info->export_env, arg);
}

static int	concat_and_update(char ***arr, int i, char *val)
{
	char	*tmp;
	char	*final;

	tmp = ft_strjoin((*arr)[i], val);
	if (!tmp)
		return (-1);
	free((*arr)[i]);
	final = remove_quotes(tmp);
	free(tmp);
	format_str(&final);
	(*arr)[i] = final;
	return (1);
}

static int	add_equal(char **var)
{
	char	*tmp;

	if (ft_strchr(*var, '=') != NULL)
		return (1);
	tmp = ft_strjoin(*var, "=");
	if (!tmp)
		return (-1);
	free(*var);
	*var = tmp;
	return (1);
}

void	add_check(char ***arr, char *str)
{
	char	*name;
	char	*value;
	int		index;

	name = reverse_strchr(str, '+');
	if (!name)
		return ;
	value = ft_strchr(str, '=');
	if (!value)
		return (free(name));
	value++;
	index = find_index(*arr, name);
	if (index == -1)
	{
		create_var(arr, str);
		free(name);
		return ;
	}
	if (add_equal(&(*arr)[index]) == -1)
		return (free(name));
	if (concat_and_update(arr, index, value) == -1)
		return (free(name));
	free(name);
}
