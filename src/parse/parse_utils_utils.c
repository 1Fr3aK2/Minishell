/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 04:43:05 by rafael            #+#    #+#             */
/*   Updated: 2025/07/11 17:20:19 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**fill_new_args(char **args, char **tmp, int idx, char **new_args)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (args[i])
	{
		if (i == idx)
			k = copy_tokens(new_args, tmp, k);
		else
		{
			new_args[k] = ft_strdup(args[i]);
			if (!new_args[k])
				return (cleanup_and_return(new_args, tmp, args));
			k++;
		}
		if (k == -1)
			return (cleanup_and_return(new_args, tmp, args));
		i++;
	}
	new_args[k] = NULL;
	return (cleanup_and_return(tmp, args, new_args));
}

char	**retokenize_specific_token(char **args, int token_index)
{
	char	**tmp;
	char	**new_args;
	int		total;

	if (!args || !args[token_index])
		return (args);
	tmp = custom_ft_split(args[token_index]);
	if (!tmp)
		return (args);
	total = count_total_tokens(args, tmp, token_index);
	new_args = malloc(sizeof(char *) * (total + 1));
	if (!new_args)
		return (cleanup_and_return(tmp, NULL, args));
	return (fill_new_args(args, tmp, token_index, new_args));
}

int	handle_new_token(char ***result_ptr, int index, char *original, char *new)
{
	char	**result;

	result = *result_ptr;
	free(result[index]);
	result[index] = new;
	if (needs_retokenization(original, new))
	{
		free(original);
		result = retokenize_specific_token(result, index);
		if (!result)
			return (0);
		*result_ptr = result;
		return (2);
	}
	free(original);
	return (1);
}

int	update_token(char ***result_ptr, int index, t_info *info)
{
	char	*original;
	char	*new;
	char	**result;

	result = *result_ptr;
	original = ft_strdup(result[index]);
	if (!original)
		return (0);
	new = handle_dollar(result[index], info);
	if (!new)
		return (free(original), 0);
	if (ft_strncmp(new, result[index], ft_strlen(result[index])) != 0)
		return (handle_new_token(result_ptr, index, original, new));
	free(new);
	free(original);
	return (1);
}
