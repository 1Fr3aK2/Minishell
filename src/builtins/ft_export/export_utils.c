/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:08:28 by rafael            #+#    #+#             */
/*   Updated: 2025/05/07 20:37:16 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shellinho.h"

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
