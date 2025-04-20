/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_handles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:16:02 by erramos           #+#    #+#             */
/*   Updated: 2025/02/13 17:16:06 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	move_left(t_cub *cub)
{
	if (cub->i_map.map[(int)(cub->i_p.pos_y)][(int)(cub->i_p.pos_x
			- cub->i_p.plane[0] * (MOVSPEED * 2))] == '0')
	{
		cub->i_p.pos_x -= cub->i_p.plane[0] * MOVSPEED;
	}
	if (cub->i_map.map[(int)(cub->i_p.pos_y - cub->i_p.plane[1] * (MOVSPEED
				* 2))][(int)cub->i_p.pos_x] == '0')
	{
		cub->i_p.pos_y -= cub->i_p.plane[1] * MOVSPEED;
	}
	return (0);
}

int	move_right(t_cub *cub)
{
	if (cub->i_map.map[(int)(cub->i_p.pos_y)][(int)(cub->i_p.pos_x
			+ cub->i_p.plane[0] * (MOVSPEED * 2))] == '0')
	{
		cub->i_p.pos_x += cub->i_p.plane[0] * MOVSPEED;
	}
	if (cub->i_map.map[(int)(cub->i_p.pos_y + cub->i_p.plane[1] * (MOVSPEED
				* 2))][(int)(cub->i_p.pos_x)] == '0')
	{
		cub->i_p.pos_y += cub->i_p.plane[1] * MOVSPEED;
	}
	return (0);
}

int	move_forward(t_cub *cub)
{
	if (cub->i_map.map[(int)cub->i_p.pos_y][(int)(cub->i_p.pos_x
		+ cub->i_p.dir[0] * (MOVSPEED * 5))] == '0')
	{
		cub->i_p.pos_x += cub->i_p.dir[0] * MOVSPEED;
	}
	if (cub->i_map.map[(int)(cub->i_p.pos_y + cub->i_p.dir[1] * (MOVSPEED
				* 5))][(int)cub->i_p.pos_x] == '0')
	{
		cub->i_p.pos_y += cub->i_p.dir[1] * MOVSPEED;
	}
	return (0);
}

int	move_backward(t_cub *cub)
{
	if (cub->i_map.map[(int)cub->i_p.pos_y][(int)(cub->i_p.pos_x
		- cub->i_p.dir[0] * (MOVSPEED * 5))] == '0')
	{
		cub->i_p.pos_x -= cub->i_p.dir[0] * MOVSPEED;
	}
	if (cub->i_map.map[(int)(cub->i_p.pos_y - cub->i_p.dir[1] * (MOVSPEED
				* 5))][(int)cub->i_p.pos_x] == '0')
	{
		cub->i_p.pos_y -= cub->i_p.dir[1] * MOVSPEED;
	}
	return (0);
}
