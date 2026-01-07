SRC = utils/math_utils.c \
	tuple_mtx_ops/build_transfo_mtx.c \
	tuple_mtx_ops/matrix_inversion.c \
	tuple_mtx_ops/matrix_ops.c \
	tuple_mtx_ops/transformation_mtx.c \
	tuple_mtx_ops/tuple_ops.c \
	tuple_mtx_ops/vector_ops.c \

NAME = minirt

CC = cc
FLAGS = -Wall -Werror -Wextra -g
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LINKS = $(LIBFT) -Lmlx_linux -lmlx_Linux -lXext -lX11 -lm -lz
OBJ_DIR = objects
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LINKS) -o $(NAME)

$(LIBFT):
	make -C ($LIBFT_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR) #for main.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(OBJ_DIR)/%.o: tuple_mtx_ops/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(OBJ_DIR)/%.o: utils/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re