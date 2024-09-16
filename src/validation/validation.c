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

/*static void	validate_textures(char *file)
{

}*/

void	validation(t_cub *cub, char *file)
{
	validate_extension(file);
	if ((cub->fd_cub = open(file, O_RDONLY)) == -1)
		error("Error: could not open the file\n");
}
