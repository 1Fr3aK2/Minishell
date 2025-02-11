SRCS =  src/main.c \
		src/utils/utils.c \
		src/builtins/ft_echo.c \
		src/builtins/ft_exit.c \
		src/builtins/ft_pwd.c \
		src/parse/parse.c \
		src/parse/init.c \
		src/processes/processes.c\
		src/processes/custom_split.c\
		src/processes/utils.c\
		
NAME = shellinho

COMPRESS = ar rcs

RM = rm -f

CC = cc

CFLAGS = -Wall -Wextra -Werror

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

v: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(NAME)

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