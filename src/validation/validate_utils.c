/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:49:35 by yufonten          #+#    #+#             */
/*   Updated: 2024/11/04 15:49:35 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	validate_extension_cub(char *file)
{
	int	i;

	i = ft_strlen(file);
	if (i < 5 || file[i - 1] != 'b' || file[i - 2] != 'u'
		|| file[i - 3] != 'c' || file[i - 4] != '.')
		error(NULL, "Error: the file must have a .cub extension\n", 0);
}

int	validate_extension_xpm(char *file)
{
	int	i;

	i = ft_strlen(file);
	if (i < 5 || file[i - 1] != 'm' || file[i - 2] != 'p'
		|| file[i - 3] != 'x' || file[i - 4] != '.')
		return (1);
	return (0);
}

int	size_rgb(char **n)
{
	int	i;

	i = 0;
	while (n[i] != 0)
		i++;
	if (i != 3)
	{
		ft_fprintf(2, "Error: misconfiguration in rgb numbers\n");
		return (1);
	}
	return (0);
}

int	validate_hx(char *num)
{
	int	n;

	n = ft_atoi(num);
	if (n > 255 || n < 0)
	{
		ft_fprintf(2, "Error: misconfiguration in rgb numbers\n");
		return (1);
	}
	return (0);
}
