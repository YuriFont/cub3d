/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:41:18 by erramos           #+#    #+#             */
/*   Updated: 2025/04/14 22:41:30 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	load_image_texture(t_cub *cub, t_img *texture, char *path)
{
	char *line;

	texture->img_ptr = mlx_xpm_file_to_image(cub->ptr_mlx, path,
			&texture->width, &texture->height);
	if (!texture->img_ptr)
		error(cub, "Error: cannot load texture image\n", 1);
	texture->img_data = (unsigned char *)mlx_get_data_addr(texture->img_ptr,
			&texture->bpp, &texture->line_len, &texture->endian);
}

int	load_texture(t_cub *cub)
{
	load_image_texture(cub, &cub->tex_east, cub->i_tex.ea);
	load_image_texture(cub, &cub->tex_west, cub->i_tex.we);
	load_image_texture(cub, &cub->tex_north, cub->i_tex.no);
	load_image_texture(cub, &cub->tex_south, cub->i_tex.so);
	return (1);
}
