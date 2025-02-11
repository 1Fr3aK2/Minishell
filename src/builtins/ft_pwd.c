/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:57:10 by dsteiger          #+#    #+#             */
/*   Updated: 2025/02/11 16:23:16 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

void	ft_pwd(t_info *info)
{
	char buf[PATH_MAX]; // buffer to store the current directory
	(void)info;
	getcwd(buf, PATH_MAX);
		// Get the current working directory and store it in 'buf'
	printf("%s\n", buf);
	return ;
}
