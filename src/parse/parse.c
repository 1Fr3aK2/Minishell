/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:55:03 by raamorim          #+#    #+#             */
/*   Updated: 2025/02/11 18:23:13 by raamorim         ###   ########.fr       */
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

// static char	*new_input(char *input)
// {
// 	int		i;
// 	char	*new;
// 	int		len;
// 	int		j;

// 	i = 0;
// 	printf("initial input = %s\n", input);
// 	if (count_skip_quotes(input) == 0)
// 		return (input);
// 	if (count_skip_quotes(input) % 2 != 0)
// 	{
// 		printf("ERROR\n");
// 		return (NULL);
// 	}
// 	len = ft_strlen(input);
// 	while (input[i] && !(is_quote(input[i])))
// 		i++;
// 	j = ++i;
// 	new = ft_substr(input, j, (len - j - 1));
// 	if (!new)
// 		return (input);
// 	return (new);
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
