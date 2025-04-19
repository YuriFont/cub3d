/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 10:35:01 by yufonten          #+#    #+#             */
/*   Updated: 2024/09/15 10:35:01 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	fill_textures(t_cub *cub, char tex, char *line)
{
	if (tex == 'N')
		cub->i_tex.no = line;
	if (tex == 'S')
		cub->i_tex.so = line;
	if (tex == 'W')
		cub->i_tex.we = line;
	if (tex == 'E')
		cub->i_tex.ea = line;
}

void	fill_colors(t_cub *cub, char fc, char **n, char **config)
{
	if (fc == 'F')
	{
		cub->i_tex.cf[0] = ft_atoi(n[0]);
		cub->i_tex.cf[1] = ft_atoi(n[1]);
		cub->i_tex.cf[2] = ft_atoi(n[2]);
	}
	if (fc == 'C')
	{
		cub->i_tex.cc[0] = ft_atoi(n[0]);
		cub->i_tex.cc[1] = ft_atoi(n[1]);
		cub->i_tex.cc[2] = ft_atoi(n[2]);
	}
	free_matriz(config);
	free_matriz(n);
}

void	fill_map(t_cub *cub)
{
	char	*line;
	char	*holder_map;
	char	*holder;
	char	**map;

	holder_map = ft_strdup("");
	while (1)
	{
		line = get_next_line(cub->fd_cub);
		if (!line)
			break ;
		holder = holder_map;
		holder_map = ft_strjoin(holder, line);
		free(line);
		free(holder);
	}
	free(line);
	valid_nl(holder_map);
	cub->i_map.map = ft_split(holder_map, '\n');
	free(holder_map);
}

void	default_values_moves(t_cub *cub)
{
	cub->move.up = 0;
	cub->move.down = 0;
	cub->move.left = 0;
	cub->move.right = 0;
	cub->move.rot_left = 0;
	cub->move.rot_right = 0;
}

void	fill_struct(t_cub *cub, char *file)
{
	char	*line;

	cub->fd_cub = open(file, O_RDONLY);
	fill_player_info(cub);
	line = get_next_line(cub->fd_cub);
	cub->i_img.img_ptr = NULL;
	while (line)
	{
		free(line);
		line = get_next_line(cub->fd_cub);
	}
	close(cub->fd_cub);
	default_values_moves(cub);
}
