/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:54:56 by raamorim          #+#    #+#             */
/*   Updated: 2025/04/08 18:01:19 by dsteiger         ###   ########.fr       */
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
	info->builtins->f[4] = ft_unset;
	info->builtins->f[5] = ft_env;
	info->builtins->f[6] = ft_exit;
	info->builtins->f[7] = NULL;
}

void	copy_env(char ***my_env, char **env)
{
	int	i;
	int	j;

	if (!env || !*env)
		return ;
	i = 0;
	while (env[i])
		i++;
	*my_env = ft_calloc((i + 1), sizeof(char *));
	if (!*my_env)
		return ;
	j = -1;
	while (++j < i)
	{
		(*my_env)[j] = ft_strdup(env[j]);
		if (!(*my_env)[j])
		{
			while (--j >= 0)
				free((*my_env)[j]);
			free(*my_env);
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

void init_io(t_io *io)
{
	if (!io)
		return ;
	io->fd_in = -1;
	io->fd_out = -1;
	io->stdin_backup = -1;
	io->stdin_backup = -1;
	io->file = NULL;
	io->redirections=NULL;
}


void	init(t_info *info, char **env)
{
	info->cmd_tree = NULL;
	info->flags = NULL;
	info->export_env = NULL;
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
	info->io = malloc(sizeof(t_io));
	if (!info->io)
	{
		free(info->builtins);
		free(info->types);
		free(info->redirections);
        return ;
	}
	init_io(info->io);
	fill_builtins(info);
	fill_types(info);
	fill_redirections(info);
	copy_env(&info->my_env, env);
	copy_env(&info->export_env, env);
}
