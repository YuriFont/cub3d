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

int	size_mat(char **config)
{
	int	i;

	i = 0;
	while (config[i])
		i++;
	if (i != 2)
		return (1);
	return (0);
}

int	validate_tex(t_cub *cub, char fw, char *line)
{
	int		fd_v;
	char	**config;
	char	*path;

	config = ft_split(line, ' ');
	path = ft_substr(config[1], 0, ft_strlen(config[1]) - 1);
	fd_v = open(path, O_RDONLY);
	if (fd_v == -1 || size_mat(config)|| validate_extension_xpm(path))
	{
		close(fd_v);
		free_matriz(config);
		free(path);
		free(line);
		close(cub->fd_cub);
		error(NULL, "Error: misconfiguration in textures\n", 0);
	}
	fill_textures(cub, fw, path);
	close(fd_v);
	free_matriz(config);
	return (1);
}

int	validate_rgb(t_cub *cub, char fc, char *line)
{
	char	**config;
	char	**n;
	int		e;

	config = ft_split(line, ' ');
	if (size_mat(config))
	{
		free_matriz(config);
		free(line);
		close(cub->fd_cub);
		error(NULL, "Error: misconfiguration in floor or ceiling\n", 0);
	}
	n = ft_split(config[1], ',');
	if (size_rgb(n) || validate_hx(n[0]) || validate_hx(n[1])
		|| validate_hx(n[2]))
	{
		free_matriz(config);
		free_matriz(n);
		free(line);
		close(cub->fd_cub);
		exit(1);
	}
	fill_colors(cub, fc, n, config);
	return (1);
}

int	loop_validate(t_cub *cub, char *line, int *validates)
{
	line = get_next_line(cub->fd_cub);
	while (line)
	{
		if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
			validates[0] = validate_tex(cub, 'N', line);
		else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
			validates[1] = validate_tex(cub, 'S', line);
		else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
			validates[2] = validate_tex(cub, 'W', line);
		else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
			validates[3] = validate_tex(cub, 'E', line);
		else if (line[0] == 'F' && line[1] == ' ')
			validates[4] = validate_rgb(cub, 'F', line);
		else if (line[0] == 'C' && line[1] == ' ')
			validates[5] = validate_rgb(cub, 'C', line);
		free(line);
		if (finish_validate(validates))
			return (0);
		line = get_next_line(cub->fd_cub);
	}
	close(cub->fd_cub);
	error(NULL, "Error: misconfiguration\n", 0);
	return (1);
}

void	validate_cub(t_cub *cub, char *file)
{
	int		validates[6];
	int		i;
	char	*line;

	i = 0;
	while (i < 6)
		validates[i++] = 0;
	cub->fd_cub = open(file, O_RDONLY);
	if (cub->fd_cub == -1)
	{
		ft_fprintf(2, "Error: cannot open this file\n");
		close(cub->fd_cub);
		exit(1);
	}
	validate_extension_cub(file);
	loop_validate(cub, line, validates);
}
