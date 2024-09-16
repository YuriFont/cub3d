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

static void	validate_extension(char *file)
{
	int	i;

	i = ft_strlen(file);
	if (i < 5 || file[i - 1] != 'b' || file[i - 2] != 'u'
		|| file[i - 3] != 'c' || file[i - 4] != '.')
		error("Error: the file must have a .cub extension\n");
}

static void	fill_textures(t_cub *cub)
{
	int		i;
	char	*line;

	i = 0;
	while (i < 4)
	{
		line = get_next_line(cub->fd_cub);
		cub->tex.no = ft_substr(line, 3, ft_strlen(line) - 4);
		if (ft_strncmp(line, "NO", 2) || (open(cub->tex.no, O_RDONLY) == -1))
			
		if (ft_strncmp(line, "SO", 2)
			|| open(ft_substr(line, 3, ft_strlen(line) - 5), O_RDONLY) == -1)
			error("Error: could not open file to the south textures\n", cub);
		if (ft_strncmp(line, "WE", 2)
			|| open(ft_substr(line, 3, ft_strlen(line) - 5), O_RDONLY) == -1)
			error("Error: could not open file to the west textures\n", cub);
		if (ft_strncmp(line, "EA", 2)
			|| open(ft_substr(line, 3, ft_strlen(line) - 5), O_RDONLY) == -1)
			error("Error: could not open file to the east textures\n", cub);
	}
}

void	fill_struct(t_cub *cub, char *file)
{
	validate_extension(file);
	if ((cub->fd_cub = open(file, O_RDONLY)) == -1)
		error("Error: could not open the file\n");
	fill_textures(cub);
}
