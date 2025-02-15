/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:55:03 by raamorim          #+#    #+#             */
/*   Updated: 2025/02/15 02:53:13 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

/* char	*remove_quotes(char *str)
{
	int		i;
	int		start;
	char	quote;
	char	*new;

	if (!str)
		return (NULL);
	if (count_quotes(str) == 0)
		return (str);
	i = 0;
	while (str[i] && is_quote(str[i]))
	{
		quote = str[i];
		i++;
	}
	start = i;
	while (str[i] && str[i] != quote)
		i++;
	new = (char *)malloc(sizeof(char) * (i - start + 1));
	if (!new)
		return (NULL);
	ft_strncpy(new, &str[start], i - start);
	new[i - start] = '\0';
	return (new);
} */
/* char	*remove_quotes(char *str)
{
	int		i;
	int		start;
	char	quote;
	char	*new;
	int is__quote = 0;

	i = 0;
	start = 0;
	quote = 0;
	if (!str)
		return (NULL);
	if (count_quotes(str) == 0)
		return (str);
	while(str[i])
	{
		if (str[i] && is__quote == 0 && is_quote(str[i]))
		{
			quote = str[i];
			is__quote = 1;
			i++;
		}
		else if (str[i] && is__quote == 1 && str[i] = quote)
		{
			is__quote = 0;
			i++;
		}
		
	}
	
} */


char	*remove_quotes(char *str)
{
	char	*new;
	int		len;
	int		i;
	int		j;
	int		in_quotes;
	char	quote_char;

	if (!str)
		return (NULL);
	len = strlen(str);
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	in_quotes = 0;
	quote_char = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			if (in_quotes == 0)
			{
				in_quotes = 1;
				quote_char = str[i];
			}
			else if (str[i] == quote_char)
				in_quotes = 0;
			else
				new[j++] = str[i];
		}
		else
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

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
	int		i;

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
	i = 0;
	while (info->args[i])
	{
		printf("before remove info->args[%d] = %s\n", i, info->args[i]);
		i++;
	}
	printf("\n\n");
	i = 0;
	while (info->args[i])
	{
		info->args[i] = remove_quotes(info->args[i]);
		printf("after remove info->args[%d] = %s\n", i, info->args[i]);
		i++;
	}
}
