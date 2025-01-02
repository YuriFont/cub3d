/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:35:26 by yufonten          #+#    #+#             */
/*   Updated: 2024/11/04 15:35:26 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	validate_tex(t_cub *cub, char *cp)
{
	char	*line;
	char	*path;
	int		fd_v;

	line = get_next_line(cub->fd_cub);
	if (!line || ft_strlen(line) < 7 || ft_strncmp(line, cp, 2))
	{
		free(line);
		close(cub->fd_cub);
		error(NULL, "Error: misconfiguration in textures\n", 0);
	}
	path = ft_substr(line, 3, ft_strlen(line) - 4);
	if (validate_extension_xpm(path) || ((fd_v = open(path, O_RDONLY)) == -1))
	{
		close(fd_v);
		free(path);
		free(line);
		close(cub->fd_cub);
		error(NULL, "Error: misconfiguration in textures\n", 0);
	}
	close(fd_v);
	free(path);
	free(line);
}

void	validate_rgb(t_cub *cub, char *fc)
{
	char	*line;
	char	*temp;
	char	**n;
	int		e;
	int		i;

	line = get_next_line(cub->fd_cub);
	if (!line || ft_strlen(line) < 7 || ft_strncmp(line, fc, 2))
	{
		free(line);
		close(cub->fd_cub);
		error(NULL, "Error: misconfiguration in floor or ceiling\n", 0);
	}
	temp = ft_substr(line, 2, ft_strlen(line) - 3);
	n = ft_split(temp, ',');
	e = -1;
	if (size_rgb(n) || validate_hx(n[0]) || validate_hx(n[1])
		|| validate_hx(n[2]))
		e = close(cub->fd_cub);
	free(temp);
	free(line);
	free_matriz(n);
	if (e == 0)
		exit(1);
}

void    validate_cub(t_cub *cub, char *file)
{
	char	*l;

	if ((cub->fd_cub = open(file, O_RDONLY)) == -1)
	{
		ft_fprintf(2, "Error: cannot open this file\n");
		close(cub->fd_cub);
		exit(1);
	}
    validate_extension_cub(file);
    validate_tex(cub, "NO");
	validate_tex(cub, "SO");
	validate_tex(cub, "WE");
	validate_tex(cub, "EA");
	l = get_next_line(cub->fd_cub);
	free(l);
	validate_rgb(cub, "F ");
	validate_rgb(cub, "C ");
}
