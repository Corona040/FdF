/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:35:52 by ecorona-          #+#    #+#             */
/*   Updated: 2024/04/04 10:45:39 by ecorona-         ###   ########.fr       */
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
