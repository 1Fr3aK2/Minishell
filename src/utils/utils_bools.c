/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:23:02 by raamorim          #+#    #+#             */
/*   Updated: 2025/05/10 03:33:33 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

bool	is_quote(char c)
{
	return ((c == '\'' || c == '\"'));
}

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	is_operator(char *str)
{
	if (!str)
		return (0);
	if ((str[0] == '|' && str[1] == '|') || (str[0] == '&' && str[1] == '&'))
		return (2);
	if ((str[0] == '<' && str[1] == '<') || (str[0] == '>' && str[1] == '>'))
		return (2);
	if (str[0] == '|' || str[0] == '<' || str[0] == '>')
		return (1);
	return (0);
}
