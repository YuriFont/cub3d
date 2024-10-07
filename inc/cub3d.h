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
# include "../libs/minilibx-linux/mlx.h"

typedef	struct s_tex
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*cf;
	char	*cc;
}	t_tex;

typedef	struct s_map
{
	char	**map;
	int		height;
}	t_map;

typedef struct s_cub
{
	int		fd_cub;
	t_tex	tex;
	t_map	info_map;
	void	*ptr_mlx;
	void	*w_mlx;
}	t_cub;

//fill_struct
//fill_struct.c
void	fill_struct(t_cub *cub, char *file);

//utils
//utils.c
void	free_cub(t_cub *cub, int flag);
int	    error(char *msg, t_cub *cub, int flag, int win);
int		final_free(t_cub *cub);

//validation
//validate_map.c
void	validate_map(t_cub *cub);
//validate_map_utils.c
int		check_character(char c);
void	validate_spaces(t_cub *cub);
void	validate_unevenness_bot(t_cub *cub);
void	validate_unevenness_top(t_cub *cub);
//check_around.c
int		check_around(char **map, int y, int x, int h);

//window
//init_window.c
void	initializing_window(t_cub *cub);

#endif
