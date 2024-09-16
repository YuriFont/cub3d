/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:14:09 by yufonten          #+#    #+#             */
/*   Updated: 2024/09/14 12:14:09 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libs/libft/libft.h"

typedef struct s_cub
{
	int	fd_cub;
}	t_cub;

//error
//error.c
int	    error(char *msg);

//validation
//validation.c
void	validation(t_cub *cub, char *file);

#endif
