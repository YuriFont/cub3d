/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:30:29 by yufonten          #+#    #+#             */
/*   Updated: 2024/09/26 20:30:29 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_character(char c)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S'
		&& c != 'E' && c != 'W' && c != ' ')
		return (1);
	return (0);
}

void	validate_spaces(t_cub *cub)
{
    int     i;
    int     j;
    char    **map;

    i = 0;
    map = cub->info_map.map;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == ' '
				&& check_around(map, i, j, cub->info_map.height))
                error("Error: the map is not surrounded by walls\n", cub, 3);
			j++;
        }
		i++;
    }
}
