/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scenery.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:06:43 by ecorona-          #+#    #+#             */
/*   Updated: 2024/04/05 11:10:20 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_win	*init_scene_win(void)
{
	t_win	*win;

	win = ft_calloc(1, sizeof(t_win));
	if (!win)
		exit(EXIT_FAILURE);
	win->mlx_ptr = mlx_init();
	win->win_ptr = mlx_new_window(win->mlx_ptr, WIN_X, WIN_Y, "FdF by ecorona");
	return (win);
}

t_img	*init_scene_img(t_win *win)
{
	t_img	*img;

	img = create_img(win->mlx_ptr, IMG_X, IMG_Y, NULL);
	if (!img)
		exit(EXIT_FAILURE);
	img->x = (float_t)(WIN_X - IMG_X) / 2;
	img->y = (float_t)(WIN_Y - IMG_Y) / 2;
	return (img);
}
