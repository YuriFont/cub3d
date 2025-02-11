#include "../inc/cub3d.h"

int	animation_wall(t_cub *cub)
{
	static int	i;
	static int	frames;

	if (i == 10)
		i = 0;
	if (frames == 40)
	{
		copy_frame(&cub->tex_east, &cub->frames[i]);
		i++;
		frames = 0;
	}
	frames++;
	return (0);
}

int	run_code(t_cub *cub)
{
	animation_wall(cub);
	move_player(cub);
	create_vision(cub);
	mlx_put_image_to_window(cub->ptr_mlx, cub->w_mlx, cub->i_img.img_ptr, 0, 0);
	return (0);
}