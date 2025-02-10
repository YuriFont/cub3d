/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/09/14 12:14:09 by yufonten          #+#    #+#             */
/*   Updated: 2024/09/14 12:14:09 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/libft/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// # define HEIGHT 480
// # define WIDTH 640
# define HEIGHT 600
# define WIDTH 800
# define ROTSPEED 0.03
# define MOVSPEED 0.05

typedef struct s_tex
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		cf[3];
	int		cc[3];
}			t_tex;

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
}			t_map;

typedef struct s_win
{
	int		w_width;
	int		w_height;
}			t_win;

typedef struct s_move
{
	int		up;
	int		down;
	int		left;
	int		right;
	int		rot_left;
	int		rot_right;
}			t_move;

typedef struct s_img
{
	void			*img_ptr;
	unsigned char	*img_data;
	int				bpp;
	int				line_len;
	int				endian;
	int				width;
	int				height;
}			t_img;

typedef struct s_p
{
	double	pos_x;
	double	pos_y;
	double	dir[2];
	double	plane[2];
}			t_p;

typedef struct s_cub
{
	int		fd_cub;
	t_tex	i_tex;
	t_map	i_map;
	t_win	i_win;
	t_img	i_img;
	t_img	tex_north;
	t_img	tex_south;
	t_img	tex_east;
	t_img	tex_west;
	t_p		i_p;
	t_move	move;
	void	*ptr_mlx;
	void	*w_mlx;
}			t_cub;

typedef struct s_rayInfo
{
	double	camera_x;		// Posição do raio no plano da câmera (-1 a 1)
	double	ray_dir_x;		// Direção X do raio
	double	ray_dir_y;		// Direção Y do raio
	double	delta_dist_x;	// Distância entre cada interseção em X
	double	delta_dist_y;	// Distância entre cada interseção em Y
	double	side_dist_x;	// Distância inicial até a primeira interseção em X
	double	side_dist_y;	// Distância inicial até a primeira interseção em Y
	double	perp_wall_dist;	// Distância perpendicular até a parede
	int		map_x;			// Posição X no mapa onde o raio está
	int		map_y;			// Posição Y no mapa onde o raio está
	int		step_x;			// Direção do passo em X (-1 ou 1)
	int		step_y;			// Direção do passo em Y (-1 ou 1)
	int		side;			// Indica se o impacto foi em X (0) ou Y (1)
	int		wall_start;
	int		wall_end;
	int		line_height;
}			t_rayInfo;

// utils
// utils.c
int			error(t_cub *cub, char *msg, int flag);
int			final_free(t_cub *cub);
void		free_matriz(char **mat);
// validation
// validate_cub.c
void		validate_cub(t_cub *cub, char *file);
// validate_utils.c
void		validate_extension_cub(char *file);
int			validate_extension_xpm(char *file);
int			validate_hx(char *num);
int			size_rgb(char **n);
// validate_map.c
void		validate_map(t_cub *cub);
// validate_map_utils.c
void		check_character(t_cub *cub, char c);
void		validate_spaces(t_cub *cub);
void		validate_unevenness_bot(t_cub *cub);
void		validate_unevenness_top(t_cub *cub);
// check_around.c
int			check_around(char **map, int y, int x, int h);
// fill_struct
// fill_struct.c
void		fill_struct(t_cub *cub, char *file);
void		fill_map(t_cub *cub);
// fil_struct_utils.c
void		fill_player_info(t_cub *cub);
// window
// init_window.c
void		initializing_window(t_cub *cub);
void		fill_player_info(t_cub *cub);
// create_vision.c
void		create_vision(t_cub *cub);
void		create_img(t_cub *cub);

// raycasting.c
void		calculate_dir(t_cub *cub, t_rayInfo *infos, int x);
int			get_player_position(t_cub *cub, t_rayInfo *infos);
int			get_delta_dist_x_and_y(t_rayInfo *infos);
int			get_side_dist(t_cub *cub, t_rayInfo *infos);
int			find_wall(t_cub *cub, t_rayInfo *infos);
int			calculate_perpendicular(t_cub *cub, t_rayInfo *infos);
int			calculate_wall_height(t_rayInfo *infos);
void		draw_line(t_cub *cub, t_rayInfo *infos, int x);

#endif