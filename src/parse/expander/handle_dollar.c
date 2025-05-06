/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:39:56 by raamorim          #+#    #+#             */
/*   Updated: 2025/05/06 17:18:55 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shellinho.h"

static char	*join_and_free(char *s1, char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	free(s1);
	return (new);
}

static int	process_variable(char *str, char **env, char **new, int i)
{
	char	*var_name;
	char	*var_value;
	char	*temp;

	var_name = expand(str + i);
	if (!var_name)
		return (-1);
	var_value = translate(var_name, env);
	if (!var_value)
		var_value = ft_strdup(" ");
	if (var_value)
	{
		temp = join_and_free(*new, var_value);
		if (!temp)
		{
			free(*new);
			return (-1);
		}
		*new = temp;
	}
	if (var_name)
		free(var_name);
	if (var_value)
		free(var_value);
	return (i + get_varname_len(str + i) + 1);
}

static int	handle_loop(char *str, char **env, char **new, int *i)
{
	char	*temp;
	int		j;

	temp = ft_substr(str, *i, size_to_var(str + *i));
	if (!temp)
		return (-1);
	*new = join_and_free(*new, temp);
	if (!*new)
		return (free(temp), -1);
	free(temp);
	*i += size_to_var(str + *i);
	if (str[*i] == '$')
	{
		j = process_variable(str, env, new, *i);
		if (j == -1)
			return (-1);
		*i = j;
	}
	return (0);
}

char	*handle_dollar(char *str, char **env)
{
	char	*new;
	int		i;

	if (!check_translate(str))
		return (ft_strdup(str));
	new = ft_strdup("");
	if (!new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (handle_loop(str, env, &new, &i) == -1)
			return (free(new), NULL);
	}
	return (new);
}
