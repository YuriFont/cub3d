/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:01:01 by yufonten          #+#    #+#             */
/*   Updated: 2024/09/16 22:01:01 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_cub(t_cub *cub)
{
	int	i;

	i = 0;
	free(cub->tex.no);
	free(cub->tex.so);
	free(cub->tex.we);
	free(cub->tex.ea);
	free(cub->tex.cf);
	free(cub->tex.cc);
	while (cub->map[i][0] != 'e')
		free(cub->map[i++]);
	free(cub->map[i]);
}
