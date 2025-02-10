/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:13:32 by yufonten          #+#    #+#             */
/*   Updated: 2024/09/14 12:13:32 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int get_mouse_pos(void *ptr)
{
	t_cub *cub = (t_cub *)ptr;
	int x = 0, y = 0;
	mlx_mouse_get_pos(cub->ptr_mlx, cub->w_mlx ,&x, &y);
	printf("posição x: %d\nposição y: %d", x, y);
	return (0);
}

int	on_keypress(int key, t_cub *cub)
{
	if (key == XK_Escape)
		final_free(cub);
	if (key == XK_Right){
		double oldDir = cub->i_p.dir[0];
		cub->i_p.dir[0] =  cub->i_p.dir[0] * cos(ROTSPEED) - cub->i_p.dir[1] * sin(ROTSPEED);
		cub->i_p.dir[1] = oldDir * sin(ROTSPEED) + cub->i_p.dir[1] * cos(ROTSPEED);
		double oldPlaneX = cub->i_p.plane[0];
		cub->i_p.plane[0] = cub->i_p.plane[0] * cos(ROTSPEED) - cub->i_p.plane[1] * sin(ROTSPEED);
		cub->i_p.plane[1] = oldPlaneX * sin(ROTSPEED) + cub->i_p.plane[1] * cos(ROTSPEED);
	}
	else if (key == XK_Left) {
		double oldDir = cub->i_p.dir[0];
		cub->i_p.dir[0] =  cub->i_p.dir[0] * cos(-ROTSPEED) - cub->i_p.dir[1] * sin(-ROTSPEED);
		cub->i_p.dir[1] = oldDir * sin(-ROTSPEED) + cub->i_p.dir[1] * cos(-ROTSPEED);
		double oldPlaneX = cub->i_p.plane[0];
		cub->i_p.plane[0] = cub->i_p.plane[0] * cos(-ROTSPEED) - cub->i_p.plane[1] * sin(-ROTSPEED);
		cub->i_p.plane[1] = oldPlaneX * sin(-ROTSPEED) + cub->i_p.plane[1] * cos(-ROTSPEED);
	}
	if (key == XK_Up || key == XK_w) {
		// Verificação do movimento na direção X
		if (cub->i_map.map[(int)cub->i_p.pos_y][(int)(cub->i_p.pos_x + cub->i_p.dir[0] * (MOVSPEED * 5))] == '0') {
			cub->i_p.pos_x += cub->i_p.dir[0] * MOVSPEED;
			// printf("x> %f\n", cub->i_p.pos_x);
		}
		
		// Verificação do movimento na direção Y
		if (cub->i_map.map[(int)(cub->i_p.pos_y + cub->i_p.dir[1] * (MOVSPEED * 5))][(int)cub->i_p.pos_x] == '0') {
			cub->i_p.pos_y += cub->i_p.dir[1] * MOVSPEED;
			// printf("y> %f\n", cub->i_p.pos_y);
		}
	}
	if (key == XK_Down || key == XK_s) {
		if (cub->i_map.map[(int)cub->i_p.pos_y][(int)(cub->i_p.pos_x - cub->i_p.dir[0] * (MOVSPEED * 5))] == '0') {
			cub->i_p.pos_x -= cub->i_p.dir[0] * MOVSPEED;
			// printf("x> %f\n", cub->i_p.pos_x);
		}
		
		// Verificação do movimento na direção Y
		if (cub->i_map.map[(int)(cub->i_p.pos_y - cub->i_p.dir[1] * (MOVSPEED * 5))][(int)cub->i_p.pos_x] == '0') {
			cub->i_p.pos_y -= cub->i_p.dir[1] * MOVSPEED;
			// printf("y> %f\n", cub->i_p.pos_y);
		}
	}
	if (key == XK_a) {
		if (cub->i_map.map[(int)(cub->i_p.pos_y)][(int)(cub->i_p.pos_x - cub->i_p.plane[0] * (MOVSPEED * 2))] == '0') {
			cub->i_p.pos_x -= cub->i_p.plane[0] * MOVSPEED;
		}
		if (cub->i_map.map[(int)(cub->i_p.pos_y - cub->i_p.plane[1] * (MOVSPEED * 2))][(int)cub->i_p.pos_x] == '0') {
			cub->i_p.pos_y -= cub->i_p.plane[1] * MOVSPEED;
		}
	}
	if (key == XK_d) {
		if (cub->i_map.map[(int)(cub->i_p.pos_y)][(int)(cub->i_p.pos_x + cub->i_p.plane[0] * (MOVSPEED * 2))] == '0') {
			cub->i_p.pos_x += cub->i_p.plane[0] * MOVSPEED;
		}
		if (cub->i_map.map[(int)(cub->i_p.pos_y + cub->i_p.plane[1] * (MOVSPEED * 2))][(int)(cub->i_p.pos_x)] == '0') {
			cub->i_p.pos_y += cub->i_p.plane[1] * MOVSPEED;
		}
	}
	create_vision(cub);
	return (0);
}

void	load_image_texture(t_cub *cub, t_img *texture, char *path)
{
	texture->img_ptr = mlx_xpm_file_to_image(cub->ptr_mlx, path, &texture->width, &texture->height);
	if (!texture->img_ptr)
		error(cub, "Error: cannot load texture image\n", 1);	
	texture->img_data = (unsigned char *)mlx_get_data_addr(texture->img_ptr, &texture->bpp, &texture->line_len, &texture->endian);
	// printf("%d   %d\n", texture->line_len, texture->bpp);
}

int run_code(t_cub *cub)
{
	create_vision(cub);
	mlx_put_image_to_window(cub->ptr_mlx, cub->w_mlx, cub->i_img.img_ptr, 0,
		0);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac != 2)
		error(NULL, "Error: cub3D only accepts one parameter\n", 0);
	validate_cub(&cub, av[1]);
	validate_map(&cub);
	fill_struct(&cub, av[1]);
	for (int i = 0; cub.i_map.map[i] != 0; i++)
		printf("%s\n", cub.i_map.map[i]);
	initializing_window(&cub);
	load_image_texture(&cub, &cub.tex_east, cub.i_tex.so);
	load_image_texture(&cub, &cub.tex_west, cub.i_tex.we);
	load_image_texture(&cub, &cub.tex_north, cub.i_tex.no);
	load_image_texture(&cub, &cub.tex_south, cub.i_tex.ea);
	create_img(&cub);
	mlx_hook(cub.w_mlx, KeyPress, KeyPressMask, &on_keypress, &cub);
	// mlx_loop_hook(cub.ptr_mlx, run_code, &cub);
	create_vision(&cub);
	mlx_hook(cub.w_mlx, 17, 0, final_free, &cub);
	// mlx_loop_hook(cub.ptr_mlx, get_mouse_pos, &cub);
	mlx_loop(cub.ptr_mlx);
	return (0);
}
