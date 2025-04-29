/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:28:25 by dsteiger          #+#    #+#             */
/*   Updated: 2025/04/23 17:29:36 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

int	check_flags(char *str)
{
	if (ft_strlen(str) != 2)
		return (1);
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
	if (check_redirections(info) == 0)
		exit(0);
	if (check_flags(info->cmd_tree->args[i]) == 0)
		++i;
	while (info->cmd_tree->args[i])
	{
		while (info->cmd_tree->args[i][j])
		{
			write(1, &info->cmd_tree->args[i][j], 1);
			j++;
		}
		if ((info->cmd_tree->args[i + 1]))
			write(1, " ", 1);
		j = 0;
		i++;
	}
	if (check_flags(info->flags) == 1)
		write(1, "\n", 1);
}
