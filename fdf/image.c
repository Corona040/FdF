/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:35:52 by ecorona-          #+#    #+#             */
/*   Updated: 2024/02/04 01:32:21 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_img	*create_img(void *mlx_ptr, int width, int height, t_img_conf *conf)
{
	t_img		*img;
	void		*img_ptr;
	char		*data;

	img = ft_calloc(1, sizeof(*img));
	if (!img)
		return (NULL);
	img_ptr = mlx_new_image(mlx_ptr, width, height);
	img->img_ptr = img_ptr;
	if (!conf)
		img->conf = (t_img_conf){32, width * 4, 0};
	else
		img->conf = *conf;
	data = mlx_get_data_addr(img_ptr, &(img->conf.bpp), \
		&(img->conf.len), &(img->conf.end));
	img->data = data;
	img->width = width;
	img->height = height;
	return (img);
}

int	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x >= img->width || x < 0)
		return (-1);
	else if (y >= img->height || y < 0)
		return (-1);
	if (img->conf.end == 0)
	{
		pixel = img->data + (y * img->conf.len) + (x * img->conf.bpp / 8);
		*(int *)pixel = color;
	}
	return (0);
}

// int	main(void)
// {
// 	void	*mlx_ptr;
// 	void	*win_ptr;
// 	t_img	*img;
//
// 	mlx_ptr = mlx_init();
// 	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "img Test");
// 	img = create_img(mlx_ptr, 50, 50, NULL);
// 	img_pixel_put(img, 50, 50, 0x00ff0000);
// 	mlx_put_img_to_window(mlx_ptr, win_ptr, img->img_ptr, 0, 0);
// 	mlx_loop(mlx_ptr);
// }
