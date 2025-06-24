/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:23:02 by raamorim          #+#    #+#             */
/*   Updated: 2025/06/24 20:00:21 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_quote(char c)
{
	return ((c == '\'' || c == '\"'));
}

int	is_operator(const char *str)
{
	if (!str)
		return (0);
	if ((str[0] == '<' && str[1] == '<') || (str[0] == '>' && str[1] == '>'))
		return (2);
	if (str[0] == '|' || str[0] == '<' || str[0] == '>')
		return (1);
	return (0);
}

int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_double_operator(char *str)
{
	if (str[0] == str[1] && (str[0] == '>' || str[0] == '<'))
		return (1);
	return (0);
}
