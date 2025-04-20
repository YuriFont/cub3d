/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:16:46 by erramos           #+#    #+#             */
/*   Updated: 2025/02/13 17:16:50 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	run_code(t_cub *cub)
{
	move_player(cub);
	create_dda_vision(cub);
	mlx_put_image_to_window(cub->ptr_mlx, cub->w_mlx, cub->i_img.img_ptr, 0, 0);
	return (0);
}
