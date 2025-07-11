/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_parse_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 04:43:05 by rafael            #+#    #+#             */
/*   Updated: 2025/07/11 17:23:24 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	should_skip(char *arg, int *skip_next)
{
	if (*skip_next)
		return (*skip_next = 0, 1);
	if (ft_strncmp(arg, "<<", 2) == 0 && arg[2] == '\0')
		return (*skip_next = 1, 1);
	return (0);
}

static int	handle_token_status(char ***result, t_info *info, int *i)
{
	int	status;

	status = update_token(result, *i, info);
	if (status == 2)
	{
		*i = 0;
		return (1);
	}
	return (status);
}

static void	process_tokens(char ***result, t_info *info)
{
	int	i;
	int	skip_next;

	i = 0;
	skip_next = 0;
	while ((*result)[i])
	{
		if (should_skip((*result)[i], &skip_next))
		{
			i++;
			continue ;
		}
		if (is_lonely_dollar((*result)[i]))
		{
			i++;
			continue ;
		}
		if (handle_token_status(result, info, &i) == 0)
			break ;
		i++;
	}
}

char	**check_dollar_and_retokenize(char **args, t_info *info)
{
	char	**result;

	if (!info || !info->my_env || !args)
		return (args);
	result = args;
	process_tokens(&result, info);
	return (result);
}
