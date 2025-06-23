/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:57:10 by dsteiger          #+#    #+#             */
/*   Updated: 2025/06/23 20:16:41 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_info *info)
{
	char	buf[PATH_MAX];

	(void)info;
	getcwd(buf, PATH_MAX);
	printf("%s\n", buf);
	return ;
}
