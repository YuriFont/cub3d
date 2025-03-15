/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:41:03 by erramos           #+#    #+#             */
/*   Updated: 2025/03/15 15:41:05 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	initial_config(t_cub *cub, char *av)
{
	validate_cub(cub, av);
	validate_map(cub);
	fill_struct(cub, av);
	initializing_window(cub);
	return (1);
}

void	loading_game(t_cub *cub, char *av)
{
	initial_config(cub, av);
	load_texture(cub);
	create_img(cub);
}
