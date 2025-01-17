/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 22:10:36 by yufonten          #+#    #+#             */
/*   Updated: 2024/10/08 22:10:36 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	fill_vector_plane(t_cub *cub, char d)
{
	if (d == 'S')
	{
		cub->i_p.plane[0] = -0.66;
		cub->i_p.plane[1] = 0;
	}
	else if (d == 'N')
	{
		cub->i_p.plane[0] = 0.66;
		cub->i_p.plane[1] = 0;
	}
	else if (d == 'E')
	{
		cub->i_p.plane[0] = 0;
		cub->i_p.plane[1] = 0.66;
	}
	else
	{
		cub->i_p.plane[0] = 0;
		cub->i_p.plane[1] = -0.66;
	}
}

void	fill_player_dir(t_cub *cub, char d)
{
	if (d == 'N')
	{
		cub->i_p.dir[0] = 0;
		cub->i_p.dir[1] = -1;
	}
	else if (d == 'S')
	{
		cub->i_p.dir[0] = 0;
		cub->i_p.dir[1] = 1;
	}
	else if (d == 'E')
	{
		cub->i_p.dir[0] = 1;
		cub->i_p.dir[1] = 0;
	}
	else if (d == 'W')
	{
		cub->i_p.dir[0] = -1;
		cub->i_p.dir[1] = 0;
	}
	fill_vector_plane(cub, d);
}

void    fill_player_info(t_cub *cub)
{
    int		i;
	int		j;
	char	**map;

	map = cub->i_map.map;
	i = 0;
    while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				cub->i_p.pos_y = (double)i;
				cub->i_p.pos_x = (double)j;
				fill_player_dir(cub, map[i][j]);
				map[i][j] = '0';
				printf("POSIÇÕES DO JOGADOR\npos_x: %lf, pos_y: %lf, dir - X: %lf Y: %lf\n", cub->i_p.pos_x, cub->i_p.pos_y, cub->i_p.dir[0], cub->i_p.dir[1]);
				return ;
			}
			j++;
		}
		i++;
	}
}
