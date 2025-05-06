/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:39:52 by raamorim          #+#    #+#             */
/*   Updated: 2025/05/06 16:56:39 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shellinho.h"

char	*expand(char *str)
{
	int		i;
	char	*var_name;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '$')
		{
			i++;
			if (str[i] && str[i] == '?')
			{
				var_name = ft_substr(str, i, ft_strlen(str) - i);
				if (!var_name)
					return (NULL);
				return (var_name);
			}
			else
				return (get_var_name(str, &i));
		}
		i++;
	}
	return (NULL);
}

char	*translate(char *str, char **env)
{
	char	*var_value;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	if (str[i] && str[i] == '?')
	{
		var_value = ft_itoa(g_exit_status);
		if (!var_value)
			return (NULL);
	}
	else
	{
		var_value = get_env(str, env);
		if (!var_value)
			return (NULL);
		else
			var_value = ft_strdup(var_value);
	}
	return (var_value);
}

bool	check_translate(char *str)
{
	int		i;
	bool	to_translate;
	bool	quote;
	bool	dquote;

	i = 0;
	to_translate = true;
	dquote = false;
	quote = false;
	if (!str)
		return (false);
	while (str[i])
	{
		if (str[i] && str[i] == '\"')
			dquote = !dquote;
		if (str[i] && str[i] == '\'' && dquote == false)
			quote = !quote;
		if (str[i] && str[i] == '$' && quote == true)
			to_translate = false;
		i++;
	}
	return (to_translate);
}
