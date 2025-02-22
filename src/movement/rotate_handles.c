/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_handles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:48:55 by yufonten          #+#    #+#             */
/*   Updated: 2025/02/22 16:48:58 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	rotate_right(t_cub *cub)
{
	double	old_dir;
	double	old_plane_x;

	old_dir = cub->i_p.dir[0];
	old_plane_x = cub->i_p.plane[0];
	cub->i_p.dir[0] = cub->i_p.dir[0] * cos(ROTSPEED) - cub->i_p.dir[1]
		* sin(ROTSPEED);
	cub->i_p.dir[1] = old_dir * sin(ROTSPEED) + cub->i_p.dir[1] * cos(ROTSPEED);
	cub->i_p.plane[0] = cub->i_p.plane[0] * cos(ROTSPEED) - cub->i_p.plane[1]
		* sin(ROTSPEED);
	cub->i_p.plane[1] = old_plane_x * sin(ROTSPEED) + cub->i_p.plane[1]
		* cos(ROTSPEED);
	return (0);
}

int	rotate_left(t_cub *cub)
{
	double	old_dir;
	double	old_plane_x;

	old_dir = cub->i_p.dir[0];
	old_plane_x = cub->i_p.plane[0];
	cub->i_p.dir[0] = cub->i_p.dir[0] * cos(-ROTSPEED) - cub->i_p.dir[1]
		* sin(-ROTSPEED);
	cub->i_p.dir[1] = old_dir * sin(-ROTSPEED) + cub->i_p.dir[1]
		* cos(-ROTSPEED);
	cub->i_p.plane[0] = cub->i_p.plane[0] * cos(-ROTSPEED) - cub->i_p.plane[1]
		* sin(-ROTSPEED);
	cub->i_p.plane[1] = old_plane_x * sin(-ROTSPEED) + cub->i_p.plane[1]
		* cos(-ROTSPEED);
	return (0);
}
