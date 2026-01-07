SRC = utils/math_utils.c \
	tuple_mtx_ops/build_transfo_mtx.c \
	tuple_mtx_ops/matrix_inversion.c \
	tuple_mtx_ops/matrix_ops.c \
	tuple_mtx_ops/transformation_mtx.c \
	tuple_mtx_ops/tuple_ops.c \
	tuple_mtx_ops/vector_ops.c \

CC = cc
FLAGS = -Wall -Werror -Wextra -g
INCLUDE = -lmlx
NAME = minirt
