/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 08:52:01 by ecorona-          #+#    #+#             */
/*   Updated: 2024/04/05 08:54:59 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	animate(void *param)
{
	t_scene		*scene;
	t_win		*win;
	t_img		*img;

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
	mlx_clear_window(win->mlx_ptr, win->win_ptr);
	scene_draw(scene);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, \
		img->img_ptr, (int) img->x, (int) img->y);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, \
		img->img_ptr, img->x, img->y);
	return (0);
}

int	mouse_press_hook(int button, int x, int y, void *param)
{
	t_scene	*scene;
	t_win	*win;

	scene = (t_scene *)param;
	win = scene->obj->win;
	if (button == 1)
	{
		scene->origin = (t_vector){x, y, 0};
		mlx_loop_hook(win->mlx_ptr, scene_rot, param);
	}
	if (button == 3)
	{
		scene->origin = (t_vector){x, y, 0};
		mlx_loop_hook(win->mlx_ptr, scene_shift, param);
	}
	else if (button == 4 && scene->perspective)
		scene->cam->origin.z -= scene->cam->zoom_factor;
	else if (button == 5 && scene->perspective)
		scene->cam->origin.z += scene->cam->zoom_factor;
	return (0);
}

int	mouse_release_hook(int button, int x, int y, void *param)
{
	t_scene	*scene;
	t_win	*win;

	scene = (t_scene *)param;
	win = scene->obj->win;
	if (button == 1 || button == 3)
	{
		scene->origin = (t_vector){x, y, 0};
		mlx_loop_hook(win->mlx_ptr, animate, param);
	}
	return (0);
}

int	quit(void *param)
{
	t_scene	*scene;
	t_win	*win;

	scene = (t_scene *)param;
	win = scene->obj->win;
	mlx_loop_end(win->mlx_ptr);
	mlx_destroy_image(win->mlx_ptr, scene->obj->img->img_ptr);
	mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	mlx_destroy_display(win->mlx_ptr);
	free(win->mlx_ptr);
	free_scene(scene);
	exit(EXIT_SUCCESS);
}

int	key_hook(int keycode, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (keycode == XK_ESCAPE)
		quit(param);
	if (keycode == XK_P)
		scene->perspective = (scene->perspective + 1) % 2;
	if (keycode == XK_UP && scene->cam->dist < (float_t)FOV * 10)
	{
		scene->cam->dist *= 10;
		scene->cam->origin.z *= 10;
		scene->cam->zoom_factor *= 10;
	}
	if (keycode == XK_DOWN && scene->cam->dist > (float_t)FOV / 10)
	{
		scene->cam->dist /= 10;
		scene->cam->origin.z /= 10;
		scene->cam->zoom_factor /= 10;
	}
	return (0);
}
