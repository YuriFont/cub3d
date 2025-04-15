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
	mlx_destroy_image(cub->ptr_mlx, cub->i_img.img_ptr);
	mlx_destroy_image(cub->ptr_mlx, cub->tex_east.img_ptr);
	mlx_destroy_image(cub->ptr_mlx, cub->tex_north.img_ptr);
	mlx_destroy_image(cub->ptr_mlx, cub->tex_south.img_ptr);
	mlx_destroy_image(cub->ptr_mlx, cub->tex_west.img_ptr);
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
	free_matriz(cub->i_map.map);
	free(cub->i_tex.no);
	free(cub->i_tex.so);
	free(cub->i_tex.we);
	free(cub->i_tex.ea);
	destroy_window(cub);
	exit(0);
	return (0);
}

int	error(t_cub *cub, char *msg, int flag)
{
	if (flag)
	{
		free_matriz(cub->i_map.map);
		free(cub->i_tex.no);
		free(cub->i_tex.so);
		free(cub->i_tex.we);
		free(cub->i_tex.ea);
		destroy_window(cub);
	}
	ft_fprintf(2, "%s", msg);
	exit(1);
}

void	valid_nl(char *holder_map)
{
	int	i;

	i = 0;
	while (holder_map[i] == '\n' || holder_map[i] == ' '
		|| holder_map[i] == '\t')
		i++;
	while (holder_map[i])
	{
		if (holder_map[i] == '\n' && holder_map[i + 1] == '\n')
		{
			while (holder_map[i] == '\n')
			{
				if (holder_map[i + 1] != '\n' && holder_map[i + 1] != ' '
					&& holder_map[i + 1] != '\t' && holder_map[i + 1] != '\0')
				{
					free(holder_map);
					error(NULL, "Error: invalid map\n", 0);
				}
				i++;
				if (holder_map[i] == '\0')
					return ;
			}
		}
		i++;
	}
}
