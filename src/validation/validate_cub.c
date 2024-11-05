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

void	validate_tex(int fd, char *cp)
{
	char	*line;
	char	*path;
	int		fd_v;

	line = get_next_line(fd);
	if (!line || ft_strlen(line) < 10 || ft_strncmp(line, cp, 2))
	{
		free(line);
		close(fd);
		error("Error: misconfiguration in textures\n");
	}
	path = ft_substr(line, 3, ft_strlen(line) - 4);
	if ((fd_v = open(path, O_RDONLY)) == -1 || validate_extension_xpm(path))
	{
		close(fd_v);
		free(path);
		free(line);
		close(fd);
		error("Error: misconfiguration in textures\n");
	}
	close(fd_v);
	free(path);
	free(line);
}

void	validate_rgb(int fd, char *fc)
{
	char	*line;
	char	*temp;
	char	**n;
	int		e;
	int		i;

	line = get_next_line(fd);
	if (!line || ft_strlen(line) < 7 || ft_strncmp(line, fc, 2))
	{
		free(line);
		close(fd);
		error("Error: misconfiguration in floor or ceiling\n");
	}
	temp = ft_substr(line, 2, ft_strlen(line) - 3);
	n = ft_split(temp, ',');
	e = -1;
	if (size_rgb(n) || validate_hx(n[0]) || validate_hx(n[1])
		|| validate_hx(n[2]))
		e = close(fd);
	free(temp);
	free(line);
	free_matriz(n);
	if (e == 0)
		exit(1);
}

void    validate_cub(t_cub *cub, char *file)
{
    int 	fd;
	char	*l;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		ft_fprintf(2, "Error: cannot open this file\n");
		close(fd);
		exit(1);
	}
    validate_extension_cub(file);
    validate_tex(fd, "NO");
	validate_tex(fd, "SO");
	validate_tex(fd, "WE");
	validate_tex(fd, "EA");
	l = get_next_line(fd);
	free(l);
	validate_rgb(fd, "F ");
	validate_rgb(fd, "C ");
	close(fd);
}
