/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/11/18 20:57:56 by yufonten          #+#    #+#             */
/*   Updated: 2024/11/18 20:57:56 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	create_img(t_cub *cub)
{
	cub->i_img.img_ptr = mlx_new_image(cub->ptr_mlx, WIDTH, HEIGHT);
	cub->i_img.width = WIDTH;
	cub->i_img.height = HEIGHT;
	if (cub->i_img.img_ptr == NULL)
		error(cub, "Error: cannot create image\n", 1);
	cub->i_img.img_data = (unsigned char *)mlx_get_data_addr(cub->i_img.img_ptr,
			&cub->i_img.bpp, &cub->i_img.line_len, &cub->i_img.endian);
	if (cub->i_img.img_data == NULL)
		error(cub, "Error: cannot get data of image\n", 1);
}

void	put_pixel(t_cub *cub, int x, int y, int color)
{
	int	pixel;

	if (x < 0 || x >= cub->i_win.w_width || y < 0 || y >= cub->i_win.w_height)
		return ;
	pixel = (y * cub->i_img.line_len) + (x * (cub->i_img.bpp / 8));
	cub->i_img.img_data[pixel] = color & 0xFF;
	cub->i_img.img_data[pixel + 1] = (color >> 8) & 0xFF;
	cub->i_img.img_data[pixel + 2] = (color >> 16) & 0xFF;
}

int	calculate_perpendicular(t_cub *cub, t_ray_info *infos)
{
	if (infos->side == 0)
		infos->perp_wall_dist = (infos->side_dist_x - infos->delta_dist_x);
	else
		infos->perp_wall_dist = (infos->side_dist_y - infos->delta_dist_y);
}

int	create_dda_vision(t_cub *cub)
{
	t_ray_info	infos;
	int			x;

	x = 0;
	while (x < WIDTH)
	{
		calculate_dir(cub, &infos, x);
		get_player_position(cub, &infos);
		get_delta_dist_x_and_y(&infos);
		get_side_dist(cub, &infos);
		find_wall(cub, &infos);
		calculate_perpendicular(cub, &infos);
		calculate_wall_height(&infos);
		draw_line(cub, &infos, x);
		x++;
	}
	return (0);
}
