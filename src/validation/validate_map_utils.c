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

void	check_character(t_cub *cub, char c)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S'
		&& c != 'E' && c != 'W' && c != ' ')
	{
		free_matriz(cub->i_map.map);
		error("Error: invalid character in map\n");
	}
}

void	validate_spaces(t_cub *cub)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	map = cub->i_map.map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' '
				&& check_around(map, i, j, cub->i_map.height))
			{
				free_matriz(cub->i_map.map);
				error("Error: the map is not surrounded by walls\n");
			}
			j++;
		}
		i++;
	}
}

void	validate_unevenness_top(t_cub *cub)
{
	int		i;
	int		j;
	int		line;
	char	**map;

	i = 0;
	map = cub->i_map.map;
	while (i < cub->i_map.height)
	{
		if ((ft_strlen(map[i]) - ft_strlen(map[i + 1])) > 0)
		{
			j = ft_strlen(map[i]) - 1;
			line = ft_strlen(map[i + 1]) - 1;
			while (j >= line)
			{
				if (map[i][j] != '1')
				{
					free_matriz(cub->i_map.map);
					error("Error: map is not surrounded by walls\n");
				}
				j--;
			}
		}
		i++;
	}
}

void	validate_unevenness_bot(t_cub *cub)
{
	int		i;
	int		j;
	int		line;
	char	**map;

	i = cub->i_map.height;
	map = cub->i_map.map;
	while (i > 0)
	{
		if ((ft_strlen(map[i]) - ft_strlen(map[i - 1])) > 0)
		{
			j = ft_strlen(map[i]) - 1;
			line = ft_strlen(map[i - 1]) - 1;
			while (j >= line)
			{
				if (map[i][j] != '1')
				{
					free_matriz(cub->i_map.map);
					error("Error: map is not surrounded by walls\n");
				}
				j--;
			}
		}
		i--;
	}
}
