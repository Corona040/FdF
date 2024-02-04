/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:59 by ecorona-          #+#    #+#             */
/*   Updated: 2024/02/04 14:09:23 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define WIN_X 1000
#define WIN_Y 1000
#define GRID_STEP 100
#define IMG_X 1000
#define IMG_Y 1000
#define CAM_POS 500
#define FOV 100
#define ZOOM_FACTOR 25
#define MOVE_FACTOR	1
#define ROT_FACTOR .01
#define ZOOM 15

void	draw_point(t_vector *p, t_img *img)
{
	t_vector	*coords;

	coords = ft_calloc(1, sizeof(*coords));
	v_assign(coords, *p, 1);
	v_planeproj(coords, (t_vector){0, 0, 1}, 1);
	// TODO COORDS IS ALLOCATED AND CAN RETURN NULL, MAKE A FUNCTION THAT DOESNT DEPEND ON ALLOCATION !!!
	img_pixel_put(img, coords->x, coords->y, 0xffffffff);
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
	v_assign(&grid[0][0], (t_vector){-(float_t)step / 2, 0, -(float_t)step / 2}, 1);
	v_assign(&grid[1][0], (t_vector){(float_t)step / 2, 0, -(float_t)step / 2}, 1);
	v_assign(&grid[0][1], (t_vector){-(float_t)step / 2, 0, (float_t)step / 2}, 1);
	v_assign(&grid[1][1], (t_vector){(float)step / 2, 0, (float_t)step / 2}, 1);
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
			node2->x = node2->x * (cam->dist / node2->z) * ZOOM;
			node2->y = node2->y * (cam->dist / node2->z) * ZOOM;
			v_sum(node2, &obj->origin, 1);
			// MORE ALLOCS MORE POINTS OF FAILURE
			if (i > 0)
			{
				node1 = v_sum(&obj->grid[i - 1][j], &cam->origin, 0);
				node1->x = node1->x * (cam->dist / node1->z) * ZOOM;
				node1->y = node1->y * (cam->dist / node1->z) * ZOOM;
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
				node1->x = node1->x * (cam->dist / node1->z) * ZOOM;
				node1->y = node1->y * (cam->dist / node1->z) * ZOOM;
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
	else if (button == 4)
		scene->cam->origin.z -= ZOOM_FACTOR;
	else if (button == 5)
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
	if (keycode == XK_Escape)
		quit(param);
	return (0);
}

int	main(void)
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_win		win;
	t_vector	**grid;
	t_obj		obj;
	t_img		*img;
	t_cam		cam;
	t_scene		scene;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIN_X, WIN_Y, "FdF by ecorona-");
	win = (t_win){mlx_ptr, win_ptr};
	grid = create_grid(2, 2, GRID_STEP);
	img = create_img(win.mlx_ptr, IMG_X, IMG_Y, NULL);
	img->x = (float_t)(WIN_X - IMG_X) / 2;
	img->y = (float_t)(WIN_Y - IMG_Y) / 2;
	obj = (t_obj){(t_vector){(float_t)IMG_X / 2, (float_t)IMG_Y / 2, 0}, 2, 2, grid, img, &win};
	cam = (t_cam){(t_vector){0, 0, CAM_POS}, FOV};
	scene = (t_scene){&obj, &cam, (t_vector){0, 0, 0}};
	mlx_do_key_autorepeatoff(mlx_ptr);
	mlx_hook(win_ptr, DestroyNotify, StructureNotifyMask, quit, (void *)&scene);
	mlx_hook(win_ptr, ButtonPress, ButtonPressMask, mouse_press_hook, (void *)&scene);
	mlx_hook(win_ptr, ButtonRelease, ButtonReleaseMask, mouse_release_hook, (void *)&scene);
	mlx_key_hook(win_ptr, key_hook, (void *)&scene);
	mlx_loop_hook(mlx_ptr, animate, (void *)&scene);
	mlx_loop(mlx_ptr);
}
