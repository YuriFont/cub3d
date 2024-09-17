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

typedef	struct s_tex
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*cf;
	char	*cc;
}	t_tex;

typedef struct s_cub
{
	int		fd_cub;
	t_tex	tex;
}	t_cub;

//error
//error.c
int	    error(char *msg, t_cub *cub);

//fill_struct
//fill_struct.c
void	fill_struct(t_cub *cub, char *file);

//utils
//utils.c
void	free_cub(t_cub *cub);

#endif
