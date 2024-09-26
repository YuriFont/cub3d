/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:13:32 by yufonten          #+#    #+#             */
/*   Updated: 2024/09/14 12:13:32 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac != 2)
		error("Error: cub3D only accepts one parameter\n", NULL, 0);
	fill_struct(&cub, av[1]);
	validate_map(&cub);
	for (int i = 0; cub.info_map.map[i] != 0; i++)
		printf("%s\n", cub.info_map.map[i]);
	free_cub(&cub, 3);
	return (0);
}
