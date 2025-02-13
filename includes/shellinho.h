/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellinho.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 23:23:23 by rafael            #+#    #+#             */
/*   Updated: 2025/02/13 15:26:48 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELLINHO_H
# define SHELLINHO_H

# include "../libraries/libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

# define RESET "\033[0m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define RED "\033[31m"
# define MAX_BUILTINS 8

# define SPACES " \n\t\v\f\r"

typedef struct s_info	t_info;
/* typedef enum s_type
{

}			t_type; */

typedef struct s_builtins
{
	char				*builtins[MAX_BUILTINS];
	void				(*f[MAX_BUILTINS])(t_info *info);
}						t_builtins;

typedef struct s_info
{
	char				**args;
	char				*flags;
	char				**my_env;
	t_builtins			*builtins;
	/* t_type type; */
}						t_info;

// utils
void					close_fds(int i);
void					print_banner(void);
void					start(t_info *info);
void					free_arr(char **arr);
void					error_exit(char *msg);
int						check_builtins(t_info *info);
void					clean(t_info *info);

// echo
int						check_flags(char *str);
void					ft_echo(t_info *info);

// exit
void					ft_exit(t_info *info);
void					ft_pwd(t_info *info);
void					sort_env(char **args);
void					ft_export(t_info *info);

// parse/init
void					copy_env(t_info *info, char **env);
void					init(t_info *info, char **env);

// parse/parse
void					parse(char *input, t_info *info);
bool					is_quote(char c);
int						count_quotes(char *input);

// processes/custom_split
char					**custom_ft_split(char const *s);

// processes
void					child_process(t_info *info);
void					exec(t_info *info);

// processes/utils
char					*find_path(t_info *info);

#endif