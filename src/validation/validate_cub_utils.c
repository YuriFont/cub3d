/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cub_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:26:57 by yufonten          #+#    #+#             */
/*   Updated: 2025/04/19 18:27:01 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
