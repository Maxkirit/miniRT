SRC = utils/math_utils.c \
	parsing/parse_file.c \
	parsing/parsing_utils.c \
	tuple_mtx_ops/build_transfo_mtx.c \
	tuple_mtx_ops/matrix_inversion.c \
	tuple_mtx_ops/matrix_ops.c \
	tuple_mtx_ops/transformation_mtx.c \
	tuple_mtx_ops/tuple_ops.c \
	tuple_mtx_ops/vector_ops.c \
	mlx_functions/render_utils.c \
	mlx_functions/mlx_event_handling.c \
	intersections/intersections.c \
	intersections/intersections_utils.c \
	raytracer.c \
	main.c

NAME = minirt

CC = cc
FLAGS = -Wall -Werror -Wextra -g
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX = mlx/libmlx_Linux.a
LINKS = $(LIBFT) -Lmlx -lmlx_Linux -lXext -lX11 -lm -lz
OBJ_DIR = objects
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LINKS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C mlx

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR) #for main.c
	$(CC) $(FLAGS) -Imlx -c $< -o $@

$(OBJ_DIR)/%.o: parsing/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -Imlx -c $< -o $@

$(OBJ_DIR)/%.o: tuple_mtx_ops/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -Imlx -c $< -o $@

$(OBJ_DIR)/%.o: mlx_functions/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -Imlx -c $< -o $@

$(OBJ_DIR)/%.o: intersections/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -Imlx -c $< -o $@

$(OBJ_DIR)/%.o: utils/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -Imlx -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C mlx
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re