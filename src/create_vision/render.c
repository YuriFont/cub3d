#include "../../inc/cub3d.h"

int	calculate_wall_height(t_rayInfo *infos)
{
	int	wall_line;

	wall_line = (int)(HEIGHT / infos->perp_wall_dist);
	infos->wall_start = -wall_line / 2 + HEIGHT / 2;
	if (infos->wall_start < 0)
		infos->wall_start = 0;
	infos->wall_end = wall_line / 2 + HEIGHT / 2;
	if (infos->wall_end >= HEIGHT)
		infos->wall_end = HEIGHT - 1;
	infos->line_height = wall_line;
	return (1);
}

int get_texture_color(t_img *texture, int tex_x, int tex_y)
{
    // Garantir que x e y estão dentro dos limites
    // if (x < 0) x = 0;
    // if (x >= texture->width) x = texture->width - 1;
    // if (y < 0) y = 0;
    // if (y >= texture->height) y = texture->height - 1;

    // if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
    // {
    //     fprintf(stderr, "Coordenadas fora dos limites da textura: x=%d, y=%d\n", x, y);
    //     return 0; // Retorne uma cor padrão ou informe o erro
    // }
    // // Calcular posição do pixel
    // int pixel = (y * texture->line_len) + (x * (texture->bpp / 8));
    // if (pixel < 0 || pixel >= (texture->line_len * texture->height)) {
    //     fprintf(stderr, "Índice do pixel fora dos limites: pixel=%d\n", pixel);
    //     return 0; // Retorna cor padrão (preta)
    // }
    // return *(int *)(texture->img_data + pixel);
    int x = (int)tex_x;
    int y = (int)tex_y;
    
    double dx = tex_x - x;
    double dy = tex_y - y;

    int pixel1 = *(int *)(texture->img_data + (y * texture->line_len) + (x * (texture->bpp / 8)));
    int pixel2 = *(int *)(texture->img_data + (y * texture->line_len) + ((x + 1) % texture->width * (texture->bpp / 8)));
    int pixel3 = *(int *)(texture->img_data + (((y + 1) % texture->height) * texture->line_len) + (x * (texture->bpp / 8)));
    int pixel4 = *(int *)(texture->img_data + (((y + 1) % texture->height) * texture->line_len) + ((x + 1) % texture->width * (texture->bpp / 8)));

    int blended_color = (
        (1 - dx) * (1 - dy) * pixel1 +
        dx * (1 - dy) * pixel2 +
        (1 - dx) * dy * pixel3 +
        dx * dy * pixel4
    );

    return blended_color;
}

t_img	*select_texture(t_cub *cub, t_rayInfo *infos)
{
	if (infos->side == 0)
	{
		if (infos->ray_dir_x > 0)
			return (&cub->tex_east);
		else
			return (&cub->tex_west);
	}
	else
	{
		if (infos->ray_dir_y > 0)
			return (&cub->tex_north);
		else
			return (&cub->tex_south);
	}
}

int	draw_sky(int *pixels, int x, t_rayInfo *infos)
{
	int	y;

	y = -1;
	while (y++ < infos->wall_start)
		pixels[y * WIDTH + x] = 0x87CEEB;
	return (1);
}

int	draw_floor(int *pixels, int x, t_rayInfo *infos)
{
	int	y;

	y = infos->wall_end - 1;
	while (y++ < HEIGHT)
		pixels[y * WIDTH + x] = 0x228B22;
	return (1);
}

int get_texture_pos_x(t_rayInfo *infos, t_img *texture)
{
	int	tex_x;

	tex_x = (infos->wall_x * (double)texture->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	return (tex_x);
}

int get_texture_pos_y(t_rayInfo *infos, t_img *texture, double tex_pos)
{
	int	tex_y;

	tex_y = (int)tex_pos;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= texture->height)
		tex_y = ((int)tex_pos) & (texture->height - 1);
	return (tex_y);
}

int	get_ray_hit_wall_x(t_cub *cub, t_rayInfo *infos)
{
	if (infos->side == 0)
		infos->wall_x = cub->i_p.pos_y + infos->perp_wall_dist
			* infos->ray_dir_y;
	else
		infos->wall_x = cub->i_p.pos_x + infos->perp_wall_dist
			* infos->ray_dir_x;
	infos->wall_x -= floor(infos->wall_x);
	return (1);
}

void	draw_line(t_cub *cub, t_rayInfo *infos, int x)
{
	int		*pixels;
	t_img	*texture;
	double	wall_x;
	double	step;
	double	tex_pos;
	double	tex_x;
	int		tex_y;
	int		color;
	int 	y;

	pixels = (int *)cub->i_img.img_data;
	texture = select_texture(cub, infos);


	// LOCAL ONDE O RAIO ATINGE A PAREDE
	get_ray_hit_wall_x(cub, infos);

	// COORDENADA X DA TEXTURA
	tex_x = get_texture_pos_x(infos, texture);

	step = 1.0 * texture->height / infos->line_height;
	tex_pos = (infos->wall_start - HEIGHT / 2 + infos->line_height / 2) * step;


	draw_sky(pixels, x, infos);
	draw_floor(pixels, x, infos);

	y = infos->wall_start;
	while (y < infos->wall_end)
	{
		tex_y = get_texture_pos_y(infos, texture, tex_pos);

		color = get_texture_color(texture, tex_x, tex_y);

		if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH)
    		pixels[y * WIDTH + x] = color;
		tex_pos += step;
		y++;
	}
	pixels[infos->wall_start * WIDTH + x] = get_texture_color(&cub->i_img, x, infos->wall_start);
	pixels[infos->wall_end * WIDTH + x] = get_texture_color(&cub->i_img, x, infos->wall_end);
}
