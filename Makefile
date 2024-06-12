NAME = cub3D

CC = cc
CFLAGS = -Wall -Werror -Wextra #-fsanitize=address

SRC_DIR = src
INC_DIR = inc
OBJ_DIR = .obj
LFT_DIR = libft

SRC_FILES = main.c
INC_FILES =

LIB = -L minilibx-linux -lmlx -lXext -lX11

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
HDRS = $(addprefix $(INC_DIR)/, $(INC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))
LIBFT = $(LFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(HDRS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIB) -o $(NAME)
	@echo "Compiled!"

$(LIBFT):
	@make --no-print-directory -C $(LFT_DIR)
	@echo $(GREEN)"Compiled Libft!"$(NC)

$(OBJ_DIR)/%.o: %.c $(HDRS)
	@mkdir -p $(OBJ_DIR)/$(dir $<)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean --no-print-directory -C $(LFT_DIR)
	@rm -rf $(OBJS) $(OBJ_DIR)
	@echo "Object files removed"

fclean: clean
	@rm -rf $(LIBFT)
	@echo "Libft removed"
	@rm -rf $(NAME)
	@echo "Executable removed"

re: fclean all

val: all
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(NAME)

.PHONY: all clean fclean re val
