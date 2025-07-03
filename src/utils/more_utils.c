/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:01:35 by dsteiger          #+#    #+#             */
/*   Updated: 2025/07/03 04:17:06 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_redir_tokens(char **args, int i)
{
	int	j;

	if (args[i])
	{
		free(args[i]);
		args[i] = NULL;
	}
	if (args[i + 1])
	{
		free(args[i + 1]);
		args[i + 1] = NULL;
	}
	j = i + 2;
	while (args[j])
	{
		args[i++] = args[j++];
	}
	args[i] = NULL;
}

int	is_valid_append_token(const char *token)
{
	int	count;

	count = 0;
	while (token[count] == '>')
		count++;
	return (count == 2);
}
