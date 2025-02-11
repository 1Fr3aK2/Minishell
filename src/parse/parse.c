/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:55:03 by raamorim          #+#    #+#             */
/*   Updated: 2025/02/11 16:28:30 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

// bool	is_quote(char c)
// {
// 	return ((c == '\'' || c == '\"'));
// }

// int	count_skip_quotes(char *input)
// {
// 	int	quotes;
// 	int	i;

// 	if (!input)
// 		return (0);
// 	i = 0;
// 	quotes = 0;
// 	while (input[i])
// 	{
// 		while (is_space(input[i]))
// 			i++;
// 		if (is_quote(input[i]))
// 		{
// 			i++;
// 			quotes++;
// 		}
// 		i++;
// 	}
// 	return (quotes);
// }

void	parse(char *input, t_info *info)
{
	size_t	size;
	// int		i;

	if (!input)
		return ;
	size = ft_strlen(input);
	if (size > 0)
	{
		// i = count_skip_quotes(input);
		// printf("%d\n", i);
		// printf("1 carater arg 1 -> %c\n", input[5]);
		info->args = ft_split(input);
		if (!info->args)
			return ;
		// printf("1 carater arg 1 -> %c\n", info->args[1][0]);
		info->flags = ft_strdup(info->args[1]);
	}
}
