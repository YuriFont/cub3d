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

void	destroy_window(t_cub *cub)
{
	mlx_destroy_window(cub->ptr_mlx, cub->w_mlx);
	mlx_destroy_display(cub->ptr_mlx);
	free(cub->ptr_mlx);
}

void	free_matriz(char **mat)
{
	int	i;

	i = 0;
	while (mat[i] != 0)
		free(mat[i++]);
	free(mat);
}

int	final_free(t_cub *cub)
{	
	//free_cub(cub, 3);
	destroy_window(cub);
	exit(0);
	return(0);
}

int	error(char *msg)
{
	ft_fprintf(2, "%s", msg);
	exit(1);
}
