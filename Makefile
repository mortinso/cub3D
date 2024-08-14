NAME = cub3D

CC = cc
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address

SRC_DIR = src
INC_DIR = inc
OBJ_DIR = .obj
LFT_DIR = libft

MAP_SRC = map.c colors.c textures.c content.c content_check.c
SRC_FILES = main.c events.c utils.c init.c 2D.c $(addprefix map/, $(MAP_SRC))
INC_FILES = cub3D.h

LIB = -L minilibx-linux -lmlx -lXext -lX11 -lm

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

# --track-fds=yes
val: all
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) maps/minimalist.cub

.PHONY: all clean fclean re val
