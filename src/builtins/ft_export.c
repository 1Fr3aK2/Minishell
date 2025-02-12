/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:26:00 by dsteiger          #+#    #+#             */
/*   Updated: 2025/02/11 16:39:42 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

// set env variables to be exported to child processes.
// Export makes a variable available to any child process.
void	sort_env(char **args)
{
	int		i;
	char	*temp;
	int		sorted;
	int		len;

	sorted = 0;
	while (!sorted)
	{
		i = 0;
		sorted = 1;
		while (args[i])
		{
			len = ft_strlen(args[i]);
			if (ft_strncmp(args[i], args[i + 1], len) > 0)
			{
				temp = args[i];
				args[i] = args[i + 1];
				args[i + 1] = temp;
				sorted = 0;
			}
			i++;
		}
		len--;
	}
}

void	ft_export(t_info *info)
{
	int	i;

	if (info->args[1] == NULL) // se o input for so "export"
	{
		sort_env(info->my_env);
		i = 0;
		while (info->my_env[i])
		{
			printf("%s %s\n", "declare -x", info->my_env[i]);
			i++;
		}
	}
	else
	{
		
	}
}
