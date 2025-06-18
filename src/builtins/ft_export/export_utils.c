/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:08:28 by rafael            #+#    #+#             */
/*   Updated: 2025/06/18 16:42:50 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	check_valid_input(char *str, int *exit)
{
	if (!str)
		return (false);
	if (*str == '\0' || *str == '=' || *str == '+' || ft_isdigit(*str) == 1
		|| check_pos(str, '-') || check_pos(str, '.') || check_pos(str, ':')
		|| check_pos(str, ',') || check_pos(str, '\\') || check_pos(str, '!')
		|| check_pos(str, '?') || (ft_strchr(str, '+')
			&& !check_plus_sign(str)))
	{
		ft_putstr_fd("Minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		*exit = 1;
		return (false);
	}
	else if (*str == '_' && (*(str + 1) == '\0' || *(str + 1) == '='))
		return (false);
	return (true);
}

bool	check_plus_sign(char *str)
{
	int	i;

	if (!str)
		return (false);
	i = 0;
	while (str[i])
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

bool	check_equal_sign(char *str)
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

bool	check_equal_plus(char *str)
{
	if ((check_equal_sign(str) && check_plus_sign(str)) == true)
		return (true);
	else
		return (false);
}

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
