#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <mlx.h>

#define WIDTH 640
#define HEIGHT 480
#define TEX_WIDTH 64
#define TEX_HEIGHT 64

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

int worldMap[MAP_WIDTH][MAP_HEIGHT] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};


typedef struct {
    double posX, posY;    // Posição do jogador
    double dirX, dirY;    // Direção do vetor
    double planeX, planeY; // Vetor do plano da câmera
    void *mlx;
    void *win;
    void *img;
    int *buffer;
    int bpp, size_line, endian;
} t_game;

void draw_buffer_to_image(t_game *game) {
    // int x, y;
    // for (y = 0; y < HEIGHT; y++) {
    //     for (x = 0; x < WIDTH; x++) {
    //         ((int *)game->buffer)[y * WIDTH + x] = game->buffer[y * WIDTH + x];
    //     }
    // }
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void render_scene(t_game *game) {
    for (int x = 0; x < WIDTH; x++) {
        double cameraX = 2 * x / (double)WIDTH - 1;
        double rayDirX = game->dirX + game->planeX * cameraX;
        double rayDirY = game->dirY + game->planeY * cameraX;

        int mapX = (int)game->posX;
        int mapY = (int)game->posY;

        double sideDistX;
        double sideDistY;

        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        int stepX;
        int stepY;
        int hit = 0;
        int side;

        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (game->posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - game->posX) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (game->posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - game->posY) * deltaDistY;
        }

        while (hit == 0) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (worldMap[mapX][mapY] > 0)
                hit = 1;
        }


        if (side == 0)
            perpWallDist = (mapX - game->posX + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - game->posY + (1 - stepY) / 2) / rayDirY;

        int lineHeight = (int)(HEIGHT / perpWallDist);

        int drawStart = -lineHeight / 2 + HEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + HEIGHT / 2;
        if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

        int color = (side == 1) ? 0xAAAAAA : 0xFFFFFF;

        for (int y = 0; y < HEIGHT; y++) {
            if (y < drawStart) {
                game->buffer[y * WIDTH + x] = 0x87CEEB; // Céu
            } else if (y > drawEnd) {
                game->buffer[y * WIDTH + x] = 0x228B22; // Chão
            } else {
                game->buffer[y * WIDTH + x] = color; // Parede
            }
        }
    }

    draw_buffer_to_image(game);
}

void handle_keys(t_game *game, int key) {
    double moveSpeed = 0.1;
    double rotSpeed = 0.05;

    if (key == 65363) { // Esquerda
        double oldDirX = game->dirX;
        game->dirX = game->dirX * cos(-rotSpeed) - game->dirY * sin(-rotSpeed);
        game->dirY = oldDirX * sin(-rotSpeed) + game->dirY * cos(-rotSpeed);
        double oldPlaneX = game->planeX;
        game->planeX = game->planeX * cos(-rotSpeed) - game->planeY * sin(-rotSpeed);
        game->planeY = oldPlaneX * sin(-rotSpeed) + game->planeY * cos(-rotSpeed);
    }
    if (key == 65361) { // Direita
        double oldDirX = game->dirX;
        game->dirX = game->dirX * cos(rotSpeed) - game->dirY * sin(rotSpeed);
        game->dirY = oldDirX * sin(rotSpeed) + game->dirY * cos(rotSpeed);
        double oldPlaneX = game->planeX;
        game->planeX = game->planeX * cos(rotSpeed) - game->planeY * sin(rotSpeed);
        game->planeY = oldPlaneX * sin(rotSpeed) + game->planeY * cos(rotSpeed);
    }
    if (key == 65362) { // Cima
        if (worldMap[(int)(game->posX + game->dirX * moveSpeed)][(int)(game->posY)] == 0)
            game->posX += game->dirX * moveSpeed;
        if (worldMap[(int)(game->posX)][(int)(game->posY + game->dirY * moveSpeed)] == 0)
            game->posY += game->dirY * moveSpeed;
    }
    if (key == 65364) { // Baixo
        if (worldMap[(int)(game->posX - game->dirX * moveSpeed)][(int)(game->posY)] == 0)
            game->posX -= game->dirX * moveSpeed;
        if (worldMap[(int)(game->posX)][(int)(game->posY - game->dirY * moveSpeed)] == 0)
            game->posY -= game->dirY * moveSpeed;
}

}

int key_hook(int keycode, t_game *game) {
    if (keycode == 65307) // ESC
        exit(0);
    handle_keys(game, keycode);
    render_scene(game);
    return 0;
}

int main() {
    t_game game;

    game.posX = 5;
    game.posY = 5;
    game.dirX = -1;
    game.dirY = 0;
    game.planeX = 0;
    game.planeY = 0.66;

    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "Raycasting");
    game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
    game.buffer = (int *)mlx_get_data_addr(game.img, &game.bpp, &game.size_line, &game.endian);

    render_scene(&game);
    mlx_hook(game.win, 2, 1L << 0, key_hook, &game);
    mlx_loop(game.mlx);

    return 0;
}
