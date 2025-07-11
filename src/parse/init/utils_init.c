/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:30:37 by raamorim          #+#    #+#             */
/*   Updated: 2025/06/25 16:11:09 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
	fill_redirections(info);
	copy_env(&info->export_env, info->my_env);
}
