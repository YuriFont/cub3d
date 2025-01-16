#include "../../inc/cub3d.h"

int	calculate_wall_height(t_rayInfo *infos)
{
	int	wallLine;

	wallLine = (int)(HEIGHT / infos->perp_wall_dist);
	infos->wall_start = -wallLine / 2 + HEIGHT / 2;
	if (infos->wall_start < 0)
		infos->wall_start = 0;
	infos->wall_end = wallLine / 2 + HEIGHT / 2;
	if (infos->wall_end >= HEIGHT)
		infos->wall_end = HEIGHT - 1;
	return (1);
}

void	draw_line(t_cub *cub, t_rayInfo *infos, int x)
{
	int	*pixels;

	pixels = (int *)cub->i_img.img_data;
	// Loop para desenhar na faixa entre lineStart e lineEnd
	for (int y = 0; y < HEIGHT; y++)
	{
		int index = y * WIDTH + x; // Cálculo do índice do pixel
		if (y < infos->wall_start)
			cub->i_img.img_data[index] = 0x87CEEB;
		else if (y > infos->wall_end)
			cub->i_img.img_data[index] = 0x228B22;
		else
		{
			if (infos->side == 1)
				cub->i_img.img_data[index] = 0xAAAAAA;
			else
				cub->i_img.img_data[index] = 0x0000FF00 >> 8;
		}
	}
}