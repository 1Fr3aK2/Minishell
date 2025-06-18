/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:54:18 by rafael            #+#    #+#             */
/*   Updated: 2025/06/18 16:34:20 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*add_spaces_around(char *str)
{
	char	*tmp;

	tmp = ft_strjoin("\x01", str);
	if (!tmp)
		return (NULL);
	return (tmp);
}

void	add_space_operators(char **str)
{
	char	*temp;

	if (!str || !*str)
		return ;
	if (ft_strncmp(*str, "\'<\'", 4) == 0 || ft_strncmp(*str, "\'<<\'", 5) == 0
		|| ft_strncmp(*str, "\'>\'", 4) == 0 || ft_strncmp(*str, "\'>>\'",
			5) == 0 || ft_strncmp(*str, "\'|\'", 4) == 0 || ft_strncmp(*str,
			"\'&&\'", 5) == 0 || ft_strncmp(*str, "\'||\'", 5) == 0
		|| ft_strncmp(*str, "\"<\"", 4) == 0 || ft_strncmp(*str, "\"<<\"",
			5) == 0 || ft_strncmp(*str, "\">\"", 4) == 0 || ft_strncmp(*str,
			"\">>\"", 5) == 0 || ft_strncmp(*str, "\"|\"", 4) == 0
		|| ft_strncmp(*str, "\"&&\"", 5) == 0 || ft_strncmp(*str, "\"||\"",
			5) == 0)
	{
		temp = add_spaces_around(*str);
		if (!temp)
			return ;
		free(*str);
		*str = temp;
	}
}

int	count_non_empty(char **tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (tokens[i][0] != '\0')
			count++;
		i++;
	}
	return (count);
}

void	copy_non_empty(char **src, char **dst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i][0] != '\0')
			dst[j++] = ft_strdup(src[i]);
		i++;
	}
	dst[j] = NULL;
}
