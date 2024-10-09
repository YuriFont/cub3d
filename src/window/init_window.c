/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 22:17:22 by yufonten          #+#    #+#             */
/*   Updated: 2024/10/03 22:17:22 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void initializing_window(t_cub *cub)
{
	cub->ptr_mlx = mlx_init();
	if (!cub->ptr_mlx)
		error("Error: cannot init ptr_mlx\n", cub, 3, 0);
	mlx_get_screen_size(cub->ptr_mlx, &cub->i_win.w_width,
		&cub->i_win.w_height);
	cub->w_mlx = mlx_new_window(cub->ptr_mlx, cub->i_win.w_width - 20,
		cub->i_win.w_height - 100, "Cub3D");
	if (!cub->w_mlx)
    {
        free(cub->ptr_mlx);
		error("Error: cannot init window\n", cub, 3, 0);
    }
}
