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
		error("Error: cub3D only accepts one parameter\n");
	validate_cub(&cub, av[1]);
	validate_map(&cub);
	/*initializing_window(&cub);
	mlx_hook(cub.w_mlx, 17, 0, final_free, &cub);
	mlx_loop(cub.ptr_mlx);*/
	return (0);
}
