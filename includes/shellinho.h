/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellinho.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 23:23:23 by rafael            #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2025/05/19 17:37:51 by raamorim         ###   ########.fr       */
=======
/*   Updated: 2025/05/19 17:46:41 by dsteiger         ###   ########.fr       */
>>>>>>> Stashed changes
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
	int					stdin_is_heredoc;

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
	unsigned int		exit_status;
	char				*flags;
	char				**my_env;
	char				**export_env;
	t_builtins			*builtins;
	t_io				*io;
	t_reds				*redirections;
	t_types				*types;
	t_tree				*cmd_tree;
}						t_info;


void	ignore_sigquit(void);
void	set_signals_noninteractive(void);
void	signal_print_newline(int signal);
void	set_signals_interactive(void);

// builtins/export/export_aux_functions.c
void					handle_regular_assignment(t_info *info, char *arg);
void					handle_plus_assignment(t_info *info, char *arg);
void					add_check(char ***arr, char *str);

// builtins/export
void					add_to_env(char ***env, char *str);
void					sort_env(char **args);
char					**create_sorted_env_copy(char **args);
void					ft_export(t_info *info);

// builtins/export/export_utils.c
bool					check_equal_plus(char *str);
bool					check_equal_sign(char *str);
bool					check_plus_sign(char *str);
bool					check_valid_input(char *str, int *exit);
void					format_str(char **str);

// builtins/export/export_utils_utils.c
bool					check_pos(char *str, char c);
int						find_index(char **arr, char *str);
void					create_var(char ***env, char *str);
bool					check_env(char ***env, char *str);

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

// builtins/pwd
void					ft_pwd(t_info *info);

// builtins/unset
void					ft_unset(t_info *info);

// builtins/ft_pipe/ft_pipe.c
void					ft_pipe_wrapper(t_info *info);
void					ft_pipe(t_info *info, t_tree *node);

// builtins/ft_pipe/ft_pipe_utils.c
void					wait_all(pid_t last_pid, t_info *info);
void					exec_command(t_info *info, t_tree *node);

// builtins/and
void					ft_and(t_info *info, t_tree *node);
void					ft_and_wrapper(t_info *info);

// builtins/or
void					exec_command_op(t_info *info, t_tree *node);
void					ft_or(t_info *info, t_tree *node);
void					ft_or_wrapper(t_info *info);

// parse/expander/handle_dollar
char					*handle_dollar(char *str, t_info *info);

// parse/expander/expander.c
char					*expand(char *str);
char					*translate(char *str, char **env, t_info *info);
bool					check_translate(char *str);

// parse/expander/utils_expander.c
int						get_varname_len(char *str);
char					*get_var_name(char *str, int *i);
int						size_to_var(char *str);

// parse/init/init.c
void					copy_env(char ***my_env, char **env);
void					init_io(t_io *io);
void					init(t_info *info);
void					update_status(t_info *info, unsigned int status);

// parse/utils_init.c
void					fill_all(t_info *info);

// parse/tree/tree.c
t_tree					*creat_op_node(char **tokens, int *index, t_info *info);
t_tree					*create_node(char **tokens);

// parse/utils_tree
int						search_ops(char **tokens);
t_node_type				find_type(char **tokens, int i);
t_tree					*parse_tokens(char **tokens, t_info *info);

// parse/parse_utils.c

int						size_woutquotes(char *str);
void					handle_quotes(char *str, char *new, int i, int *j);
char					**new_input(char *input);

// parse/parse.c
t_tree					*build_tree_tokens(char **tokens, t_info *info);
void					parse(char *input, t_info *info);

// parse/quotes
int						check_quotes(char *input);
char					*remove_quotes(char *str);
void					remove_all_quotes(char **tokens);

// processes/processes.c
void					child_process(t_info *info);
void					exec(t_info *info, t_tree *node);

// processes/utils.c
char					*get_env(char *variable_name, char **env);
char					*find_path(t_info *info, char *cmd);

// redirections/heredocs
void					handle_heredoc_redirection(t_io *io, t_info *info);
void					prepare_heredocs(t_tree *node, t_info *info);
void					handle_siging_heredoc(int sig);

// redirections/redir_utils
void					storing_backup(t_io *io);
void					restore_io(t_io *io);

// redirections/redirections
void					handle_output_redirection(t_io *io);
void					handle_input_redirection(t_io *io);
void					handle_append_redirection(t_io *io);

// signals
void	ignore_sigquit(void);
void					handle_sigint(int sig);
void	set_signals_interactive(void);
void	print_newline(int signal);
void	set_signals_noninteractive(void);

// splits/custom_split.c
char					**custom_ft_split(char const *s);

// splits/split_quotes.c
char					**ft_split_quotes(char *s);

// splits/utils_split_quotes.c
int						count_quotes(char *input);
int						count_word(char *str);

// utils/checks.c
int						check_builtins(t_info *info);
int						check_operators(t_info *info);
int						check_redirections(t_info *info);
void					update_io_file(t_io *io, char *filename);
void					remove_redir_tokens(char **args, int i);

// utils/free.c
void					free_arr(char **arr);
void					free_tree(t_tree *node);
void					free_io_file(t_io *io);
void					free_builtins(t_builtins *builtins);
void					*free_str(char **dest, int i);

// utils/utils_bools
bool					is_quote(char c);
int						is_operator(const char *str);
int						is_operator_char(char c);
int						is_double_operator(char *str);

// utils
void					close_fds(int i);
void					close_pipe_fds(int fd[2]);
char					*reverse_strchr(char *str, int c);
void					change_shlvl(char ***env, char *name);

// main
void					start(t_info *info);

#endif