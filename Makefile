NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I$(INC_DIR)

INC_DIR = inc
SRC_DIR = src
OBJ_DIR = obj

SRC := $(addprefix $(SRC_DIR)/, \
    main.c \
    events.c \
    utils.c \
    init.c \
    $(addprefix map/, \
        map.c \
        colors.c \
        textures.c \
        content.c \
        content_check.c \
    ) \
    $(addprefix raycasting/, \
        drawing.c \
        raycasting.c \
    ) \
)

OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLXFLAGS = -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft $(MLXFLAGS)
	@echo "cub3D compiled"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)
	@echo "libft compiled"

$(MLX):
	@$(MAKE) -s -C $(MLX_DIR) > /dev/null 2>&1
	@echo "mlx compiled"

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -s clean -C $(LIBFT_DIR)
	@$(MAKE) -s clean -C $(MLX_DIR) > /dev/null 2>&1
	@echo "cub3D removed"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s fclean -C $(LIBFT_DIR)
	@echo "cub3D removed"

re: fclean all

val: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) maps/minimalist.cub

.PHONY: all clean fclean re