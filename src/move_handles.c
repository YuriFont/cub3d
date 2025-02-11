
#include "../inc/cub3d.h"

int	get_mouse_pos(void *ptr)
{
	t_cub	*cub;
	int		x;
	int		y;

	cub = (t_cub *)ptr;
	x = 0;
	y = 0;
	mlx_mouse_get_pos(cub->ptr_mlx, cub->w_mlx, &x, &y);
	printf("posição x: %d\nposição y: %d", x, y);
	return (0);
}

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