/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:43:04 by raamorim          #+#    #+#             */
/*   Updated: 2025/06/18 03:51:37 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_valid_redirection(const char *token, t_info *info)
{
	int	i;

	i = 0;
	while (info->redirections->reds[i])
	{
		if (ft_strncmp(token, info->redirections->reds[i],
				ft_strlen(token)) == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	print_redir_syntax_error(char *token, t_info *info)
{
	ft_putstr_fd("Shellinho: syntax error near unexpected token `", 2);
	if (token)
		ft_putstr_fd(token, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
	info->exit_status = 2;
}

static int	check_missing_redir_target(char **tokens, t_info *info)
{
	int	i;

	i = 0;
	while (tokens && tokens[i])
	{
		if (ft_strncmp(tokens[i], ">", 2) == 0 || ft_strncmp(tokens[i], ">>",
				3) == 0 || ft_strncmp(tokens[i], "<", 2) == 0
			|| ft_strncmp(tokens[i], "<<", 3) == 0)
		{
			if (!tokens[i + 1] || ft_strncmp(tokens[i + 1], ">", 2) == 0
				|| ft_strncmp(tokens[i + 1], ">>", 3) == 0
				|| ft_strncmp(tokens[i + 1], "<", 2) == 0 || ft_strncmp(tokens[i
						+ 1], "<<", 3) == 0)
				return (print_redir_syntax_error(tokens[i + 1], info), 1);
		}
		i++;
	}
	return (0);
}

static int	check_invalid_redir_length(char **tokens, t_info *info)
{
	int		i;
	char	*token;

	i = 0;
	while (tokens && tokens[i])
	{
		token = tokens[i];
		if (token[0] == '\x01') // Corrigido!
			token++;
		if (ft_strncmp(token, "<", 2) == 0 || ft_strncmp(token, ">", 2) == 0
			|| ft_strncmp(token, ">>", 3) == 0 || ft_strncmp(token, "<<", 3) == 0)
		{
			if (ft_strlen(token) > 3)
			{
				ft_putstr_fd("Shellinho: syntax error near unexpected token `", 2);
				ft_putstr_fd(tokens[i], 2);
				ft_putstr_fd("'\n", 2);
				return (update_status(info, 2), 1);
			}
		}
		i++;
	}
	return (0);
}


int	has_invalid_redirection(char **tokens, t_info *info)
{
	if (check_missing_redir_target(tokens, info))
		return (1);
	if (check_invalid_redir_length(tokens, info))
		return (1);
	return (0);
}
