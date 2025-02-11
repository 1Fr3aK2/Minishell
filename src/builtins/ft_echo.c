/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:28:25 by dsteiger          #+#    #+#             */
/*   Updated: 2025/02/10 18:51:18 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void	is_valid(char **argv)
{
	if (!argv[2])
		write(1, "\n", 1);
}

int	check_flags(char *str)
{
	if (ft_strncmp(str, "-n", 2) == 0)
		return (0);
	return (1);
}

void	ft_echo(t_info *info)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (check_flags(info->args[i]) == 0)
		++i;
	while (info->args[i])
	{
		while (info->args[i][j])
		{
			write(1, &info->args[i][j], 1);
			j++;
		}
		if ((info->args[i + 1])) // espaco entre comandos
			write(1, " ", 1);
		j = 0;
		i++;
	}
	if (check_flags(info->flags) == 1)
		write(1, "\n", 1);
}
