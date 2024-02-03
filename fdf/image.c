/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:35:52 by ecorona-          #+#    #+#             */
/*   Updated: 2024/02/03 17:41:47 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_img	*create_img(void *mlx_ptr, int width, int height, t_img_conf *conf)
{
	t_img		*image;
	void		*img_ptr;
	char		*data;

	image = ft_calloc(1, sizeof(*image));
	if (!image)
		return (NULL);
	img_ptr = mlx_new_image(mlx_ptr, width, height);
	image->img_ptr = img_ptr;
	if (!conf)
		image->conf = (t_img_conf){32, width * 4, 0};
	else
		image->conf = *conf;
	data = mlx_get_data_addr(img_ptr, &(image->conf.bpp), \
		&(image->conf.len), &(image->conf.end));
	image->data = data;
	image->width = width;
	image->height = height;
	return (image);
}

int	img_pixel_put(t_img *image, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if (x > image->width || x <= 0)
		return (-1);
	else if (y > image->height || y <= 0)
		return (-1);
	y--;
	x--;
	if (image->conf.end == 0)
	{
		pixel = image->data + (y * image->conf.len) + (x * image->conf.bpp / 8);
		*(int *)pixel = color;
	}
	return (0);
}

int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*image;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "Image Test");
	image = create_img(mlx_ptr, 50, 50, NULL);
	img_pixel_put(image, 50, 50, 0x00ff0000);
	mlx_put_image_to_window(mlx_ptr, win_ptr, image->img_ptr, 0, 0);
	mlx_loop(mlx_ptr);
}
