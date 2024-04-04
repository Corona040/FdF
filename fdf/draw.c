/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:59 by ecorona-          #+#    #+#             */
/*   Updated: 2024/04/04 10:44:58 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_point(t_vector *p, t_rgb color, t_img *img)
{
	t_vector	coords;

	v_assign(&coords, *p, 1);
	v_planeproj(&coords, (t_vector){0, 0, 1}, 1);
	img_pixel_put(img, coords.x, coords.y, ctoi(color) | 0xFF000000);
}

// int	get_color_from_warp(float_t z_warp)
// {
// 	int	r;
// 	int	g;
// 	int	b;
//
// 	r = -0xff * z_warp;
// 	g = 0x11 + (0x11 * z_warp) / 2;
// 	b = 0x44 + (0x11 * z_warp) / 2;
// 	return (0x00000000 | (r << (2 * 8)) | (g << (1 * 8)) | b);
// }

void	connect_vertices(t_vector *v1, t_vector *v2, t_rgb c1, t_rgb c2, t_img *img)
{
	float_t		dist;
	t_vector	step;
	t_vector	point;
	t_rgb		gradient;

	(void) c1;
	(void) c2;
	point.x = v1->x;
	point.y = v1->y;
	point.z = v1->z;
	dist = v_distance(v1, v2);
	gradient = get_gradient(c1, c2, dist);
	step.x = -((v1->x - v2->x) / dist);
	step.y = -((v1->y - v2->y) / dist);
	step.z = -((v1->z - v2->z) / dist);
	while ((int) v_distance(&point, v2) > 1)
	{
		point.x += step.x;
		point.y += step.y;
		point.z += step.z;
		c1.r += gradient.r;
		c1.g += gradient.g;
		c1.b += gradient.b;
		draw_point(&point, c1, img);
	}
}

t_rgb	get_gradient(t_rgb c1, t_rgb c2, float_t dist)
{
	t_rgb	grad;

	grad.r = -((c1.r - c2.r) / dist);
	grad.g = -((c1.g - c2.g) / dist);
	grad.b = -((c1.b - c2.b) / dist);
	return (grad);
}

t_vector	**create_gridv(int width, int height, float_t step)
{
	t_vector	**grid;
	int			i;
	int			j;

	grid = ft_calloc(width, sizeof(t_vector *));
	if (!grid)
		return (0);
	i = 0;
	while (i < width)
	{
		grid[i] = ft_calloc(height, sizeof(**grid));
		if (!grid[i++])
			return (0);
	}
	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < height)
		{
			v_assign(&grid[i][j], (t_vector){i * (float_t)step - ((float_t)(step * width) / 2) + (float_t)step / 2, 0, j * (float_t)step - ((float_t)(step * height) / 2) + (float_t)step / 2}, 1);
			j++;
		}
		i++;
	}
	return (grid);
}

t_rgb	**create_gridc(int width, int height)
{
	t_rgb	**grid;
	int		i;

	grid = ft_calloc(width, sizeof(int *));
	if (!grid)
		return (0);
	i = 0;
	while (i < width)
	{
		grid[i] = ft_calloc(height, sizeof(**grid));
		if (!grid[i++])
			return (0);
	}
	return (grid);
}

t_vector	*add_perspective(t_vector *node, t_scene *scene, int inplace)
{
	t_vector	*result;

	if (inplace)
		result = node;
	else
	{
		result = ft_calloc(1, sizeof(*result));
		if (!result)
			return (NULL);
		result->z = node->z;
	}
	result->x = node->x * (scene->cam->dist / node->z) * ZOOM;
	result->y = node->y * (scene->cam->dist / node->z) * ZOOM;
	return (result);
}

void	scene_draw(t_scene *scene)
{
	int			i;
	int			j;
	t_vector	node[2];
	t_obj		*obj;
	t_cam		*cam;

	cam = scene->cam;
	obj = scene->obj;
	i = 0;
	while (i < obj->width)
	{
		j = 0;
		while (j < obj->height)
		{
			v_assign(&node[0], obj->grid->v[i][j], 1);
			v_sum(&node[0], &cam->origin, 1);
			if (scene->perspective)
				add_perspective(&node[0], scene, 1);
			v_sum(&node[0], &obj->origin, 1);
			if (i > 0)
			{
				v_assign(&node[1], obj->grid->v[i - 1][j], 1);
				v_sum(&node[1], &cam->origin, 1);
				if (scene->perspective)
					add_perspective(&node[1], scene, 1);
				if (node[1].z > cam->dist && node[0].z > cam->dist)
				{
					v_sum(&node[1], &obj->origin, 1);
					connect_vertices(&node[1], &node[0], obj->grid->c[i - 1][j], obj->grid->c[i][j], obj->img);
				}
			}
			if (j > 0)
			{
				v_assign(&node[1], obj->grid->v[i][j - 1], 1);
				v_sum(&node[1], &cam->origin, 1);
				if (scene->perspective)
					add_perspective(&node[1], scene, 1);
				if (node[1].z > cam->dist && node[0].z > cam->dist)
				{
					v_sum(&node[1], &obj->origin, 1);
					connect_vertices(&node[1], &node[0], obj->grid->c[i][j - 1], obj->grid->c[i][j], obj->img);
				}
			}
			j++;
		}
		i++;
	}
}

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
				v_rotate(&obj->grid->v[i][j++], axis, a, 1);
			}
			i++;
		}
	}
}

void	obj_translate(t_obj *obj, t_vector axis, float_t val)
{
	if (v_module(&axis) != 0)
		v_shift(&(obj->origin), axis, val, 1);
}

int	animate(void *param)
{
	t_scene		*scene;
	t_win		*win;
	t_img		*img;

	scene = (t_scene *)param;
	win = scene->obj->win;
	img = create_img(win->mlx_ptr, IMG_X, IMG_Y, NULL);
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
