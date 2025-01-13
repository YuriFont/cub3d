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
		WIDTH, HEIGHT);
	if (cub->i_img.img_ptr == NULL)
		error(cub, "Error: cannot create image\n", 1);
	cub->i_img.img_data = (int *)mlx_get_data_addr(cub->i_img.img_ptr,
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

void    create_background(t_cub *cub)
{
    int	c1;
	int	c2;

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
}

int	create_dda_vision(t_cub *cub)
{
	int mapPos[2];
	double rayX, rayY;
	for (int x = 0; x < WIDTH; x++) {
		// CADA RAIO NO EIXO X, USADO PARA AJUSTAR CADA RAIO QUE PARDE DA POSIÇÃO DO JOGADOR
		double cameraX = 2 * x /(double)WIDTH - 1;


		// RAIO DO PIXEL ATUAL
		rayX = cub->i_p.dir[0] + cub->i_p.plane[0] * cameraX;
		rayY = cub->i_p.dir[1] + cub->i_p.plane[1] * cameraX;

		// QUADRADO EM QUE O JOGADOR ESTA
		mapPos[0] = (int)cub->i_p.pos_x;
		mapPos[1] = (int)cub->i_p.pos_y;

		double deltaDistX, deltaDistY;
		// DISTANCIA ENTRE UM QUADRADO E OUTRO
		deltaDistX = fabs(1 / rayX);
		// deltaDistY = fabs(1 / rayY);
		deltaDistY = fabs(1 / rayY);

		// CALCULAR DISTANCIA PARA O LADO DA PAREDE
		double sideDistX, sideDistY;
		int stepX, stepY;
		if (rayX < 0)
		{
			stepX = -1;
			sideDistX = (cub->i_p.pos_x - mapPos[0]) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapPos[0] + 1.0 - cub->i_p.pos_x) * deltaDistX;
		}
		if (rayY < 0)
		{
			stepY = -1;
			sideDistY = (cub->i_p.pos_y - mapPos[1]) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapPos[1] + 1.0 - cub->i_p.pos_y) * deltaDistY;
		}
		// printf("DELTA DIST X: %f Y: %f\n", deltaDistX, deltaDistY);
		// printf("SIDE DIST X: %f Y: %f\n", sideDistX, sideDistY);
		int hit = 0;
		int side = -1;
		while (!hit)
		{
			// AVANÇA ATE ACHAR A PAREDE
			if (sideDistX < sideDistY) {
				sideDistX += deltaDistX;
				mapPos[0] += stepX;
				side = 0;
			} else {
				sideDistY += deltaDistY;
				mapPos[1] += stepY;
				side = 1;
			}
			// printf("%d, %d\n", mapPos[0], mapPos[1]);
			// VERIFICAR SE BATEU NA PAREDE
			if(cub->i_map.map[mapPos[1]][mapPos[0]] == '1') hit = 1;
		}

		// printf("Lado: %d, lado x %f, lado y %f, posição no mapa x = %d, y = %d\n", side, sideDistX, sideDistY, mapPos[0], mapPos[1]);
		double perpendicularDist = 0;
		if (side == 0) {
			// perpendicularDist = fabs(mapPos[0] - cub->i_p.pos_x + (1.0 - ((double)stepX / 2.0))) / rayX;
			// perpendicularDist = (sideDistX - deltaDistX);
			perpendicularDist = (mapPos[0] - cub->i_p.pos_x + (1 - stepX) / 2) / rayX;
		} else {
			// perpendicularDist = fabs(mapPos[1] - cub->i_p.pos_y + (1.0 - ((double)stepY / 2.0))) / rayY;
			//perpendicularDist = (sideDistY - deltaDistY);
			perpendicularDist = (mapPos[1] - cub->i_p.pos_y + (1 - stepY) / 2) / rayY;
		}

		int wallLine = (int)(HEIGHT / perpendicularDist);

		int lineStart = -wallLine / 2 + HEIGHT / 2;
		//  floor((HEIGHT / 2) - (wallLine / 2));
		if (lineStart < 0) lineStart = 0;
		int lineEnd = wallLine / 2 + HEIGHT / 2;
		if (lineEnd >= HEIGHT) lineEnd = HEIGHT - 1;
		//  floor((HEIGHT / 2) + (wallLine / 2));

		int c1 = create_color(cub->i_tex.cc[0], cub->i_tex.cc[1], cub->i_tex.cc[2]);

		// printf("Line: %f, Line Start: %f, Line end: %f\n", wallLine, lineStart, lineEnd);

		int *pixels = (int *)cub->i_img.img_data;
		int width = WIDTH;



		// Loop para desenhar na faixa entre lineStart e lineEnd
		for (int y = 0; y < HEIGHT; y++) {
					int index = y * width + x; // Cálculo do índice do pixel

					if (y < lineStart) {
						cub->i_img.img_data[index] = 0x87CEEB;
					} else if (y > lineEnd) {
						cub->i_img.img_data[index] = 0x228B22;
					}
					else {
						if (side == 1) { // Caso o raio tenha batido no lado vertical
							cub->i_img.img_data[index] = 0xAAAAAA; // Cor para o lado vertical (exemplo vermelho)
						} else { // Caso o raio tenha batido no lado horizontal
							cub->i_img.img_data[index] = 0x0000FF00 >> 8; // Cor para o lado horizontal (exemplo verde)
						}
					}
				}
	}
	return (0);
}

void	create_vision(t_cub *cub)
{
    // create_background(cub);
    create_dda_vision(cub);
    // Exibindo a imagem na janela
    mlx_put_image_to_window(cub->ptr_mlx, cub->w_mlx, cub->i_img.img_ptr, 0, 0);
	// mlx_destroy_image(cub->ptr_mlx, cub->i_img.img_ptr);
}
