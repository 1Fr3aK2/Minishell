/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:55:33 by raamorim          #+#    #+#             */
/*   Updated: 2025/02/14 03:43:56 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

/* static void	*my_malloc(size_t size)
{
	int malloc_fail_counter = 0; // Número de chamadas antes de falhar
	if (--malloc_fail_counter <= 0)
	{
		return (NULL); // Força falha de alocação
	}
	return (malloc(size));
}

static void	check_open_fds(void)
{
	int	fd;

	// F_GETFD retorna -1 se o FD não está em uso
	for (fd = 3; fd < 1024; ++fd)
	{
		if (fcntl(fd, F_GETFD) != -1)
		{
			printf("\nFD %d is still open\n", fd);
		}
	}
} */

void	close_fds(int i)
{
	i = 3;
	while (i < FOPEN_MAX)
	{
		close(i);
		i++;
	}
}

void	print_banner(void)
{
    printf(GREEN
        "   _____ __  __________    __    _____   ____  ______ \n"
        "  / ___// / / / ____/ /   / /   /  _/ | / / / / / __ \\ \n"
        "  \\__ \\/ /_/ / __/ / /   / /    / //  |/ / /_/ / / / / \n"
        " ___/ / __  / /___/ /___/ /____/ // /|  / __  / /_/ /  \n"
        "/____/_/ /_/_____/_____/_____/___/_/ |_/_/ /_/\\____/   \n"
        "\n" RESET"\n");
}

void	error_exit(char *msg)
{
	if (!msg)
		perror("Error\n");
	else
		perror(msg);
	close_fds(0);
	rl_clear_history();
	exit(EXIT_FAILURE);
}

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

int	check_builtins(t_info *info)
{
	char	*cmd;
	int		i;

	cmd = info->args[0];
	i = 0;
	while (info->builtins->builtins[i])
	{
		if (ft_strncmp(cmd, info->builtins->builtins[i], ft_strlen(cmd)) == 0)
		{
			if (info->builtins->f[i])
				info->builtins->f[i](info);
			return (0);
		}
		i++;
	}
	return (1);
}

void clean(t_info *info)
{
	if (!info)
		return ;
	if (info->args)
		free_arr(info->args);
	if (info->flags)
		free(info->flags);
	// if (info->builtins)
	// {
	// 	free_arr(info->builtins->builtins);
	// 	free(info->builtins->f);
	// 	free(info->builtins);
	// }
	close_fds(3);
	rl_clear_history();
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}