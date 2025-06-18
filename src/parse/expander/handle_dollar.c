/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:39:56 by raamorim          #+#    #+#             */
/*   Updated: 2025/06/18 08:24:09 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*join_and_free(char *s1, char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	free(s1);
	return (new);
}

static int	process_variable(char *str, char **new, int i, t_info *info)
{
	char	*var_name;
	char	*var_value;
	char	*temp;
	int		len;

	var_name = expand(str + i);
	if (!var_name)
		return (-1);
	if (var_name[0] == '\0')
		var_value = ft_strdup("$");
	else
		var_value = translate(var_name, info->my_env, info);
	len = get_varname_len(str + i) + 1;
	free(var_name);
	if (!var_value || var_value[0] == '\0')
		return (free(var_value), i + len);
	temp = join_and_free(*new, var_value);
	free(var_value);
	if (!temp)
	{
		free(*new);
		return (-1);
	}
	*new = temp;
	return (i + len);
}


static int	handle_loop(char *str, char **new, int *i, t_info *info)
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
		j = process_variable(str, new, *i, info);
		if (j == -1)
			return (-1);
		*i = j;
	}
	return (0);
}

char	*handle_dollar(char *str, t_info *info)
{
	char	*new;
	int		i;
	int		j;

	if (!check_translate(str))
		return (ft_strdup(str));
	new = ft_strdup("");
	if (!new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			j = process_variable(str, &new, i, info);
			if (j == -1)
				return (free(new), NULL);
			if (j == 0) // variável vazia -> liberamos new e retornamos NULL
				return (free(new), NULL);
			i = j;
		}
		else
		{
			if (handle_loop(str, &new, &i, info) == -1)
				return (free(new), NULL);
		}
	}
	return (new);
}

