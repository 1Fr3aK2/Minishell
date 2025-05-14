/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:30:37 by raamorim          #+#    #+#             */
/*   Updated: 2025/05/14 03:08:31 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shellinho.h"

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

static void	fill_types(t_info *info)
{
	info->types->types[0] = "|";
	info->types->types[1] = "||";
	info->types->types[2] = "&&";
	info->types->types[3] = NULL;
	info->types->f[0] = ft_pipe_wrapper;
	info->types->f[1] = ft_or_wrapper;
	info->types->f[2] = ft_and_wrapper;
	info->types->f[3] = NULL;
}

static void	fill_redirections(t_info *info)
{
	info->redirections->reds[0] = ">";
	info->redirections->reds[1] = "<";
	info->redirections->reds[2] = ">>";
	info->redirections->reds[3] = NULL;
	info->redirections->f[0] = handle_output_redirection;
	info->redirections->f[1] = handle_input_redirection;
	info->redirections->f[2] = handle_append_redirection;
	info->redirections->f[3] = NULL;
}

void	fill_all(t_info *info)
{
	fill_builtins(info);
	fill_builtins(info);
	fill_types(info);
	fill_redirections(info);
	copy_env(&info->export_env, info->my_env);
}
