SRCS =  src/main.c \
		src/builtins/ft_echo.c \
		src/builtins/ft_env.c \
		src/builtins/ft_cd.c \
		src/builtins/ft_exit.c \
		src/builtins/ft_pwd.c \
		src/builtins/ft_export/ft_export.c \
		src/builtins/ft_export/ft_export_wrapper.c \
		src/builtins/ft_export/export_utils.c \
		src/builtins/ft_export/export_utils_utils.c \
		src/builtins/ft_export/export_aux_functions.c \
		src/builtins/ft_unset.c \
		src/builtins/ft_pipe/ft_pipe.c \
		src/builtins/ft_pipe/ft_pipe_utils.c \
		src/builtins/ft_pipe/handlers.c \
		src/builtins/utils_builtins.c \
		src/parse/expander/handle_dollar.c\
		src/parse/expander/expander.c\
		src/parse/expander/utils_expander.c\
		src/parse/init/init.c \
		src/parse/init/utils_init.c \
		src/parse/parse.c \
		src/parse/parse_utils.c \
		src/parse/quotes.c \
		src/parse/utils_quotes.c \
		src/parse/tree/syntax_tree.c \
		src/parse/tree/tree.c \
		src/parse/tree/utils_tree.c \
		src/processes/main_process.c\
		src/processes/processes.c\
		src/processes/utils.c\
		src/redirections/heredocs.c\
		src/redirections/redirections.c\
		src/redirections/redir_utils.c\
		src/redirections/utils_redirections.c\
		src/signals/signal_handle.c\
		src/splits/custom_split.c\
		src/splits/split_quotes.c \
		src/splits/utils_split_quotes.c \
		src/utils/checks.c \
		src/utils/free.c \
		src/utils/more_utils.c \
		src/utils/utils_bools.c \
		src/utils/utils.c \
		src/utils/fds.c \
		src/utils/more_fds.c \
		
NAME = minishell

COMPRESS = ar rcs

RM = rm -f

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

RDL_FLAGS = -lreadline 

OBJ_DIR = obj

# Lista de arquivos .o correspondentes aos .c
OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = ./libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a

RESET   = \033[0m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
RED     = \033[31m

all: $(NAME) $(LIBFT)

# Regra para criar o executável a partir dos arquivos objeto e bibliotecas
$(NAME): $(OBJS) $(LIBFT)
	@echo "$(YELLOW)compiling $(NAME) ...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(RDL_FLAGS)
	@echo "$(GREEN)$(NAME) ready! $(RESET)"

# Regra para compilar arquivos objeto a partir de arquivos fonte, cria a pasta para o arq obj se nao existir
$(OBJ_DIR)/%.o: src/%.c | $(CREATE_DIR)
	@mkdir -p $(@D)
	@echo "$(BLUE)making objs directorys!$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(CREATE_DIR):
	@mkdir -p $(OBJ_DIR)/src

$(LIBFT):
	@echo "$(YELLOW)compiling LIBFT ...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

v: re
	valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --track-origins=yes --show-reachable=yes --suppressions=.readline.supp ./$(NAME)

clean:
	@echo "$(RED)cleaning objs ...$(RESET)"
	@$(RM) -r $(OBJ_DIR)	# Remove o diretório obj e seu conteúdo
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo "$(RED)objs && libs cleaned! $(RESET)"

fclean: clean
	@$(RM) $(NAME)  # Remove o executável
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(RED)$(NAME) removed! $(RESET)"

re: fclean all

.PHONY: all clean fclean re