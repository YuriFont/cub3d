/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:53:33 by yufonten          #+#    #+#             */
/*   Updated: 2025/02/22 14:53:36 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	calculate_wall_height(t_ray_info *infos)
{
	int	wall_line;

	wall_line = (int)(HEIGHT / infos->perp_wall_dist);
	infos->wall_start = -wall_line / 2 + HEIGHT / 2;
	if (infos->wall_start < 0)
		infos->wall_start = 0;
	infos->wall_end = wall_line / 2 + HEIGHT / 2;
	if (infos->wall_end >= HEIGHT)
		infos->wall_end = HEIGHT - 1;
	infos->line_height = wall_line;
	return (1);
}

int	get_texture_color(t_img *texture, int tex_x, int tex_y, t_cub *cub)
{
	int	pixel;

	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= texture->height)
		tex_y = texture->height - 1;
	if (tex_x < 0 || tex_x >= texture->width || tex_y < 0
		|| tex_y >= texture->height)
		error(cub, "Coordinates outside texture boundaries\n", 1);
	pixel = (tex_y * texture->line_len) + (tex_x * (texture->bpp / 8));
	if (pixel < 0 || pixel >= (texture->line_len * texture->height))
		error(cub, "Pixel index out of bounds\n", 1);
	return (*(int *)(texture->img_data + pixel));
}

t_img	*select_texture(t_cub *cub, t_ray_info *infos)
{
	if (infos->side == 0)
	{
		if (infos->ray_dir_x > 0)
			return (&cub->tex_east);
		else
			return (&cub->tex_west);
	}
	else
	{
		if (infos->ray_dir_y > 0)
			return (&cub->tex_north);
		else
			return (&cub->tex_south);
	}
}
