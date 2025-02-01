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
	if (key == XK_Up) {
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
	if (key == XK_Down) {
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
	if (key == 'a') {
		if (cub->i_map.map[(int)(cub->i_p.pos_y)][(int)(cub->i_p.pos_x - cub->i_p.plane[0] * (MOVSPEED * 2))] == '0') {
			cub->i_p.pos_x -= cub->i_p.plane[0] * MOVSPEED;
		}
		if (cub->i_map.map[(int)(cub->i_p.pos_y - cub->i_p.plane[1] * (MOVSPEED * 2))][(int)cub->i_p.pos_x] == '0') {
			cub->i_p.pos_y -= cub->i_p.plane[1] * MOVSPEED;
		}
	}
	if (key == 'd') {
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
	create_img(&cub);
	create_vision(&cub);
	mlx_hook(cub.w_mlx, 17, 0, final_free, &cub);
	mlx_hook(cub.w_mlx, KeyPress, KeyPressMask, &on_keypress, &cub);
	// mlx_loop_hook(cub.ptr_mlx, get_mouse_pos, &cub);
	mlx_loop(cub.ptr_mlx);
	return (0);
}
