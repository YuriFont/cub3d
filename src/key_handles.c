/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:15:48 by erramos           #+#    #+#             */
/*   Updated: 2025/02/13 17:15:52 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	on_keypress(int key, t_cub *cub)
{
	if (key == XK_Escape)
		final_free(cub);
	if (key == XK_Right)
		cub->move.rot_right = 1;
	else if (key == XK_Left)
		cub->move.rot_left = 1;
	if (key == XK_Up || key == XK_w)
		cub->move.up = 1;
	if (key == XK_Down || key == XK_s)
		cub->move.down = 1;
	if (key == XK_a)
		cub->move.left = 1;
	if (key == XK_d)
		cub->move.right = 1;
	create_vision(cub);
	return (0);
}

int	on_keyrelease(int key, t_cub *cub)
{
	if (key == XK_w || key == XK_Up)
		cub->move.up = 0;
	if (key == XK_s || key == XK_Down)
		cub->move.down = 0;
	if (key == XK_a)
		cub->move.left = 0;
	if (key == XK_d)
		cub->move.right = 0;
	if (key == XK_Left)
		cub->move.rot_left = 0;
	if (key == XK_Right)
		cub->move.rot_right = 0;
	return (0);
}

int	move_player(t_cub *cub)
{
	if (cub->move.right)
		move_right(cub);
	if (cub->move.left)
		move_left(cub);
	if (cub->move.up)
		move_forward(cub);
	if (cub->move.down)
		move_backward(cub);
	if (cub->move.rot_right)
		rotate_right(cub);
	if (cub->move.rot_left)
		rotate_left(cub);
	return (0);
}
