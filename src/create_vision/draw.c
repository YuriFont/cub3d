/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:06:40 by yufonten          #+#    #+#             */
/*   Updated: 2025/04/14 23:01:21 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

unsigned int	int_to_hex(int r, int g, int b)
{
	unsigned int	hex;

	hex = (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
	return (hex);
}

int	draw_sky(t_cub *cub, int x, t_ray_info *infos)
{
	int	y;
	int	*pixels;

	pixels = (int *)cub->i_img.img_data;
	y = -1;
	while (y++ < infos->wall_start)
	{
		pixels[y * WIDTH + x] = int_to_hex(cub->i_tex.cc[0],
				cub->i_tex.cc[1], cub->i_tex.cc[2]);
	}
	return (1);
}

int	draw_floor(t_cub *cub, int x, t_ray_info *infos)
{
	int	y;
	int	*pixels;

	pixels = (int *)cub->i_img.img_data;
	y = infos->wall_end - 1;
	while (y++ < HEIGHT)
	{
		pixels[y * WIDTH + x] = int_to_hex(cub->i_tex.cf[0],
				cub->i_tex.cf[1], cub->i_tex.cf[2]);
	}
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
