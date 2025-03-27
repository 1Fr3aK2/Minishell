/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:54:56 by raamorim          #+#    #+#             */
/*   Updated: 2025/03/27 18:12:47 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

static void	fill_builtins(t_info *info)
{
	info->builtins->builtins[0] = "echo";
	info->builtins->builtins[1] = "cd";
	info->builtins->builtins[2] = "pwd";
	info->builtins->builtins[3] = "export";
	info->builtins->builtins[4] = "unset";
	info->builtins->builtins[5] = "env";
	info->builtins->builtins[6] = "exit";
	info->builtins->builtins[7] = NULL;
	info->builtins->f[0] = ft_echo;
	info->builtins->f[1] = ft_cd;
	info->builtins->f[2] = ft_pwd;
	info->builtins->f[3] = ft_export;
	// info->builtins->f[4] = ft_unset;
	info->builtins->f[5] = ft_env;
	info->builtins->f[6] = ft_exit;
	info->builtins->f[7] = NULL;
}

void	copy_env(t_info *info, char **env)
{
	int	i;
	int	j;

	if (!env || !*env)
		return ;
	i = 0;
	while (env[i])
		i++;
	info->my_env = ft_calloc((i + 1), sizeof(char *));
	if (!info->my_env)
		return ;
	j = -1;
	while (++j < i)
	{
		info->my_env[j] = ft_strdup(env[j]);
		if (!info->my_env[j])
		{
			while (--j >= 0)
				free(info->my_env[j]);
			free(info->my_env);
			return ;
		}
	}
}

static void	fill_types(t_info *info)
{
	info->types->types[0] = "|";
	info->types->types[1] = "||";
	info->types->types[2] = "&&";
	info->types->types[3] = NULL;
	info->types->f[0] = ft_pipe_wrapper;
	info->types->f[1] = /* ft_or */ NULL;
	info->types->f[2] = /* ft_and */ NULL;
	info->types->f[3] = NULL;
}

static void	fill_redirections(t_info *info)
{
	info->redirections->reds[0] = ">";
	info->redirections->reds[1] = "<";
	info->redirections->reds[2] = ">>";
	info->redirections->reds[3] = "<<";
	info->redirections->reds[4] = NULL;
    info->redirections->f[0] = handle_output_redirection; // >
    info->redirections->f[1] = handle_input_redirection;  // <
    info->redirections->f[2] = handle_append_redirection; // >>
    info->redirections->f[3] = handle_heredoc_redirection; // <<
    info->redirections->f[4] = NULL;
}

void	init(t_info *info, char **env)
{
	info->cmd_tree = NULL;
	info->flags = NULL;
	info->builtins = malloc(sizeof(t_builtins));
	if (!info->builtins)
	{
		return ;
	}
	info->types = malloc(sizeof(t_types));
	if (!info->types)
		return (free(info->builtins));
	info->redirections = malloc(sizeof(t_reds));
    if (!info->redirections)
    {
		free(info->builtins);
		free(info->types);
        return ;
    }
	fill_builtins(info);
	fill_types(info);
	fill_redirections(info);
	copy_env(info, env);
}
