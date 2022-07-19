# Program file name
NAME	= minishell

# Compiler and compilation flags
CC		= clang
CFLAGS	=  -lreadline -Werror -Wextra -Wall

# Build files and directories
SRC_PATH = ./sources/
OBJ_PATH = ./objects/
SRC		= 	main.c \
			test.c \
			exit.c \
			builtins/env.c \
			builtins/pwd.c \
			builtins/echo.c
SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
INC		= -I ./includes/ -I ./libft/

# Libft files and directories
LIBFT_PATH = ./libft/
LIBFT = ./libft/libft.a

# Main rule
all: $(OBJ_PATH) $(LIBFT) $(NAME)

# Objects directory rule
$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)/builtins

# Objects rule
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

# Project file rule
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBFT)

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