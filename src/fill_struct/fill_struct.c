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

static void	validate_extension(t_cub *cub, char *file)
{
	int	i;

	i = ft_strlen(file);
	if (i < 5 || file[i - 1] != 'b' || file[i - 2] != 'u'
		|| file[i - 3] != 'c' || file[i - 4] != '.')
		error("Error: the file must have a .cub extension\n", NULL, 0, 0);
	cub->fd_cub = open(file, O_RDONLY);
	if (cub->fd_cub == -1)
		error("Error: could not open the file\n", NULL, 0, 0);
}

static void	fill_textures(t_cub *cub)
{
	char	*line[4];
	int		i;

	i = 0;
	while (i < 4)
		line[i++] = get_next_line(cub->fd_cub);
	cub->tex.no = ft_substr(line[0], 3, ft_strlen(line[0]) - 4);
	cub->tex.so = ft_substr(line[1], 3, ft_strlen(line[1]) - 4);
	cub->tex.we = ft_substr(line[2], 3, ft_strlen(line[2]) - 4);
	cub->tex.ea = ft_substr(line[3], 3, ft_strlen(line[3]) - 4);
	i = 0;
	while (i < 4)
		free(line[i++]);
	if (ft_strncmp(line[0], "NO", 2) || open(cub->tex.no, O_RDONLY) == -1)
		error("Error: misconfiguration in north texture\n", cub, 1, 0);
	if (ft_strncmp(line[1], "SO", 2) || open(cub->tex.so, O_RDONLY) == -1)
		error("Error: misconfiguration in south texture\n", cub, 1, 0);
	if (ft_strncmp(line[2], "WE", 2) || open(cub->tex.we, O_RDONLY) == -1)
		error("Error: misconfiguration in west texture\n", cub, 1, 0);
	if (ft_strncmp(line[3], "EA", 2) || open(cub->tex.ea, O_RDONLY) == -1)
		error("Error: misconfiguration in east texture\n", cub, 1, 0);
}

static void	fill_colors(t_cub *cub)
{
	char	*line[3];
	char	**cf;
	char	**cc;
	char	*linet;
	char 	*linec;
	int		i;

	i = 0;
	while (i < 3)
		line[i++] = get_next_line(cub->fd_cub);
	if (ft_strncmp(line[1], "F", 1))
		error("Error: misconfiguration in floor color\n", cub, 2, 0);
	if (ft_strncmp(line[2], "C", 1))
		error("Error: misconfiguration in ceiling color\n", cub, 2, 0);
	linet = ft_substr(line[1], 2, ft_strlen(line[1]) - 3);
	linec = ft_substr(line[2], 2, ft_strlen(line[2]) - 3);
	cf = ft_split(linet, ',');
	cc = ft_split(linec, ',');
	i = 0;
	while (i < 3)
	{
		cub->tex.cf[i] = ft_atoi(cf[i]);
		cub->tex.cc[i] = ft_atoi(cc[i]);
		free(cf[i]);
		free(cc[i]);
		i++;
	}
	free(linet);
	free(linec);
	free(cf);
	free(cc);
	free(line[0]);
	free(line[1]);
	free(line[2]);
}

static	void	fill_map(t_cub *cub)
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
	cub->i_map.map = ft_split(holder_map, '\n');
	free(holder_map);
}

void	fill_struct(t_cub *cub, char *file)
{
	validate_extension(cub, file);
	fill_textures(cub);
	fill_colors(cub);
	fill_map(cub);
	fill_player_info(cub);
	close(cub->fd_cub);
}
