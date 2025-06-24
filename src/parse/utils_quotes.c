/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:54:18 by rafael            #+#    #+#             */
/*   Updated: 2025/06/24 20:39:03 by rafael           ###   ########.fr       */
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

void	print_syntax_error_token(t_tree *node, char **tokens, t_info *info)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (node && node->args && node->args[0])
		ft_putstr_fd(node->args[0], 2);
	else if (tokens && tokens[0])
		ft_putstr_fd(tokens[0], 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
	info->error_msg = true;
}
