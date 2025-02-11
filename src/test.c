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