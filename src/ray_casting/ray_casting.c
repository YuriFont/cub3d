/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:57:56 by yufonten          #+#    #+#             */
/*   Updated: 2024/11/18 20:57:56 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	create_img(t_cub *cub)
{
	cub->i_img.img_ptr = mlx_new_image(cub->ptr_mlx,
		cub->i_win.w_width, cub->i_win.w_height);
	if (cub->i_img.img_ptr == NULL)
		error(cub, "Error: cannot create image\n", 1);
	cub->i_img.img_data = mlx_get_data_addr(cub->i_img.img_ptr,
		&cub->i_img.bpp, &cub->i_img.line_len, &cub->i_img.endian);
	if (cub->i_img.img_data == NULL)
		error(cub, "Error: cannot get data of image\n", 1);
	printf("line_len: %d, bpp: %d\n", cub->i_img.line_len, cub->i_img.bpp);
}

int create_color(int red, int green, int blue)
{
    return (red << 16) | (green << 8) | blue;
}

void put_pixel(t_cub *cub, int x, int y, int color)
{
    int pixel;

	if (x < 0 || x >= cub->i_win.w_width || y < 0 || y >= cub->i_win.w_height)
    	return;
    pixel = (y * cub->i_img.line_len) + (x * (cub->i_img.bpp / 8));
    cub->i_img.img_data[pixel] = color & 0xFF;          // Canal azul
    cub->i_img.img_data[pixel + 1] = (color >> 8) & 0xFF;   // Canal verde
    cub->i_img.img_data[pixel + 2] = (color >> 16) & 0xFF;  // Canal vermelho
}

void	ray_casting(t_cub *cub)
{
	int	c1;
	int	c2;

	create_img(cub);
	c1 = create_color(cub->i_tex.cc[0], cub->i_tex.cc[1], cub->i_tex.cc[2]);
	c2 = create_color(cub->i_tex.cf[0], cub->i_tex.cf[1], cub->i_tex.cf[2]);
	for (int y = 0; y < cub->i_win.w_height; y++)
    {
        for (int x = 0; x < cub->i_win.w_width; x++)
        {
            if (y < cub->i_win.w_height / 2)
                put_pixel(cub, x, y, c1);
            else
                put_pixel(cub, x, y, c2);
        }
    }
    // Exibindo a imagem na janela
    mlx_put_image_to_window(cub->ptr_mlx, cub->w_mlx, cub->i_img.img_ptr, 0, 0);
}
