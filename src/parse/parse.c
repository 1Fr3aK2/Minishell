/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:55:03 by raamorim          #+#    #+#             */
/*   Updated: 2025/02/11 21:03:20 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

bool	is_quote(char c)
{
	return ((c == '\'' || c == '\"'));
}

int	count_skip_quotes(char *input)
{
	int	quotes;
	int	i;

	if (!input)
		return (0);
	i = 0;
	quotes = 0;
	while (input[i])
	{
		if (is_quote(input[i]))
			quotes++;
		i++;
	}
	return (quotes);
}

static char	*new_input(char *input)
{
	char	*new;
	int		i;
	int		len;
	int		quotes;
	int		j;

	j = 0;
	i = -1;
	printf("initial input = %s\n", input);
	len = ft_strlen(input);
	quotes = count_skip_quotes(input);
	if (quotes == 0)
		return (input);
	if (quotes % 2 != 0)
	{
		printf("ERROR\n");
		return (NULL);
	}
	new = (char *)malloc(sizeof(char) * (len - quotes + 1));
	if (!new)
		return (NULL);
	while (input[++i])
	{
		if (!is_quote(input[i]))
			new[j++] = input[i];
	}
	new[j] = '\0';
	return (new);
}

void	parse(char *input, t_info *info)
{
	size_t	size;
	char	*teste;

	(void)info;
	if (!input)
		return ;
	size = ft_strlen(input);
	if (size > 0)
	{
		teste = new_input(input);
		if (teste)
			printf("teste: %s\n", teste);
		/* info->args = ft_split(input);
		if (!info->args)
			return ;
		info->flags = ft_strdup(info->args[1]); */
		// printf("1 carater arg 1 -> %c\n", info->args[1][0]);
	}
}
