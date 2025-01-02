/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:15:34 by yufonten          #+#    #+#             */
/*   Updated: 2024/09/24 19:15:34 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	validate_chars(t_cub *cub)
{
	int		i;
	int		j;
	int		position;
	char	**map;

	i = -1;
	position = 0;
	map = cub->i_map.map;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			check_character(cub, map[i][j]);
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
				position++;
		}
	}
	if (position != 1)
	{
		free_matriz(cub->i_map.map);
		error(NULL, "Error: invalid quantity of player start position\n", 0);
	}
}

static void	validate_sides(t_cub *cub)
{
	char	**map;
	int		i;
	int		j;
	int		k;

	map = cub->i_map.map;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] == ' ')
			j++;
		k = ft_strlen(map[i]) - 1;
		if (map[i][j] != '1' || map[i][k] != '1')
		{
			free_matriz(cub->i_map.map);
			error(NULL, "Error: the map is not surrounded by walls\n", 0);
		}
		i++;
	}
}

static void	validate_top(t_cub *cub)
{
	char	**map;
	int		i;
	int		j;

	map = cub->i_map.map;
	j = 0;
	i = 0;
	while (map[i][j])
	{
		i = 0;
		while (map[i][j] == ' ')
			i++;
		if (map[i][j] != '1')
		{
			free_matriz(cub->i_map.map);
			error(NULL, "Error: the map is not surrounded by walls\n", 0);
		}
		j++;
	}
}

static void	validate_bottom(t_cub *cub)
{
	int		i;
	int		j;
	char	**map;

	map = cub->i_map.map;
	j = 0;
	i = cub->i_map.height;
	while (map[i][j])
	{
		i = cub->i_map.height;
		while (map[i][j] == ' ')
			i--;
		if (map[i][j] != '1')
		{
			free_matriz(cub->i_map.map);
			error(NULL, "Error: the map is not surrounded by walls\n", 0);
		}
		j++;
	}
}

void	validate_map(t_cub *cub)
{
	int	i;

	i = 0;
	cub->i_map.width = 0;
	fill_map(cub);
	close(cub->fd_cub);
	while (cub->i_map.map[i])
	{
		if (cub->i_map.width < ft_strlen(cub->i_map.map[i]))
			cub->i_map.width = ft_strlen(cub->i_map.map[i]);
		i++;
	}
	cub->i_map.height = i - 1;
	validate_chars(cub);
	validate_sides(cub);
	validate_spaces(cub);
	validate_top(cub);
	validate_bottom(cub);
	validate_unevenness_top(cub);
	validate_unevenness_bot(cub);
}
