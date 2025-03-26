/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:39:52 by raamorim          #+#    #+#             */
/*   Updated: 2025/03/26 00:37:18 by rafael           ###   ########.fr       */
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
			start = ++i;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			return (i - start);
		}
		i++;
	}
	return (0);
}

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
			var_name = ft_substr(str, i, get_varname_len(str));
			if (!var_name)
				return (NULL);
			return (var_name);
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
		var_value = ft_itoa(exit_status);
		if (!var_value)
			return (NULL);
	}
	else 
	{
		var_value = get_env(str, env);
		if (!var_value)
			return (NULL);
		else
			free(str);
	}
	return (var_value);
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
