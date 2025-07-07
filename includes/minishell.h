/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 23:23:23 by rafael            #+#    #+#             */
/*   Updated: 2025/07/07 18:49:43 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# define MAX_TYPES 3
# define MAX_REDS 5

# define SPACES " \n\t\v\f\r"

typedef struct s_info			t_info;
typedef struct s_io				t_io;

typedef struct s_builtins
{
	char						*builtins[MAX_BUILTINS];
	void						(*f[MAX_BUILTINS])(t_info *info);
}								t_builtins;

typedef struct s_reds
{
	char						*reds[MAX_REDS];
	int							(*f[MAX_REDS])(t_io *io, t_info *info);
}								t_reds;

typedef struct s_io
{
	char						*file;
	int							fd_in;
	int							fd_out;
	int							stdin_backup;
	int							stdout_backup;
	int							heredoc_fd;
	int							stdin_is_heredoc;
	t_reds						*redirections;
}								t_io;

typedef enum s_node_type
{
	PIPE,
	CMD
}								t_node_type;

typedef struct s_tree
{
	char						**args;
	t_node_type					type;
	t_io						*io;
	struct s_tree				*left;
	struct s_tree				*right;
}								t_tree;

typedef struct s_info
{
	bool						in_redir;
	bool						error_msg;
	unsigned int				exit_status;
	char						**my_env;
	char						**export_env;
	t_builtins					*builtins;
	t_io						*io;
	t_reds						*redirections;
	t_tree						*cmd_tree;
}								t_info;

extern volatile sig_atomic_t	g_sigint_received;

// builtins/export/export_aux_functions.c
bool							check_pipeline_redirection(t_tree *node);
void							handle_regular_assignment(t_info *info,
									char *arg);
void							handle_plus_assignment(t_info *info, char *arg);
void							add_check(char ***arr, char *str);

// builtins/export.c
void							print_sorted_env(char **env);
void							add_to_env(char ***env, char *str);
void							sort_env(char **args);
char							**create_sorted_env_copy(char **args);
void							ft_export(t_info *info);

// builtins/ft_export/ft_export_wrapper.c
void							ft_export_wrapper(t_info *info, t_tree *node);

// builtins/export/export_utils.c
bool							check_equal_plus(char *str);
bool							check_equal_sign(char *str);
bool							check_plus_sign(char *str);
bool							check_valid_input(char *str, int *exit);
void							format_str(char **str);

// builtins/export/export_utils_utils.c
bool							check_pos(char *str, char c);
int								find_index(char **arr, char *str);
void							create_var(char ***env, char *str);
bool							check_env(char ***env, char *str);

// builtins/echo.c
int								check_flags(char *str);
void							ft_echo(t_info *info);
void							ft_echo_wrapper(t_info *info, t_tree *node);

// builtins/env.c
void							ft_env(t_info *info);

// builtins/cd.c
void							cd_with_arg(const char *path, t_info *info);
int								count_levels(const char *arg);
void							ft_cd_doispontos(t_info *info, int levels);
void							ft_cd_home(t_info *info);
void							ft_cd(t_info *info);

// builtins/exit.c
void							ft_exit(t_info *info);
void							ft_exit2(t_info *info);

// builtins/pwd.c
void							ft_pwd(t_info *info);

// builtins/unset.c
void							ft_unset(t_info *info);

// builtins/ft_pipe/ft_pipe.c
void							child_exec(t_info *info, t_tree *node, int in,
									int out);
pid_t							handle_pipe_fork(t_info *info, t_tree *node,
									int in, int *fd);
pid_t							create_pipe(t_info *info, t_tree *node, int in,
									int *out);
void							ft_pipe(t_info *info, t_tree *node);
void							ft_pipe_wrapper(t_info *info);

// builtins/ft_pipe/ft_pipe_utils.c
void							wait_all(pid_t last_pid, t_info *info);
void							handle_heredoc(t_tree *node);
void							exec_comand_op(t_info *info, t_tree *node);
void							execute_node(t_info *info, t_tree *node);
bool							check_pipeline_redirection(t_tree *node);

// builtins/ft_pipe/handlers.c
void							handle_fork_exec(t_info *info, t_tree *curr,
									int in, pid_t *last_pid);
void							handle_pipe_loop(t_info *info, t_tree **curr,
									int *in, pid_t *last_pid);

// builtins/utils_builtins.c
void							exec_command(t_info *info, t_tree *node);
int								exec_builtins(char **cmd, t_info *info,
									t_tree *node);
int								is_builtin(char **builtins, char *cmd);

// parse/expander/handle_dollar.c
char							*handle_dollar(char *str, t_info *info);

// parse/expander/expander.c
char							*expand(char *str);
char							*translate(char *str, char **env, t_info *info);
bool							check_translate(char *str);

// parse/expander/utils_expander.c
int								get_varname_len(char *str);
char							*get_var_name(char *str, int *i);
int								size_to_var(char *str);

// parse/init/init.c
void							copy_env(char ***my_env, char **env);
void							init_io(t_io *io);
void							init(t_info *info);
void							update_status(t_info *info,
									unsigned int status);

// parse/utils_init.c
void							fill_all(t_info *info);

// parse/tree/syntax_tree.c
int								is_valid_redirection(const char *token,
									t_info *info);
int								has_invalid_redirection(char **tokens,
									t_info *info);

// parse/tree/tree.c
t_tree							*creat_op_node(char **tokens, int *index,
									t_info *info);
t_tree							*create_node(char **tokens);

// parse/utils_tree.c
int								search_ops(char **tokens);
t_node_type						find_type(char **tokens, int i);
t_tree							*parse_tokens(char **tokens, t_info *info);
char							**dup_args(char **tokens);

// parse/parse_utils.c
int								size_woutquotes(char *str);
void							handle_quotes(char *str, char *new, int i,
									int *j);
char							**new_input(char *input);
t_io							*alloc_io(void);

// parse/parse.c
t_tree							*build_tree_tokens(char **tokens, t_info *info);
void							remove_empty_tokens(char ***tokens);
void							parse(char *input, t_info *info);

// parse/quotes.c
int								check_quotes(char *input);
char							*remove_quotes(char *str);
void							remove_all_quotes(char **tokens);

// parse/utils_quotes.c
char							*add_spaces_around(char *str);
void							add_space_operators(char **str);
int								count_non_empty(char **tokens);
void							copy_non_empty(char **src, char **dst);
void							print_syntax_error_token(t_tree *node,
									char **tokens, t_info *info);

// processes/main_process.c
void							child_process(t_info *info);

// processes/processes.c
void							exec_child_process(t_info *info);
void							handle_exec_failure(t_info *info, char *cmd,
									int exit_code);
void							exec(t_info *info, t_tree *node);

// processes/utils.c
char							*get_env(char *variable_name, char **env);
char							*find_path(t_info *info, char *cmd);
int								is_directory(char *path);
// redirections/heredocs.c
void							handle_heredoc_child(t_io *io, t_info *info,
									int fd[2]);
void							handle_heredoc_parent(t_io *io, t_info *info,
									int fd[2], pid_t pid);
void							handle_heredoc_redirection(t_io *io,
									t_info *info);
int								process_heredoc_args(t_tree *node,
									t_info *info);
void							prepare_heredocs(t_tree *node, t_info *info);

// redirections/redir_utils.c
void							restore_io(t_io *io);
void							restore_redirections(int saved_in,
									int saved_out);
void							handle_redir_error(t_info *info);
void							print_heredoc_eof(t_io *io, char *line);

// redirections/redirections.c
int								handle_output_redirection(t_io *io,
									t_info *info);
int								handle_input_redirection(t_io *io,
									t_info *info);
int								handle_append_redirection(t_io *io,
									t_info *info);
void							process_redirections(t_tree *node,
									t_info *info);

// redirections/utils_redirections.c
int								is_redir(char **redirs, char *cmd);
bool							has_redirection(t_tree *node);
void							exec_redirs(t_tree *node, t_info *info, int *i);
int								apply_redirections_node(t_tree *node,
									int *saved_in, int *saved_out);

// signals/sigint_received.c
void							sigint_received(t_info *info);
void							handle_child_signals(void);
void							handle_parent_signals(int status, t_info *info);
void							print_newline(int signal);

// signals/signal_handle.c
void							ignore_sigquit(void);
void							handle_sigint(int sig);
void							set_signals_interactive(void);
void							handle_sigint_heredoc(int sig);
void							set_signals_noninteractive(void);

// splits/custom_split.c
char							**custom_ft_split(char const *s);

// splits/split_quotes.c
char							**ft_split_quotes(char *s);

// splits/utils_split_quotes.c
int								count_quotes(char *input);
int								count_word(char *str);

// utils/fds/close_fds.c
void							close_io_fds(t_io *io);
void							close_fds(int i);
void							close_pipe_fds(int *fd);
void							close_and_reset(int *fd);
void							close_heredoc_backups(t_io *io);

// utils/fds/setup_fds.c
void							setup_io_fds(int in, int out);
void							setup_io_from_tree(t_info *info);

// utils/fds/fds.c
void							handle_node_io(t_tree *node);
void							close_heredoc_fds(t_tree *node);

// utils/fds/more_fds.c
void							dup_and_close_fd(int fd, int std_fd,
									const char *err_msg);
void							cleanup_and_exit(t_info *info);
void							update_io_file(t_io *io, char *filename);
void							storing_backup(t_io *io);

// utils/checks.c
int								apply_redirections(t_info *info, int *saved_in,
									int *saved_out);
int								check_builtins(t_info *info);
int								check_redirections(t_info *info);
int								check_redirections_node(t_tree *node,
									t_info *info);

// utils/free.c
void							free_arr(char **arr);
void							free_tree(t_tree *node);
void							free_io_file(t_io *io);
void							free_builtins(t_builtins *builtins);
void							*free_str(char **dest, int i);

// utils/more_utils.c
void							remove_redir_tokens(char **args, int i);
int								is_valid_append_token(const char *token);

// utils/utils_bools.c
bool							is_quote(char c);
int								is_operator(const char *str);
int								is_operator_char(char c);
int								is_double_operator(char *str);

// utils.c
char							*reverse_strchr(char *str, int c);
void							change_shlvl(char ***env, char *name);

// main.c
void							start(t_info *info);

#endif
