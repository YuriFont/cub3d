/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_around.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:43:58 by yufonten          #+#    #+#             */
/*   Updated: 2024/09/26 20:43:58 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	leak(char c)
{
	if (c != ' ' && c != '1')
		return (1);
	return (0);
}

int	check_around(char **map, int y, int x, int h)
{
	if ((y == 0 && x == 0) && (leak(map[y][x + 1])
		|| leak(map[y + 1][x + 1]) || leak(map[y + 1][x])))
		return (printf("1\n"), 1);
	else if ((y == h && x == 0) && (leak(map[y - 1][x])
		|| leak(map[y][x + 1]) || leak(map[y - 1][x + 1])))
		return (printf("2\n"), 1);
	else if ((y == 0 && x != 0) && (leak(map[y][x + 1]) || leak(map[y][x - 1])
		|| leak(map[y + 1][x]) || leak(map[y + 1][x + 1])
		|| leak(map[y + 1][x - 1])))
		return (printf("3\n"), 1);
	else if ((y == h && x != 0) && (leak(map[y][x - 1]) || leak(map[y][x + 1])
		|| leak(map[y - 1][x - 1]) || leak(map[y - 1][x + 1])
		|| leak(map[y - 1][x])))
		return (printf("4\n"), 1);
	else if ((x != 0 && y != 0 && y != h)
		&& (leak(map[y - 1][x - 1]) || leak(map[y - 1][x])
		|| leak(map[y - 1][x + 1]) || leak(map[y][x + 1])
		|| leak(map[y + 1][x + 1]) || leak(map[y + 1][x])
		|| leak(map[y + 1][x - 1]) || leak(map[y][x - 1])))
		return (1);
	return (0);
}
