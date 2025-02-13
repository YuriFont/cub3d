#include "../inc/cub3d.h"

int copy_frame(t_img *dest, t_img *source)
{
	dest->img_ptr = source->img_ptr;
	dest->img_data = source->img_data;
	dest->bpp = source->bpp;
	dest->line_len = source->line_len;
	dest->endian = source->endian;
	dest->width = source->width;
	dest->height = source->height;
}

/* 	teste troca de textura com um gif */
/* char filename[35];
for (int i = 0 ; i < 10; i++) {
	sprintf(filename, "./assets/test/frame_wall_%d.xpm", i);
	load_image_texture(&cub, &cub.frames[i], filename);
} */

/* 	// função para trocar os valores das variaveis da textura */
/* 	// copy_frame(&cub.tex_east, &cub.frames[0]); */