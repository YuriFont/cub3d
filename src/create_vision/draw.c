/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:06:40 by yufonten          #+#    #+#             */
/*   Updated: 2025/02/22 16:06:43 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	draw_sky(t_cub *cub, int x, t_ray_info *infos)
{
	int	y;
	int	*pixels;

	pixels = (int *)cub->i_img.img_data;
	y = -1;
	while (y++ < infos->wall_start)
		pixels[y * WIDTH + x] = 0x87CEEB;
	return (1);
}

int	draw_floor(t_cub *cub, int x, t_ray_info *infos)
{
	int	y;
	int	*pixels;

	pixels = (int *)cub->i_img.img_data;
	y = infos->wall_end - 1;
	while (y++ < HEIGHT)
		pixels[y * WIDTH + x] = 0x228B22;
	return (1);
}

void	draw_wall(t_cub *cub, int x, t_ray_info *infos, t_img *texture)
{
	int	y;
	int	color;
	int	tex_y;
	int	*pixels;

	pixels = (int *)cub->i_img.img_data;
	y = infos->wall_start;
	while (y < infos->wall_end)
	{
		tex_y = get_texture_pos_y(infos, texture, infos->tex_pos);
		color = get_texture_color(texture, infos->tex_x, tex_y, cub);
		if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH)
			pixels[y * WIDTH + x] = color;
		infos->tex_pos += infos->step;
		y++;
	}
}
