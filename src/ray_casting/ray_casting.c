/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufonten <yufonten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 22:28:57 by yufonten          #+#    #+#             */
/*   Updated: 2024/10/08 22:28:57 by yufonten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

#define MAP_WIDTH 8
#define MAP_HEIGHT 8

int worldMap[MAP_WIDTH][MAP_HEIGHT] = {
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,1},
    {1,0,1,0,1,0,0,1},
    {1,0,1,0,1,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,1,1,0,1,0,1},
    {1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1}
};

double playerX = 3.5;
double playerY = 3.5;
double dirX = -1;  // Direção inicial do jogador (olhando para cima no mapa)
double dirY = 0;   // Vetor da direção
double planeX = 0;
double planeY = 0.66;  // Define o "campo de visão" (field of view)

#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define MOVE_SPEED 0.7  // Velocidade de movimento
#define ROT_SPEED 0.7  // Velocidade de rotação

int key_press(int keycode, t_cub *cub)
{
    if (keycode == 65307)
        final_free(cub);
    if (keycode == 65362)  // Seta para cima (andar para frente)
    {
        if (worldMap[(int)(playerX + dirX * MOVE_SPEED)][(int)playerY] == 0) playerX += dirX * MOVE_SPEED;
        if (worldMap[(int)playerX][(int)(playerY + dirY * MOVE_SPEED)] == 0) playerY += dirY * MOVE_SPEED;
    }
    if (keycode == 65364)  // Seta para baixo (andar para trás)
    {
        if (worldMap[(int)(playerX - dirX * MOVE_SPEED)][(int)playerY] == 0) playerX -= dirX * MOVE_SPEED;
        if (worldMap[(int)playerX][(int)(playerY - dirY * MOVE_SPEED)] == 0) playerY -= dirY * MOVE_SPEED;
    }
    if (keycode == 65361)  // Seta para esquerda (rotacionar à esquerda)
    {
        double oldDirX = dirX;
        dirX = dirX * cos(ROT_SPEED) - dirY * sin(ROT_SPEED);
        dirY = oldDirX * sin(ROT_SPEED) + dirY * cos(ROT_SPEED);
        double oldPlaneX = planeX;
        planeX = planeX * cos(ROT_SPEED) - planeY * sin(ROT_SPEED);
        planeY = oldPlaneX * sin(ROT_SPEED) + planeY * cos(ROT_SPEED);
    }
    if (keycode == 65363)  // Seta para direita (rotacionar à direita)
    {
        double oldDirX = dirX;
        dirX = dirX * cos(-ROT_SPEED) - dirY * sin(-ROT_SPEED);
        dirY = oldDirX * sin(-ROT_SPEED) + dirY * cos(-ROT_SPEED);
        double oldPlaneX = planeX;
        planeX = planeX * cos(-ROT_SPEED) - planeY * sin(-ROT_SPEED);
        planeY = oldPlaneX * sin(-ROT_SPEED) + planeY * cos(-ROT_SPEED);
    }

    // Após qualquer movimento, redesenhar a cena
    mlx_clear_window(cub->ptr_mlx, cub->w_mlx);  // Limpar a janela
    ray_casting(cub->ptr_mlx, cub->w_mlx);  // Desenhar a cena novamente
    return (0);
}

void ray_casting(void *mlx, void *win)
{
    int x;
    for (x = 0; x < WIN_WIDTH; x++)
    {
        // Calcula a posição do raio e a direção
        double cameraX = 2 * x / (double)WIN_WIDTH - 1; // Coordenada no espaço da câmera
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        // Posição inicial do mapa
        int mapX = (int)playerX;
        int mapY = (int)playerY;

        // Delta da distância que o raio percorre de uma linha de grade à próxima
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);

        // Variáveis de rastreamento de passos
        int stepX, stepY;
        double sideDistX, sideDistY;

        // Definir stepX e stepY de acordo com a direção do raio
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (playerX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - playerX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (playerY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - playerY) * deltaDistY;
        }

        // Executar o DDA (Digital Differential Analyzer) para encontrar o ponto de colisão com a parede
        int hit = 0;
        int side;
        while (hit == 0)
        {
            // Pular para a próxima linha de grade
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            // Verificar se atingiu uma parede
            if (worldMap[mapX][mapY] > 0) hit = 1;
        }

        // Calcular a distância até a parede
        double perpWallDist;
        if (side == 0)
            perpWallDist = (mapX - playerX + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - playerY + (1 - stepY) / 2) / rayDirY;

        // Calcular a altura da linha para desenhar a parede
        int lineHeight = (int)(WIN_HEIGHT / perpWallDist);

        // Calcular o início e fim da linha
        int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
        if (drawEnd >= WIN_HEIGHT) drawEnd = WIN_HEIGHT - 1;

        // Escolher a cor com base no lado da parede
        int color;
        if (side == 0)
            color = 0xFF0000; // Vermelho para as paredes verticais
        else
            color = 0x00FF00; // Verde para as paredes horizontais

        // Desenhar a linha vertical (parede) na tela
        for (int y = drawStart; y < drawEnd; y++)
        {
            mlx_pixel_put(mlx, win, x, y, color);
        }
    }
}
