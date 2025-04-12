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

static void	fill_textures(t_cub *cub)
{
	char	*line[4];
	int		i;

	i = 0;
	while (i < 4)
		line[i++] = get_next_line(cub->fd_cub);
	cub->i_tex.no = ft_substr(line[0], 3, ft_strlen(line[0]) - 4);
	cub->i_tex.so = ft_substr(line[1], 3, ft_strlen(line[1]) - 4);
	cub->i_tex.we = ft_substr(line[2], 3, ft_strlen(line[2]) - 4);
	cub->i_tex.ea = ft_substr(line[3], 3, ft_strlen(line[3]) - 4);
	free(line[0]);
	free(line[1]);
	free(line[2]);
	free(line[3]);
}

static void	fill_colors(t_cub *cub)
{
	char	*line[3];
	char	**c[2];
	char	*linec[2];
	int		i;

	i = 0;
	while (i < 3)
		line[i++] = get_next_line(cub->fd_cub);
	linec[0] = ft_substr(line[1], 2, ft_strlen(line[1]) - 3);
	linec[1] = ft_substr(line[2], 2, ft_strlen(line[2]) - 3);
	c[0] = ft_split(linec[0], ',');
	c[1] = ft_split(linec[1], ',');
	i = -1;
	while (++i < 3)
	{
		cub->i_tex.cf[i] = ft_atoi(c[0][i]);
		cub->i_tex.cc[i] = ft_atoi(c[1][i]);
		free(c[0][i]);
		free(c[1][i]);
		free(line[i]);
	}
	free(linec[0]);
	free(linec[1]);
	free(c[0]);
	free(c[1]);
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
	ft_fprintf(1, "%s", holder_map);
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
	fill_textures(cub);
	fill_colors(cub);
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
