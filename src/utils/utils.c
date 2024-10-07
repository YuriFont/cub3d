/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:01:01 by yufonten          #+#    #+#             */
/*   Updated: 2024/09/16 22:01:01 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_cub(t_cub *cub, int flag)
{
	int	i;

	if (flag >= 1)
	{
		free(cub->tex.no);
		free(cub->tex.so);
		free(cub->tex.we);
		free(cub->tex.ea);
	}
	if (flag >= 2)
	{
		free(cub->tex.cf);
		free(cub->tex.cc);
	}
	if (flag >= 3)
	{
		i = 0;
		while (cub->info_map.map[i] != 0)
			free(cub->info_map.map[i++]);
		free(cub->info_map.map);
	}
}

void	destroy_window(t_cub *cub)
{
	mlx_destroy_window(cub->ptr_mlx, cub->w_mlx);
	mlx_destroy_display(cub->ptr_mlx);
	free(cub->ptr_mlx);
}

int	final_free(t_cub *cub)
{
	free_cub(cub, 3);
	destroy_window(cub);
	exit(0);
	return(0);
}

int	error(char *msg, t_cub *cub, int flag, int win)
{
	if (flag)
		free_cub(cub, flag);
	if (win)
		destroy_window(cub);
	ft_fprintf(2, "%s", msg);
	exit(1);
}
