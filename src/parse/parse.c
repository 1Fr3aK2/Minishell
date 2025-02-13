/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:55:03 by raamorim          #+#    #+#             */
/*   Updated: 2025/02/13 17:30:00 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

bool	is_quote(char c)
{
	return ((c == '\'' || c == '\"'));
}

int	count_quotes(char *input)
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

// static int	counte_word(char *str)
// {
// 	int		i;
// 	int		words;
// 	int		in_word;

// 	if (!str)
// 		return (-1);
// 	i = -1;
// 	words = 0;
// 	in_word = 0;
// 	while (str[++i])
// 	{
// 		if (is_quote(str[i]))
// 			continue;
// 		if (!is_space(str[i])) // Encontrou uma palavra
// 		{
// 			if (in_word == 0)
// 			{
// 				words++;
// 				in_word = 1;
// 			}
// 		}
// 		else
// 			continue; // Saiu de uma palavra
// 	}
// 	return (words);
// }
static int	counte_word(char *str)
{
	int	i;
	int	words;
	int	in_word;

	if (!str)
		return (-1);
	i = -1;
	words = 0;
	in_word = 0;
	while (str[++i])
	{
		if (is_quote(str[i]))
			continue ;
		if (!is_space(str[i])) // Encontrou uma palavra
		{
			if (in_word == 0)
			{
				words++;
				in_word = 1;
			}
		}
		else
			in_word = 0; // Saiu de uma palavra
	}
	return (words);
}

void	process_input(char *input, char **new)
{
	int		i;
	int		j;
	int		k;
	int		in_quotes;
	char	*temp;

	i = 0;
	j = 0;
	while (input[i])
	{
		while (input[i] && is_space(input[i]))
			i++;
		if (!input[i])
			break ;
		k = 0;
		in_quotes = 0;
		temp = (char *)malloc(sizeof(char) * (ft_strlen(input) + 1));
		if (!temp)
		{
			while (j > 0)
				free(new[--j]);
			free(new);
			return ;
		}
		while (input[i] && (in_quotes == 1 || !is_space(input[i])))
		{
			if (is_quote(input[i]))
				in_quotes = !in_quotes;
			else
				temp[k++] = input[i];
			i++;
		}
		temp[k] = '\0';
		new[j++] = ft_strdup(temp);
		free(temp);
	}
	new[j] = NULL;
}

char	**new_input(char *input)
{
	char	**new;

	if (count_quotes(input) % 2 != 0)
		return (printf("ERROR\n"), NULL);
	if (count_quotes(input) == 0)
		return (custom_ft_split(input));
	new = (char **)malloc(sizeof(char *) * (counte_word(input) + 1));
	if (!new)
		return (NULL);
	process_input(input, new);
	if (!new)
		return (NULL);
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
