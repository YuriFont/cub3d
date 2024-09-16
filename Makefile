NAME = cub3D

ERROR = error.c

FILL_STRUCT = fill_struct.c

FILES = main.c\
		$(addprefix error/, $(ERROR))\
		$(addprefix fill_struct/, $(FILL_STRUCT))

LIBFT = ./libs/libft/

LIBFT_A = $(LIBFT)libft.a

LIBMLX = ./libs/minilibx-linux/

LIBMLX_A = $(LIBMLX)libmlx_Linux.a

CC = cc

FLAGS = -Wall -Wextra -Werror -Lmlx -lXext -lX11

RM = rm -rf

all: $(NAME)

$(LIBFT_A):
			$(MAKE) -C $(LIBFT)

$(LIBMLX_A):
			$(MAKE) -C $(LIBMLX)

$(NAME): $(LIBFT_A) $(LIBMLX_A)
			$(CC) $(CFLAGS) $(addprefix ./src/, $(FILES)) $(LIBFT_A) $(LIBMLX_A) -o $(NAME)

clean:
			$(MAKE) clean -C $(LIBFT)
			$(MAKE) clean -C $(LIBMLX)

fclean: clean
			$(MAKE) fclean -C $(LIBFT)
			$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re