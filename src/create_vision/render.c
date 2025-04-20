/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:03:18 by yufonten          #+#    #+#             */
/*   Updated: 2025/02/22 17:03:21 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	get_texture_pos_x(t_ray_info *infos, t_img *texture)
{
	int	tex_x;

	tex_x = (infos->wall_x * (double)texture->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	return (tex_x);
}

int	get_texture_pos_y(t_ray_info *infos, t_img *texture, double tex_pos)
{
	int	tex_y;

	tex_y = (int)tex_pos;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= texture->height)
		tex_y = ((int)tex_pos) & (texture->height - 1);
	return (tex_y);
}

int	get_ray_hit_wall_x(t_cub *cub, t_ray_info *infos)
{
	if (infos->side == 0)
		infos->wall_x = cub->i_p.pos_y + infos->perp_wall_dist
			* infos->ray_dir_y;
	else
		infos->wall_x = cub->i_p.pos_x + infos->perp_wall_dist
			* infos->ray_dir_x;
	infos->wall_x -= floor(infos->wall_x);
	return (1);
}

void	draw_line(t_cub *cub, t_ray_info *infos, int x)
{
	t_img	*texture;

	texture = select_texture(cub, infos);
	get_ray_hit_wall_x(cub, infos);
	infos->tex_x = get_texture_pos_x(infos, texture);
	infos->step = 1.0 * texture->height / infos->line_height;
	infos->tex_pos = (infos->wall_start - HEIGHT / 2 + infos->line_height / 2)
		* infos->step;
	draw_sky(cub, x, infos);
	draw_floor(cub, x, infos);
	draw_wall(cub, x, infos, texture);
}
