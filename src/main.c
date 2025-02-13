/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+    	+#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:13:32 by yufonten          #+#    #+#             */
/*   Updated: 2024/09/14 12:13:32 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	load_image_texture(t_cub *cub, t_img *texture, char *path)
{
	texture->img_ptr = mlx_xpm_file_to_image(cub->ptr_mlx, path,
			&texture->width, &texture->height);
	if (!texture->img_ptr)
		error(cub, "Error: cannot load texture image\n", 1);
	texture->img_data = (unsigned char *)mlx_get_data_addr(texture->img_ptr,
			&texture->bpp, &texture->line_len, &texture->endian);
}

int initial_config(t_cub *cub, char *av)
{
	validate_cub(cub, av);
	validate_map(cub);
	fill_struct(cub, av);
	initializing_window(cub);
	return (1);
}

int	load_texture(t_cub *cub)
{
	load_image_texture(cub, &cub->tex_east, cub->i_tex.ea);
	load_image_texture(cub, &cub->tex_west, cub->i_tex.we);
	load_image_texture(cub, &cub->tex_north, cub->i_tex.no);
	load_image_texture(cub, &cub->tex_south, cub->i_tex.so);
	return (1);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac != 2)
		error(NULL, "Error: cub3D only accepts one parameter\n", 0);
/* 	validate_cub(&cub, av[1]);
	validate_map(&cub);
	fill_struct(&cub, av[1]);
	initializing_window(&cub); */
	initial_config(&cub, av[1]);
	for (int i = 0; cub.i_map.map[i] != 0; i++)
		printf("%s\n", cub.i_map.map[i]);
	load_texture(&cub);
	create_img(&cub);
	mlx_hook(cub.w_mlx, KeyPress, KeyPressMask, &on_keypress, &cub);
	mlx_hook(cub.w_mlx, KeyRelease, KeyReleaseMask, &on_keyrelease, &cub);
	mlx_loop_hook(cub.ptr_mlx, run_code, &cub);
	mlx_hook(cub.w_mlx, 17, 0, final_free, &cub);
/* 	mlx_loop_hook(cub.ptr_mlx, get_mouse_pos, &cub); */
	mlx_loop(cub.ptr_mlx);
	return (0);
}
