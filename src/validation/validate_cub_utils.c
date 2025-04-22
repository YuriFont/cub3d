/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cub_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:26:57 by yufonten          #+#    #+#             */
/*   Updated: 2025/04/20 22:36:00 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	error_tex(t_cub *cub, char *msg, int *validate)
{
	close(cub->fd_cub);
	if (validate[0])
		free(cub->i_tex.no);
	if (validate[1])
		free(cub->i_tex.so);
	if (validate[2])
		free(cub->i_tex.we);
	if (validate[3])
		free(cub->i_tex.ea);
	ft_fprintf(2, "%s", msg);
	exit(1);
}

int	finish_validate(int *validates)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (validates[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

int	line_with_error(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isalpha(line[i]))
			return (1);
		i++;
	}
	return (0);
}
