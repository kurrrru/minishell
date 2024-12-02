# executable
NAME			= 	minishell

# source files
SRCS_BUILTIN	=	bi_cd.c \
					bi_echo.c \
					bi_env.c \
					bi_exit.c \
					bi_export.c \
					bi_export_util.c \
					bi_pwd.c \
					bi_unset.c \
					exec_builtin.c \
					update_env.c
SRCS_CONFIG		=	free_config.c \
					ft_realloc_env.c \
					init_config.c
SRCS_EXEC		=	exec_bi.c \
					exec_command.c \
					exec_command_bi.c \
					exec_logical_and.c \
					exec_pipe.c \
					exec_pipe_left_cmd.c \
					exec_pipe_left_con.c \
					free_exec.c \
					get_path.c \
					is_directory.c \
					make_envp.c \
					perror_exit.c \
					redirect_handler.c \
					run_node.c \
					run_tree.c
SRCS_EXPANDER	=	del_quote.c \
					expand_command_node.c \
					expand_env.c \
					expand_env_heredoc_content.c \
					expand_len.c \
					expander.c \
					expander_quote.c \
					find_env.c \
					wildcard.c \
					wildcard_get_files_in_directory.c \
					wildcard_is_match.c \
					wildcard_sort_strings.c
SRCS_LEXER		=	assign_token_type.c \
					free_data.c \
					lexer.c \
					lexer_split.c \
					lexer_util.c
SRCS_PARSER		=	free_tree.c \
					ft_realloc_redirect.c \
					new_command_node.c \
					new_connecter_node.c \
					parse_command.c \
					parse_connector.c \
					parse_data.c \
					parse_heredoc.c \
					parse_paren_left.c \
					parse_paren_right.c \
					parse_redirect.c \
					parser.c
SRCS_SIGNAL		=	check_core_dump.c \
					signals.c \
					signals_handler.c
SRCS_UTIL		=	extract_status.c \
					free_2d.c \
					free_3d.c \
					ft_realloc.c \
					ft_realloc_char.c \
					ft_strcmp.c
SRCS			=	src/main.c \
					src/main_loop.c \
					$(addprefix src/builtin/, $(SRCS_BUILTIN)) \
					$(addprefix src/config/, $(SRCS_CONFIG)) \
					$(addprefix src/exec/, $(SRCS_EXEC)) \
					$(addprefix src/expander/, $(SRCS_EXPANDER)) \
					$(addprefix src/lexer/, $(SRCS_LEXER)) \
					$(addprefix src/parser/, $(SRCS_PARSER)) \
					$(addprefix src/signals/, $(SRCS_SIGNAL)) \
					$(addprefix src/util/, $(SRCS_UTIL))


# object files
OBJS			=	$(SRCS:.c=.o)

# compiler
CC				=	cc

# libraries
LIBFT_DIR		=	libft
LIBFT_NAME		=	libft.a
LIBFT			=	$(LIBFT_DIR)/$(LIBFT_NAME)

# include
INCLUDE_DIR		= 	include

# flags
CFLAGS			=	-Wall -Wextra -Werror -I$(LIBFT_DIR) -I$(INCLUDE_DIR)
LFLAGS			=	-Wall -Wextra -Werror -L$(LIBFT_DIR) -lft -lreadline
SANITIZE		=	-fsanitize=address

# CFLAGS			+=	$(SANITIZE)
# LFLAGS			+=	$(SANITIZE)

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
