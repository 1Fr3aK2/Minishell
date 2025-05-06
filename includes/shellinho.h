/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellinho.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 23:23:23 by rafael            #+#    #+#             */
/*   Updated: 2025/05/06 01:53:45 by rafael           ###   ########.fr       */
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
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
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
# define MAX_TYPES 8
# define MAX_REDS 5

# define SPACES " \n\t\v\f\r"

typedef struct s_info	t_info;
typedef struct s_io		t_io;

typedef struct s_types
{
	char				*types[MAX_TYPES];
	void				(*f[MAX_TYPES])(t_info *info);
}						t_types;

typedef struct s_builtins
{
	char				*builtins[MAX_BUILTINS];
	void				(*f[MAX_BUILTINS])(t_info *info);
}						t_builtins;

typedef struct s_reds
{
	char				*reds[MAX_REDS];
	void				(*f[MAX_REDS])(t_io *io);
}						t_reds;

typedef struct s_io
{
	char				*file;
	int					fd_in;
	int					fd_out;
	int					stdin_backup;
	int					stdout_backup;
	t_reds				*redirections;
}						t_io;

typedef enum s_node_type
{
	AND,
	PIPE,
	OR,
	CMD
}						t_node_type;

typedef struct s_tree
{
	char				**args;
	t_node_type			type;
	struct s_tree		*left;
	struct s_tree		*right;
}						t_tree;

typedef struct s_info
{
	char				*flags;
	char				**my_env;
	char				**export_env;
	t_builtins			*builtins;
	t_io				*io;
	t_reds				*redirections;
	t_types				*types;
	t_tree				*cmd_tree;
}						t_info;

extern unsigned int		g_exit_status;

// to_remove
void					print_node_type(t_node_type type);
void					init_io(t_io *io);
int						check_redirections(t_info *info);
void					remove_redir_tokens(char **args, int i);
void					remove_operator_tokens(char **args, int i);

// builtins/echo
int						check_flags(char *str);
void					ft_echo(t_info *info);

// builtins/env
void					ft_env(t_info *info);

// builtins/cd
void					cd_with_arg(const char *path);
int						count_levels(const char *arg);
void					ft_cd_doispontos(t_info *info, int levels);
void					ft_cd_home(t_info *info);
void					ft_cd(t_info *info);

// builtins/exit
void					ft_exit(t_info *info);
void					ft_pwd(t_info *info);
void					sort_env(char **args);

// builtins/export
void					sort_env(char **args);
char					*reverse_strchr(char *str, int c);
char					**create_sorted_env_copy(char **args);
void					ft_export(t_info *info);

// builtins/unset
void					ft_unset(t_info *info);

// builtins/pipe
void					ft_pipe_wrapper(t_info *info);

// builtins/and
void					exec_command(t_info *info, t_tree *node);
void					ft_and(t_info *info);

// builtins/or
void					ft_or(t_info *info);

// parse/handle_dollar
char					*handle_dollar(char *str, char **env);

// parse/expander
int						get_varname_len(char *str);
char					*expand(char *str);
char					*translate(char *str, char **env);
int						size_to_var(char *str);
bool					check_translate(char *str);

// parse/init
void					init(t_info *info);
void					copy_env(char ***my_env, char **env);

// parse/utils_init.c
void					fill_all(t_info *info);

// parse/parse
int						size_woutquotes(char *str);
char					*remove_quotes(char *str);
void					handle_quotes(char *str, char *new, int i, int *j);
char					**new_input(char *input);
void					parse(char *input, t_info *info);

// parse/parse_utils.c
void					ft_free(void **ptr);

// parse/quotes
int						check_quotes(char *input);
void					remove_all_quotes(char **tokens);

// parse/tree
t_tree					*parse_tokens(char **tokens);

// parse/utils_tree
int						search_ops(char **tokens);
t_node_type				find_type(char **tokens, int i);
// processes
void					child_process(t_info *info);
/* void					exec(t_info *info); */
void					exec(t_info *info, t_tree *node);

// processes/utils
/* char					*find_path(t_info *info); */
char					*find_path(t_info *info, char *cmd);
char					*get_env(char *variable_name, char **env);
void					free_types(t_types *types);

// redirections
void					handle_input_redirection(t_io *io);
void					handle_output_redirection(t_io *io);
void					handle_append_redirection(t_io *io);
void					handle_heredoc_redirection(t_io *io);
void					storing_backup(t_io *io);
void					restore_io(t_io *io);

// signals
void					handle_sigint(int sig);
void					set_signals(void);

// splits/custom_split
char					**custom_ft_split(char const *s);

// splits/split_quotes
char					**ft_split_quotes(char *s);

// splits/utils_split_quotes
int						count_word(char *str);
int						count_quotes(char *input);

// utils/utils_bools
bool					is_quote(char c);
int						is_operator(const char *str);

// utils
void					close_fds(int i);
void					close_pipe_fds(int fd[2]);
void					print_banner(void);
void					error_exit(char *msg);
void					free_arr(char **arr);
int						check_builtins(t_info *info);
int						check_operators(t_info *info);
void					clean(t_info *info);
char					*ft_strncpy(char *dest, char *src, unsigned int n);
void					free_tree(t_tree *node);

// main
void					start(t_info *info);
void					free_builtins(t_builtins *builtins);

#endif