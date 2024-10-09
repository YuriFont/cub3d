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
				cub->i_map.y_player = i;
				cub->i_map.x_player = j;
				return ;
			}
			j++;
		}
		i++;
	}
}
