/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:33:46 by yufonten          #+#    #+#             */
/*   Updated: 2024/09/14 12:33:46 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*static void	free_struct(t_cub *cub)
{
	
}*/

int	error(char *msg, t_cub *cub)
{
	if (cub)
		free_struct(cub);
	ft_fprintf(2, "%s", msg);
	exit(1);
}
