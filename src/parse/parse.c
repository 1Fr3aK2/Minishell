/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:55:03 by raamorim          #+#    #+#             */
/*   Updated: 2025/02/14 16:37:43 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

char	**new_input(char *input)
{
	char	**new;

	if (count_quotes(input) % 2 != 0)
		return (printf("ERROR\n"), NULL);
	if (count_quotes(input) == 0)
		return (custom_ft_split(input));
	new = (char **)malloc(sizeof(char *) * (count_word(input) + 1));
	if (!new)
		return (NULL);
	new = ft_split_quotes(input);
	if (!new)
		return (free_arr(new), NULL);
	return (new);
}

void	parse(char *input, t_info *info)
{
	size_t	size;

	if (!input)
		return ;
	size = ft_strlen(input);
	if (size > 0)
	{
		info->args = new_input(input);
		if (!info->args)
			return ;
		info->flags = ft_strdup(info->args[1]);
	}
}
