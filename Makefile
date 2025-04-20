NAME = cub3D

VALIDATION = validate_map.c\
				validate_map_utils.c\
				check_around.c\
				validate_cub.c\
				validate_utils.c\
				validate_cub_utils.c 

FILL_STRUCT = fill_struct.c\
				fill_struct_utils.c\
				load_game.c\
				load_texture.c

UTILS = utils.c

INIT_WIN = init_window.c

CREATE_VISION = create_vision.c\
				raycasting.c\
				render.c\
				render_utils.c\
				draw.c

MOVEMENT = key_handles.c\
		   move_handles.c\
		   rotate_handles.c

FILES = main.c\
		$(addprefix utils/, $(UTILS))\
		$(addprefix validation/, $(VALIDATION))\
		$(addprefix fill_struct/, $(FILL_STRUCT))\
		$(addprefix window/, $(INIT_WIN))\
		$(addprefix create_vision/, $(CREATE_VISION))\
		$(addprefix movement/, $(MOVEMENT))\
		loop_game.c\

LIBFT = ./libs/libft/

LIBFT_A = $(LIBFT)libft.a

LIBMLX = ./libs/minilibx-linux/

LIBMLX_A = $(LIBMLX)libmlx_Linux.a

CC = gcc -g

FLAGS = -Wall -Wextra -Werror

MLXFLAGS = -Lmlx -lXext -lX11

RM = rm -rf

all: $(NAME)

$(LIBFT_A):
			$(MAKE) -C $(LIBFT)

$(LIBMLX_A):
			$(MAKE) -C $(LIBMLX)

$(NAME): $(LIBFT_A) $(LIBMLX_A)
			$(CC) $(CFLAGS) $(addprefix ./src/, $(FILES)) $(LIBFT_A) $(LIBMLX_A) $(MLXFLAGS) -o $(NAME)  -lm

clean:
			$(MAKE) clean -C $(LIBFT)
			$(MAKE) clean -C $(LIBMLX)

fclean: clean
			$(MAKE) fclean -C $(LIBFT)
			$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re