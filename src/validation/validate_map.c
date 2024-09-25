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

static void check_character(char c, int *position, t_cub *cub)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
		error("Error: invalid character in map\n", cub, 3);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		*position = *position + 1;
}

static int	is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

void	count_assets(t_cub *cub)
{
	int	i;
	int	j;
	int	position;

	i = 0;
	position = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (!is_space(cub->map[i][j]))
				check_character(cub->map[i][j], &position, cub);
			j++;
		}
		i++;
	}
	if (position != 1)
		error("Error: invalid quantity of player start position\n", cub, 3);
}

void	validate_map(t_cub *cub)
{
	count_assets(cub);
}
