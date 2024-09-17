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
		error("Error: the file must have a .cub extension\n");
	if ((cub->fd_cub = open(file, O_RDONLY)) == -1)
		error("Error: could not open the file\n");
}

static void	fill_textures(t_cub *cub)
{
	char	*line;

	line = get_next_line(cub->fd_cub);
	cub->tex.no = ft_substr(line, 3, ft_strlen(line) - 4);
	if (ft_strncmp(line, "NO", 2) || open(cub->tex.no, O_RDONLY) == -1)
		error("Error: misconfiguration in north texture\n");
	line = get_next_line(cub->fd_cub);
	cub->tex.so = ft_substr(line, 3, ft_strlen(line) - 4);
	if (ft_strncmp(line, "SO", 2) || open(cub->tex.so, O_RDONLY) == -1)
		error("Error: misconfiguration in south texture\n");
	line = get_next_line(cub->fd_cub);
	cub->tex.we = ft_substr(line, 3, ft_strlen(line) - 4);
	if (ft_strncmp(line, "WE", 2) || open(cub->tex.we, O_RDONLY) == -1)
		error("Error: misconfiguration in west texture\n");
	line = get_next_line(cub->fd_cub);
	cub->tex.ea = ft_substr(line, 3, ft_strlen(line) - 4);
	if (ft_strncmp(line, "EA", 2) || open(cub->tex.ea, O_RDONLY) == -1)
		error("Error: misconfiguration in east texture\n");
}

void	fill_struct(t_cub *cub, char *file)
{
	validate_extension(cub, file);
	fill_textures(cub);
}
