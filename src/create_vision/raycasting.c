#include "../../inc/cub3d.h"

void	calculate_dir(t_cub *cub, t_rayInfo *infos, int x)
{
    double  cameraX;

	cameraX = 2 * x / (double)WIDTH - 1;
	infos->ray_dir_x = cub->i_p.dir[0] + cub->i_p.plane[0] * cameraX;
	infos->ray_dir_y = cub->i_p.dir[1] + cub->i_p.plane[1] * cameraX;
}

int	get_player_position(t_cub *cub, t_rayInfo *infos)
{
	infos->map_x = (int)cub->i_p.pos_x;
	infos->map_y = (int)cub->i_p.pos_y;
	return (1);
}

int	get_delta_dist_x_and_y(t_rayInfo *infos)
{
	infos->delta_dist_x = fabs(1 / infos->ray_dir_x);
	infos->delta_dist_y = fabs(1 / infos->ray_dir_y);
}

int	get_side_dist(t_cub *cub, t_rayInfo *infos)
{
	if (infos->ray_dir_x < 0)
	{
		infos->step_x = -1;
		infos->side_dist_x = (cub->i_p.pos_x - infos->map_x)
			* infos->delta_dist_x;
	}
	else
	{
		infos->step_x = 1;
		infos->side_dist_x = (infos->map_x + 1.0 - cub->i_p.pos_x)
			* infos->delta_dist_x;
	}
	if (infos->ray_dir_y < 0)
	{
		infos->step_y = -1;
		infos->side_dist_y = (cub->i_p.pos_y - infos->map_y)
			* infos->delta_dist_y;
	}
	else
	{
		infos->step_y = 1;
		infos->side_dist_y = (infos->map_y + 1.0 - cub->i_p.pos_y)
			* infos->delta_dist_y;
	}
}

int find_wall(t_cub *cub, t_rayInfo *infos)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		// AVANÇA ATE ACHAR A PAREDE
		if (infos->side_dist_x < infos->side_dist_y)
		{
			infos->side_dist_x += infos->delta_dist_x;
			infos->map_x += infos->step_x;
			infos->side = 0;
		}
		else
		{
			infos->side_dist_y += infos->delta_dist_y;
			infos->map_y += infos->step_y;
			infos->side = 1;
		}
		// VERIFICAR SE BATEU NA PAREDE
		if (cub->i_map.map[infos->map_y][infos->map_x] == '1')
			hit = 1;
	}
}
int	calculate_perpendicular(t_cub *cub, t_rayInfo *infos)
{
	if (infos->side == 0)
		infos->perp_wall_dist = (infos->side_dist_x - infos->delta_dist_x);
	else
		infos->perp_wall_dist = (infos->side_dist_y - infos->delta_dist_y);
}