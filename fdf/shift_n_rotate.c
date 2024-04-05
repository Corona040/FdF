/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_n_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 08:58:18 by ecorona-          #+#    #+#             */
/*   Updated: 2024/04/05 09:15:14 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	obj_rotate(t_obj *obj, t_vector axis, float_t a)
{
	int	i;
	int	j;

	if (v_module(&axis) != 0)
	{
		i = 0;
		while (i < obj->width)
		{
			j = 0;
			while (j < obj->height)
			{
				if (!v_rotate(&obj->grid->v[i][j++], axis, a, 1))
					exit(EXIT_FAILURE);
			}
			i++;
		}
	}
}

void	obj_translate(t_obj *obj, t_vector axis, float_t val)
{
	if (v_module(&axis) != 0)
		if (!v_shift(&(obj->origin), axis, val, 1))
			exit(EXIT_FAILURE);
}

int	scene_rot(void *param)
{
	t_scene		*scene;
	t_img		*img;
	t_win		*win;
	t_vector	v;
	int			mouse_pos[2];

	scene = (t_scene *)param;
	win = scene->obj->win;
	img = create_img(win->mlx_ptr, IMG_X, IMG_Y, NULL);
	if (!img)
		exit(EXIT_FAILURE);
	img->x = scene->obj->img->x;
	img->y = scene->obj->img->y;
	mlx_destroy_image(win->mlx_ptr, scene->obj->img->img_ptr);
	free(scene->obj->img);
	scene->obj->img = img;
	mlx_mouse_get_pos(win->mlx_ptr, win->win_ptr, mouse_pos, mouse_pos + 1);
	v = (t_vector){mouse_pos[0], mouse_pos[1], 0};
	obj_rotate(scene->obj, (t_vector){(mouse_pos[1] - scene->origin.y) * -1, \
		mouse_pos[0] - scene->origin.x, 0}, \
		-v_distance(&scene->origin, &v) * ROT_FACTOR);
	scene->origin = v;
	scene_draw(scene);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, \
		img->img_ptr, img->x, img->y);
	return (0);
}

int	scene_shift(void *param)
{
	t_scene		*scene;
	t_img		*img;
	t_win		*win;
	t_vector	v;
	int			mouse_pos[2];

	scene = (t_scene *)param;
	win = scene->obj->win;
	img = create_img(win->mlx_ptr, IMG_X, IMG_Y, NULL);
	if (!img)
		exit(EXIT_FAILURE);
	img->x = scene->obj->img->x;
	img->y = scene->obj->img->y;
	mlx_destroy_image(win->mlx_ptr, scene->obj->img->img_ptr);
	free(scene->obj->img);
	scene->obj->img = img;
	mlx_mouse_get_pos(win->mlx_ptr, win->win_ptr, mouse_pos, mouse_pos + 1);
	v = (t_vector){mouse_pos[0], mouse_pos[1], 0};
	img->x += (v.x - scene->origin.x) * MOVE_FACTOR;
	img->y += (v.y - scene->origin.y) * MOVE_FACTOR;
	scene->origin = v;
	scene_draw(scene);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, \
		img->img_ptr, img->x, img->y);
	return (0);
}
