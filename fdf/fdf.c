/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:36:54 by ecorona-          #+#    #+#             */
/*   Updated: 2024/04/05 11:10:24 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_scene		scene;
	t_map		map;

	if (argc == 2)
	{
		map = read_map_file(argv[1]);
		init_scene_from_map(&scene, map);
		isometric_ize(&scene);
		hook_n_loop(&scene);
	}
}

void	init_scene_from_map(t_scene *scene, t_map map)
{
	t_win	*win;
	t_grid	*grid;
	t_img	*img;
	t_obj	*obj;
	t_cam	*cam;

	win = init_scene_win();
	img = init_scene_img(win);
	grid = get_grid_from_map(map);
	if (!grid)
		exit(EXIT_FAILURE);
	obj = ft_calloc(1, sizeof(t_obj));
	if (!obj)
		exit(EXIT_FAILURE);
	*obj = (t_obj){(t_vector){(float_t)IMG_X / 2, (float_t)IMG_Y / 2, 0}, \
		map.x, map.y, grid, img, win};
	cam = ft_calloc(1, sizeof(t_cam));
	if (!cam)
		exit(EXIT_FAILURE);
	*cam = (t_cam){(t_vector){0, 0, CAM_POS}, FOV, ZOOM_FACTOR};
	*scene = (t_scene){obj, cam, (t_vector){0, 0, 0}, 0};
}

void	isometric_ize(t_scene *scene)
{
	obj_rotate(scene->obj, (t_vector){0, 1, 0}, 3 * M_PI / 4);
	obj_rotate(scene->obj, (t_vector){1, 0, 0}, M_PI / 4);
}

void	parallel_ize(t_scene *scene)
{
	obj_rotate(scene->obj, (t_vector){1, 0, 0}, M_PI / 2);
	obj_rotate(scene->obj, (t_vector){0, 0, 1}, M_PI);
}

void	hook_n_loop(t_scene *scene)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = scene->obj->win->mlx_ptr;
	win_ptr = scene->obj->win->win_ptr;
	mlx_do_key_autorepeatoff(mlx_ptr);
	mlx_hook(win_ptr, DestroyNotify, StructureNotifyMask, quit, (void *)scene);
	mlx_hook(win_ptr, ButtonPress, ButtonPressMask, \
		mouse_press_hook, (void *)scene);
	mlx_hook(win_ptr, ButtonRelease, ButtonReleaseMask, \
		mouse_release_hook, (void *)scene);
	mlx_key_hook(win_ptr, key_hook, (void *)scene);
	mlx_loop_hook(mlx_ptr, animate, (void *)scene);
	mlx_loop(mlx_ptr);
}
