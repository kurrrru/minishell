# executable
NAME		= 	minishell

# source files
SRCS		=	$(wildcard src/*/*.c) src/main.c # Change to specify all source files explicitly later

# object files
OBJS		=	$(SRCS:.c=.o)

# compiler
CC			=	cc

# libraries
LIBFT_DIR	=	libft
LIBFT_NAME	=	libft.a
LIBFT		=	$(LIBFT_DIR)/$(LIBFT_NAME)

# include
INCLUDE_DIR	= 	include

# flags
CFLAGS		=	-Wall -Wextra -Werror -I$(LIBFT_DIR) -I$(INCLUDE_DIR)
LFLAGS		=	-Wall -Wextra -Werror -L$(LIBFT_DIR) -lft -lreadline
SANITIZE	=	-fsanitize=address

# CFLAGS		+=	$(SANITIZE)
# LFLAGS		+=	$(SANITIZE)

.DEFAULT_GOAL = all

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) -o $(NAME) $(LFLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

all: $(NAME)

.PHONY: all clean fclean re
