/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellinho.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 23:23:23 by rafael            #+#    #+#             */
/*   Updated: 2025/03/06 19:10:04 by dsteiger         ###   ########.fr       */
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
# include <string.h>
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
# define MAX_TYPES 8
# define MAX_REDS 5

# define SPACES " \n\t\v\f\r"

typedef struct s_info	t_info;
// typedef struct s_type
// {
// 	char	*types[MAX_TYPES];
// 	void	(*f[MAX_TYPES])(t_info *info);
// }			t_type;

typedef struct s_io		t_io;

typedef struct s_builtins
{
	char				*builtins[MAX_BUILTINS];
	void				(*f[MAX_BUILTINS])(t_info *info);
}						t_builtins;

/* typedef struct s_args
{
	char **args;
	t_type

}			t_args; */

typedef struct s_reds
{
	char				*reds[MAX_REDS];
	void				(*f[MAX_REDS])(t_io *io);
}						t_reds;

typedef struct s_io
{
	int fd_in;  // this is the new STDIN_FILENO.  It represents the opened file in_file
	int fd_out; // this is the new STDOUT_FILENO. It represents the opened file out_file
	int					stdin_backup;
	int stdout_backup; // Backup and restore original file descriptors to prevent unwanted redirections for the next command.
	char *in_file;     // alocar memoria pra ambos: infile e outfile
	char *out_file;    // ex: echo "Hello" > outfile.txt  -> hello will be written in outfile.txt,instead of the terminal as STDOUT
	t_reds				*redirections;
}						t_io;

typedef struct s_info
{
	char				**args;
	char				*flags;
	char				**my_env;
	t_builtins			*builtins;
	t_io				io;
	// t_type *types;
}						t_info;

extern					int command_running;

// builtins/echo
int						check_flags(char *str);
void					ft_echo(t_info *info);

// builtins/env
void    				ft_env(t_info *info);

// builtins/cd
void 					cd_with_arg(const char *path);
int                     count_levels(const char *arg);
void					ft_cd_doispontos(t_info *info, int levels);
void					ft_cd_home(t_info *info);
void					ft_cd(t_info *info);

// builtins/exit
void					ft_exit(t_info *info);
void					ft_pwd(t_info *info);
void					sort_env(char **args);

// builtins/export
void					sort_env(char **args);
void					add_to_my_env(t_info *info, char *str);
char					**create_sorted_env_copy(char **args);
void					ft_export(t_info *info);

// builtins/unset
void					ft_unset(t_info *info);

// parse/handle_dollar
char					*handle_dollar(char *str, char **env);

// parse/expander
int						get_varname_len(char *str);
char					*expand(char *str);
char					*translate(char *str, char **env);
int						size_to_var(char *str);
bool					check_translate(char *str);

// parse/init
void					copy_env(t_info *info, char **env);
void					init(t_info *info, char **env);

// parse/parse
int						size_woutquotes(char *str);
void					handle_quotes(char *str, char *new, int i, int *j);
char					**new_input(char *input);
void					parse(char *input, t_info *info);

// parse/quotes
int						check_quotes(char *input);
void					remove_all_quotes(t_info *info);

// processes
void					child_process(t_info *info);
void					exec(t_info *info);

// processes/utils
char					*find_path(t_info *info);
char					*get_env(char *variable_name, char **env);

// redirections
void					fill_redirections(t_io *io);
void					handle_input_redirection(t_io *io);
void					handle_output_redirection(t_io *io);
void					handle_append_redirection(t_io *io);
void					storing_backup(t_io *io);
void					restore_io(t_io *io);
void					execute_command(t_info *info);

// signals
void					handle_sigint(int sig);
void					handle_sigquit(int sig);
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

// utils
void					close_fds(int i);
void					print_banner(void);
void					error_exit(char *msg);
void					free_arr(char **arr);
int						check_builtins(t_info *info);
void					clean(t_info *info);
char					*ft_strncpy(char *dest, char *src, unsigned int n);

// main
void					start(t_info *info);
void					free_builtins(t_builtins *builtins);

#endif