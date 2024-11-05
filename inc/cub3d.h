/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:14:09 by yufonten          #+#    #+#             */
/*   Updated: 2024/09/14 12:14:09 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../libs/libft/libft.h"
# include "../libs/minilibx-linux/mlx.h"

typedef	struct s_tex
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		cf[3];
	int		cc[3];
}	t_tex;

typedef	struct s_map
{
	char	**map;
	int		height;
	int		width;
	double	x_player;
	double	y_player;
}	t_map;

typedef struct s_win
{
	int	w_width;
	int	w_height;
}	t_win;

typedef struct s_cub
{
	int		fd_cub;
	t_tex	tex;
	t_map	i_map;
	t_win	i_win;
	void	*ptr_mlx;
	void	*w_mlx;
}	t_cub;


//utils
//utils.c
void	free_cub(t_cub *cub, int flag);
int	    error(char *msg);
int		final_free(t_cub *cub);
void	free_matriz(char **mat);
//validation
//validate_cub.c
void    validate_cub(t_cub *cub, char *file);
//validate_utils.c
void	validate_extension_cub(char *file);
int		validate_extension_xpm(char *file);
int		validate_hx(char *num);
int		size_rgb(char **n);
//validate_map.c
void	validate_map(t_cub *cub);
//validate_map_utils.c
void	check_character(t_cub *cub, char c);
void	validate_spaces(t_cub *cub);
void	validate_unevenness_bot(t_cub *cub);
void	validate_unevenness_top(t_cub *cub);
//check_around.c
int		check_around(char **map, int y, int x, int h);
//fill_struct
//fill_struct.c
void	fill_map(t_cub *cub);
//window
//init_window.c
void	initializing_window(t_cub *cub);
void    fill_player_info(t_cub *cub);
//ray_casting


#endif
