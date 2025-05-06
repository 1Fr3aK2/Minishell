/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:53:49 by rafael            #+#    #+#             */
/*   Updated: 2025/05/06 20:28:09 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shellinho.h"

int	get_varname_len(char *str)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '$')
		{
			i++;
			if (str[i] == '?')
				return (i);
			start = i;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			return (i - start);
		}
		i++;
	}
	return (0);
}

char	*get_var_name(char *str, int *i)
{
	char	*var_name;

	if (!str || !i || *i < 0)
		return (NULL);
	var_name = ft_substr(str, *i, get_varname_len(str));
	if (!var_name)
	{
		if (var_name)
			free(var_name);
		return (NULL);
	}
	return (var_name);
}

int	size_to_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '$')
			return (i);
		i++;
	}
	return (i);
}
