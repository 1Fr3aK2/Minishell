/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:55:03 by raamorim          #+#    #+#             */
/*   Updated: 2025/02/13 12:54:34 by raamorim         ###   ########.fr       */
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
		while (input[i] && is_space(input[i])) // Ignorar espaços antes da palavra
			i++;
		if (!input[i]) // Se chegou ao final da string
			break ;
		k = 0;
		in_quotes = 0;
		temp = (char *)malloc(sizeof(char) * (ft_strlen(input) + 1));// Buffer temporário para remover aspas
		if (!temp)
		{
			while (j > 0) // Liberar memória alocada anteriormente
				free(new[--j]);
			free(new);
			return ;
		}
		while (input[i] && (in_quotes == 1 || !is_space(input[i])))// Copiar mantendo espaços dentro de aspas
		{
			if (is_quote(input[i])) // Alternar estado de "dentro das aspas"
				in_quotes = !in_quotes;
			else
				temp[k++] = input[i]; // Adicionar caractere se não for uma aspa
			i++;
		}
		temp[k] = '\0';             // Finaliza a string sem aspas
		new[j++] = ft_strdup(temp); // Aloca a palavra final sem aspas
		free(temp);
	}
	new[j] = NULL; // Finalizar o array de strings
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
	process_input(input, new); // Chamar a função sem precisar de retorno
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
