/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:59 by ecorona-          #+#    #+#             */
/*   Updated: 2024/02/04 16:15:27 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_point(t_vector *p, t_img *img)
{
	t_vector	*coords;
	float_t		z_warp;
	int			pixel;
	int			r;
	int			g;
	int			b;

	coords = ft_calloc(1, sizeof(*coords));
	z_warp = (p->z + ((float_t) 434/2)) / (1000 + 434);
	r = -0xff * z_warp;
	g = 0x11 + (0x11 * z_warp)/2;
	b = 0x44 + (0x11 * z_warp)/2;
	pixel = (0x00000000 | (r << (2 * 8)) | (g << (1 * 8)) | b);
	v_assign(coords, *p, 1);
	v_planeproj(coords, (t_vector){0, 0, 1}, 1);
	// TODO COORDS IS ALLOCATED AND CAN RETURN NULL, MAKE A FUNCTION THAT DOESNT DEPEND ON ALLOCATION !!!
	img_pixel_put(img, coords->x, coords->y, pixel);
	free(coords);
}

void	connect_vertices(t_vector *v1, t_vector *v2, t_img *img)
{
	float_t		dist;
	t_vector	step;
	t_vector	point;

	point.x = v1->x;
	point.y = v1->y;
	point.z = v1->z;
	dist = v_distance(v1, v2);
	step.x = -((v1->x - v2->x) / dist);
	step.y = -((v1->y - v2->y) / dist);
	step.z = -((v1->z - v2->z) / dist);
	while ((int) v_distance(&point, v2) > 1)
	{
		point.x += step.x;
		point.y += step.y;
		point.z += step.z;
		draw_point(&point, img);
	}
}

t_vector	**create_grid(int width, int height, int step)
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
	(void)step;
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

void	scene_draw(t_scene *scene)
{
	int			i;
	int			j;
	t_vector	*node1;
	t_vector	*node2;
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
			node2 = v_sum(&obj->grid[i][j], &cam->origin, 0);
			if (scene->perspective)
			{
				node2->x = node2->x * (cam->dist / node2->z) * ZOOM;
				node2->y = node2->y * (cam->dist / node2->z) * ZOOM;
			}
			v_sum(node2, &obj->origin, 1);
			// MORE ALLOCS MORE POINTS OF FAILURE
			if (i > 0)
			{
				node1 = v_sum(&obj->grid[i - 1][j], &cam->origin, 0);
				if (scene->perspective)
				{
					node1->x = node1->x * (cam->dist / node1->z) * ZOOM;
					node1->y = node1->y * (cam->dist / node1->z) * ZOOM;
				}
				if (node1->z > cam->dist && node2->z > cam->dist)
				{
					v_sum(node1, &obj->origin, 1);
					connect_vertices(node1, node2, obj->img);
				}
				free(node1);
			}
			if (j > 0)
			{
				node1 = v_sum(&obj->grid[i][j - 1], &cam->origin, 0);
				if (scene->perspective)
				{
					node1->x = node1->x * (cam->dist / node1->z) * ZOOM;
					node1->y = node1->y * (cam->dist / node1->z) * ZOOM;
				}
				if (node1->z > cam->dist && node2->z > cam->dist)
				{
					v_sum(node1, &obj->origin, 1);
					connect_vertices(node1, node2, obj->img);
				}
				free(node1);
			}
			free(node2);
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
				v_rotate(&obj->grid[i][j++], axis, a, 1);
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

	(void)param;
	(void)scene;
	(void)win;
	(void)img;
	scene = (t_scene *)param;
	win = scene->obj->win;
	img = create_img(win->mlx_ptr, IMG_X, IMG_Y, NULL);
	img->x = scene->obj->img->x;
	img->y = scene->obj->img->y;
	mlx_destroy_image(win->mlx_ptr, scene->obj->img->img_ptr);
	scene->obj->img = img;
	mlx_clear_window(win->mlx_ptr, win->win_ptr);
	scene_draw(scene);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, img->img_ptr, (int) img->x, (int) img->y);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, img->img_ptr, img->x, img->y);
	return (0);
}

int	scene_rot(void *param)
{
	t_scene		*scene;
	t_img		*img;
	t_win		*win;
	t_vector	v;
	int			x;
	int			y;

	scene = (t_scene *)param;
	img = scene->obj->img;
	win = scene->obj->win;
	img = create_img(win->mlx_ptr, IMG_X, IMG_Y, NULL);
	img->x = scene->obj->img->x;
	img->y = scene->obj->img->y;
	mlx_destroy_image(win->mlx_ptr, scene->obj->img->img_ptr);
	scene->obj->img = img;
	mlx_mouse_get_pos(win->mlx_ptr, win->win_ptr, &x, &y);
	v = (t_vector){x, y, 0};
	obj_rotate(scene->obj, (t_vector){-(y - scene->origin.y), x - scene->origin.x, 0}, -v_distance(&scene->origin, &v) * ROT_FACTOR);
	scene->origin = v;
	scene_draw(scene);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, img->img_ptr, img->x, img->y);
	return (0);
}

int	scene_shift(void *param)
{
	t_scene		*scene;
	t_img		*img;
	t_win		*win;
	t_vector	v;
	int			x;
	int			y;

	scene = (t_scene *)param;
	img = scene->obj->img;
	win = scene->obj->win;
	img = create_img(win->mlx_ptr, IMG_X, IMG_Y, NULL);
	img->x = scene->obj->img->x;
	img->y = scene->obj->img->y;
	mlx_destroy_image(win->mlx_ptr, scene->obj->img->img_ptr);
	scene->obj->img = img;
	mlx_mouse_get_pos(win->mlx_ptr, win->win_ptr, &x, &y);
	v = (t_vector){x, y, 0};
	img->x += (v.x - scene->origin.x) * MOVE_FACTOR;
	img->y += (v.y - scene->origin.y) * MOVE_FACTOR;
	scene->origin = v;
	scene_draw(scene);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, img->img_ptr, img->x, img->y);
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
		scene->cam->origin.z -= ZOOM_FACTOR;
	else if (button == 5 && scene->perspective)
		scene->cam->origin.z += ZOOM_FACTOR;
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
	exit(EXIT_SUCCESS);
}

int	key_hook(int keycode, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (keycode == XK_Escape)
		quit(param);
	if (keycode == XK_p)
		scene->perspective = (scene->perspective + 1) % 2;
	return (0);
}
