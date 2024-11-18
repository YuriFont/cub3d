NAME = cub3D

VALIDATION = validate_map.c\
				validate_map_utils.c\
				check_around.c\
				validate_cub.c\
				validate_utils.c

FILL_STRUCT = fill_struct.c\
				fill_struct_utils.c

UTILS = utils.c

INIT_WIN = init_window.c

RAY = ray_casting.c

FILES = main.c\
		$(addprefix utils/, $(UTILS))\
		$(addprefix validation/, $(VALIDATION))\
		$(addprefix fill_struct/, $(FILL_STRUCT))\
		$(addprefix window/, $(INIT_WIN))

LIBFT = ./libs/libft/

LIBFT_A = $(LIBFT)libft.a

LIBMLX = ./libs/minilibx-linux/

LIBMLX_A = $(LIBMLX)libmlx_Linux.a

CC = cc

FLAGS = -Wall -Wextra -Werror

MLXFLAGS = -Lmlx -lXext -lX11

RM = rm -rf

all: $(NAME)

$(LIBFT_A):
			$(MAKE) -C $(LIBFT)

$(LIBMLX_A):
			$(MAKE) -C $(LIBMLX)

$(NAME): $(LIBFT_A) $(LIBMLX_A)
			$(CC) $(CFLAGS) $(addprefix ./src/, $(FILES)) $(LIBFT_A) $(LIBMLX_A) $(MLXFLAGS) -o $(NAME)

clean:
			$(MAKE) clean -C $(LIBFT)
			$(MAKE) clean -C $(LIBMLX)

fclean: clean
			$(MAKE) fclean -C $(LIBFT)
			$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re