/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:26:00 by dsteiger          #+#    #+#             */
/*   Updated: 2025/03/27 15:45:53 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shellinho.h"

// set env variables to be exported to child processes.
// Export makes a variable available to any child process.

// TODO - "a b" - nao e suposto funcionar
// 		- a b - suposto criar 2 variaveis a, b
//		- essencialmente, nao pode ter espacos quando uso aspas

//		- o meu aceita espacos quando ha aspas
void	sort_env(char **args)
{
	int		i;
	char	*temp;
	int		sorted;
	int		len;

	sorted = 0;
	while (!sorted)
	{
		i = 0;
		sorted = 1;
		while (args[i])
		{
			len = ft_strlen(args[i]);
			if (ft_strncmp(args[i], args[i + 1], len) > 0)
			{
				temp = args[i];
				args[i] = args[i + 1];
				args[i + 1] = temp;
				sorted = 0;
			}
			i++;
		}
		len--;
	}
}

void	add_to_my_env(t_info *info, char *str)
{
	int i;
	char **new_env;
	
	i = 0;
	new_env = NULL;
	while (info->my_env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	i = 0;
	while (info->my_env[i])
	{
		new_env[i] = info->my_env[i];
		i++;
	}
	new_env[i] = ft_strdup(str); // add o que vem dps de export
	new_env[i + 1] = NULL;
	free(info->my_env);
	info->my_env = new_env;
}

char	**create_sorted_env_copy(char **args)
{
	int		i;
	char	**dest;

	i = 0;
	while (args[i])
		i++;
	dest = (char **)malloc(sizeof(char *) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (args[i])
	{
		dest[i] = ft_strdup(args[i]);
		i++;
	}
	dest[i] = NULL;
	sort_env(dest);
	return (dest);
}

static bool check_valid_input(char *str)
{
	int i;
	
	if (!str)
		return (false);
	i = 0;
	while(str[i])
	{
		if (str[i] && str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

static bool check_env(char **env, char *str)
{
	int i;
	
	if (!env || !*env || !str)
		return (false);
	i = 0;
	while(env[i])
	{
		if (ft_strncmp(str, env[i], (ft_strlen(str) - ft_strlen(ft_strrchr(str, '=')))) == 0)
		{
			free(env[i]);
			char *teste = ft_strdup(str);
			env[i] = teste;
			i++;
			return (true);
		}
		i++;
	}
	return (false);

}

void	ft_export(t_info *info)
{
	char	**sorted_env;
	int		i;

	i = 1;
	if (info->cmd_tree->args[i] != NULL) // ve se ha algo depois do export
	{
		if (check_valid_input(info->cmd_tree->args[i]) == true)
		{
			if (check_env(info->my_env, info->cmd_tree->args[i]) == false)
			{
				printf("string %s\n", info->cmd_tree->args[i]);
				while (info->cmd_tree->args[i])
				{
					add_to_my_env(info, info->cmd_tree->args[i++]);
				}
			}
		}
		else
			return ;
	}
	else
	{
		printf("aqui\n");
		sorted_env = create_sorted_env_copy(info->my_env);
		if (!sorted_env)  // talvez desnecessario... ja faco isto na outra funcao
			return ;
		i = 0;
		while (sorted_env[i])
		{
			printf("declare -x %s\n", sorted_env[i]);
			free(sorted_env[i]);
			i++;
		}
		free(sorted_env);
	}
}
