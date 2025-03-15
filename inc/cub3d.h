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
# include <sys/time.h>

# define HEIGHT 600
# define WIDTH 800
# define ROTSPEED 0.01
# define MOVSPEED 0.01

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
	t_img	frames[10];
	t_p		i_p;
	t_move	move;
	void	*ptr_mlx;
	void	*w_mlx;
}			t_cub;

typedef struct s_ray_info
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		wall_start;
	int		wall_end;
	int		line_height;
	double	wall_x;
	double	step;
	double	tex_pos;
	double	tex_x;
}			t_ray_info;

int			error(t_cub *cub, char *msg, int flag);
int			final_free(t_cub *cub);
void		free_matriz(char **mat);
void		validate_cub(t_cub *cub, char *file);
void		validate_extension_cub(char *file);
int			validate_extension_xpm(char *file);
int			validate_hx(char *num);
int			size_rgb(char **n);
void		validate_map(t_cub *cub);
void		check_character(t_cub *cub, char c);
void		validate_spaces(t_cub *cub);
void		validate_unevenness_bot(t_cub *cub);
void		validate_unevenness_top(t_cub *cub);
int			check_around(char **map, int y, int x, int h);
void		fill_struct(t_cub *cub, char *file);
void		fill_map(t_cub *cub);
void		fill_player_info(t_cub *cub);
void		initializing_window(t_cub *cub);
void		fill_player_info(t_cub *cub);
int			create_dda_vision(t_cub *cub);
void		create_img(t_cub *cub);
int			get_texture_pos_y(t_ray_info *infos, t_img *texture,
				double tex_pos);
int			calculate_wall_height(t_ray_info *infos);
int			get_texture_color(t_img *texture, int tex_x, int tex_y, t_cub *cub);
t_img		*select_texture(t_cub *cub, t_ray_info *infos);
int			draw_floor(t_cub *cub, int x, t_ray_info *infos);
int			draw_sky(t_cub *cub, int x, t_ray_info *infos);
void		draw_wall(t_cub *cub, int x, t_ray_info *info, t_img *texture);
void		calculate_dir(t_cub *cub, t_ray_info *infos, int x);
int			get_player_position(t_cub *cub, t_ray_info *infos);
int			get_delta_dist_x_and_y(t_ray_info *infos);
int			get_side_dist(t_cub *cub, t_ray_info *infos);
int			find_wall(t_cub *cub, t_ray_info *infos);
int			calculate_perpendicular(t_cub *cub, t_ray_info *infos);
int			calculate_wall_height(t_ray_info *infos);
void		draw_line(t_cub *cub, t_ray_info *infos, int x);
int			on_keypress(int key, t_cub *cub);
int			on_keyrelease(int key, t_cub *cub);
int			move_player(t_cub *cub);
int			move_left(t_cub *cub);
int			move_right(t_cub *cub);
int			move_forward(t_cub *cub);
int			move_backward(t_cub *cub);
int			rotate_right(t_cub *cub);
int			rotate_left(t_cub *cub);
int			get_mouse_pos(void *ptr);
int			animation_wall(t_cub *cub);
int			run_code(t_cub *cub);
void		load_image_texture(t_cub *cub, t_img *texture, char *path);
int			load_texture(t_cub *cub);
void		loading_game(t_cub *cub, char *av);
int			initial_config(t_cub *cub, char *av);

#endif