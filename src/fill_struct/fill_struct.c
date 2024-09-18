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
		error("Error: the file must have a .cub extension\n", NULL);
	if ((cub->fd_cub = open(file, O_RDONLY)) == -1)
		error("Error: could not open the file\n", NULL);
}

static void	fill_textures(t_cub *cub)
{
	char	*line;

	line = get_next_line(cub->fd_cub);
	cub->tex.no = ft_substr(line, 3, ft_strlen(line) - 4);
	if (ft_strncmp(line, "NO", 2) || open(cub->tex.no, O_RDONLY) == -1)
		error("Error: misconfiguration in north texture\n", cub);
	free(line);
	line = get_next_line(cub->fd_cub);
	cub->tex.so = ft_substr(line, 3, ft_strlen(line) - 4);
	if (ft_strncmp(line, "SO", 2) || open(cub->tex.so, O_RDONLY) == -1)
		error("Error: misconfiguration in south texture\n", cub);
	free(line);
	line = get_next_line(cub->fd_cub);
	cub->tex.we = ft_substr(line, 3, ft_strlen(line) - 4);
	if (ft_strncmp(line, "WE", 2) || open(cub->tex.we, O_RDONLY) == -1)
		error("Error: misconfiguration in west texture\n", cub);
	free(line);
	line = get_next_line(cub->fd_cub);
	cub->tex.ea = ft_substr(line, 3, ft_strlen(line) - 4);
	if (ft_strncmp(line, "EA", 2) || open(cub->tex.ea, O_RDONLY) == -1)
		error("Error: misconfiguration in east texture\n", cub);
	free(line);
}

static void	fill_colors(t_cub *cub)
{
	char	*line;

	line = get_next_line(cub->fd_cub);
	free(line);
	line = get_next_line(cub->fd_cub);
	cub->tex.cf = ft_substr(line, 2, ft_strlen(line) - 3);
	if (ft_strncmp(line, "F", 1))
		error("Error: misconfiguration in floor color\n", cub);
	free(line);
	line = get_next_line(cub->fd_cub);
	cub->tex.cc = ft_substr(line, 2, ft_strlen(line) - 3);
	if (ft_strncmp(line, "C", 1))
		error("Error: misconfiguration in ceiling color\n", cub);
	free(line);
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
		{
			holder = holder_map;
			holder_map = ft_strjoin(holder, "\ne");
			free(holder);
			break ;
		}
		holder = holder_map;
		holder_map = ft_strjoin(holder, line);
		free(line);
		free(holder);
	}
	free(line);
	cub->map = ft_split(holder_map, '\n');
	free(holder_map);
}

void	fill_struct(t_cub *cub, char *file)
{
	validate_extension(cub, file);
	fill_textures(cub);
	fill_colors(cub);
	fill_map(cub);
	close(cub->fd_cub);
}
