# Program file name
NAME	= minishell

# Compiler and compilation flags
CC		= clang
CFLAGS	= -Werror -Wextra -Wall

# Build files and directories
SRC_PATH = ./sources/
OBJ_PATH = ./objects/
INC_PATH = ./includes/
SRC		= 	main.c \
			init_data.c \
			env/env.c \
			env/env_set.c \
			lexer/tokenization.c \
			lexer/check_if_var.c \
			lexer/lexer_utils.c \
			lexer/token_lst_utils.c \
			lexer/token_lst_utils_2.c \
			lexer/var_tokenization.c \
			parser/var_expander.c \
			parser/identify_var.c \
			parser/quotes_handler.c \
			parser/quotes_remover.c \
			parser/recover_value.c \
			parser/replace_var.c \
			parser/create_commands.c \
			parser/parse_word.c \
			parser/fill_arguments.c \
			parser/parse_input.c \
			parser/parse_trunc.c \
			parser/parse_append.c \
			parser/parse_heredoc.c \
			parser/parse_pipe.c \
			parser/cmd_lst_utils.c \
			builtins/export_builtin.c \
			builtins/unset_builtin.c \
			builtins/cd_builtin.c \
			builtins/env_builtin.c \
			builtins/pwd_builtin.c \
			builtins/echo_builtin.c \
			builtins/exit_builtin.c \
			execution/execute.c \
			execution/parse_path.c \
			redirections/pipe.c \
			redirections/file_io.c \
			exit_utils/exit.c \
			exit_utils/error.c \
			exit_utils/cleanup.c \
			exit_utils/free_data.c \
			signals/signal.c
SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
INC		= -I $(INC_PATH) -I $(LIBFT_PATH)

# Libft files and directories
LIBFT_PATH = ./libft/
LIBFT = ./libft/libft.a

# Main rule
all: $(OBJ_PATH) $(LIBFT) $(NAME)

# Objects directory rule
$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)/builtins
	mkdir -p $(OBJ_PATH)/lexer
	mkdir -p $(OBJ_PATH)/parser
	mkdir -p $(OBJ_PATH)/testing
	mkdir -p $(OBJ_PATH)/env
	mkdir -p $(OBJ_PATH)/execution
	mkdir -p $(OBJ_PATH)/exit_utils
	mkdir -p $(OBJ_PATH)/redirections
	mkdir -p $(OBJ_PATH)/signals

# Objects rule
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

# Project file rule
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC) $(LIBFT) -lreadline

# Libft rule
$(LIBFT):
	make -C $(LIBFT_PATH)

# Clean up build files rule
clean:
	rm -rf $(OBJ_PATH)
	make -C $(LIBFT_PATH) clean

# Remove program executable
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

# Clean + remove executable
re: fclean all

.PHONY: all re clean fclean