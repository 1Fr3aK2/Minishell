/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:57:10 by dsteiger          #+#    #+#             */
/*   Updated: 2025/06/06 15:40:26 by dsteiger         ###   ########.fr       */
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
