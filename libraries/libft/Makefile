SRCS =	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c \
        ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
        ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
        ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_atol.c ft_calloc.c ft_strdup.c ft_substr.c \
        ft_strjoin.c ft_strtrim.c ft_split.c  ft_strmapi.c ft_putchar_fd.c \
        ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_striteri.c ft_itoa.c ft_strncpy.c is_space.c\


LST	=	ft_lstnew.c \
        ft_lstadd_front.c \
        ft_lstsize.c \
        ft_lstlast.c \
        ft_lstadd_back.c \
        ft_lstdelone.c \
        ft_lstclear.c \
        ft_lstiter.c \
        ft_lstmap.c

NAME = libft.a

COMPRESS = ar rcs

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

CC = cc

OBJS = $(SRCS:.c=.o) 

BONUS_OBJS = $(LST:.c=.o)

all: $(NAME)

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@


$(NAME): $(OBJS) $(BONUS_OBJS)
	@$(COMPRESS) $(NAME) $(OBJS) $(BONUS_OBJS)
	@echo "$(NAME) ready!"

clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all