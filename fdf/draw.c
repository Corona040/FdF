/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:59 by ecorona-          #+#    #+#             */
/*   Updated: 2024/02/03 18:09:45 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_point(t_vector *p, struct window *window)
{
	t_vector	*coords;
	float_t		z_warp;
	int			pixel;
	int 		r;
	int			g;
	int			b;

	z_warp = (p->z + ((float_t) 434/2)) / (1000 + 434);
	r = 0xff * z_warp;
	g = 0x77 - (0x11 * z_warp)/2;
	b = 0x77 - (0x11 * z_warp)/2;
	pixel = (0x00000000 | (r << (2 * 8)) | (g << (1 * 8)) | b);
	coords = v_planeproj(p, (t_vector){0, 0, 1}, 0);
	(void) window;
	mlx_pixel_put(window->mlx_ptr, window->win_ptr, \
		(int) coords->x, (int) coords->y, pixel);
	free(coords);
}

void	connect_vertices(t_vector *v1, t_vector *v2, struct window *window)
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
		draw_point(&point, window);
	}
}

t_vector	**create_cube(t_vector o, float_t len)
{
	t_vector	**cube_v;
	int			i;

	cube_v = ft_calloc(8, sizeof(t_vector *));
	i = 0;
	while (i < 8)
		cube_v[i++] = ft_calloc(1, sizeof(**cube_v));
	v_assign(cube_v[0], o, 1);
	v_assign(cube_v[1], (t_vector){o.x, o.y, o.z + len}, 1);
	v_assign(cube_v[2], (t_vector){o.x + len, o.y, o.z + len}, 1);
	v_assign(cube_v[3], (t_vector){o.x + len, o.y, o.z}, 1);
	v_assign(cube_v[4], (t_vector){o.x, o.y + len, o.z}, 1);
	v_assign(cube_v[5], (t_vector){o.x, o.y + len, o.z + len}, 1);
	v_assign(cube_v[6], (t_vector){o.x + len, o.y + len, o.z + len}, 1);
	v_assign(cube_v[7], (t_vector){o.x + len, o.y + len, o.z}, 1);
	return (cube_v);
}

t_vector	*cheat_warp(t_vector *u)
{
	float_t		z_warp;
	float_t		x_factor;
	float_t		y_factor;

	z_warp = (u->z + ((float_t)434 / 2)) / (1000 + ((float_t)434 / 2));
	x_factor = (u->x - (125 + 375)) / 250;
	y_factor = (u->y - (125 + 375)) / 250;
	u->x += 200 * x_factor * z_warp;
	u->y += 200 * y_factor * z_warp;
	return (u);
}

void	draw_cube(t_object *cube, struct window *window)
{
	int			i;
	t_vector	*node1;
	t_vector	*node2;

	i = 0;
	while (i < 4)
	{
		node1 = v_sum(cube->obj[i], &cube->origin, 0);
		cheat_warp(node1);
		node2 = v_sum(cube->obj[(i + 1) % 4], &cube->origin, 0);
		cheat_warp(node2);
		connect_vertices(node1, node2, window);
		free(node1);
		free(node2);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		node1 = v_sum(cube->obj[i + 4], &cube->origin, 0);
		cheat_warp(node1);
		node2 = v_sum(cube->obj[(i + 1) % 4 + 4], &cube->origin, 0);
		cheat_warp(node2);
		connect_vertices(node1, node2, window);
		free(node1);
		free(node2);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		node1 = v_sum(cube->obj[i], &cube->origin, 0);
		cheat_warp(node1);
		node2 = v_sum(cube->obj[i + 4], &cube->origin, 0);
		cheat_warp(node2);
		connect_vertices(node1, node2, window);
		free(node1);
		free(node2);
		i++;
	}
}

void	rotate_obj(t_object *obj, t_vector axis, float_t a)
{
	int	i;

	i = 0;
	while (i < obj->size)
		v_rotate(obj->obj[i++], axis, a, 1);
}

void	translate_obj(t_object *obj, t_vector axis, float_t val)
{
	int	i;

	i = 0;
	while (i < obj->size)
	{
		v_translate(&(obj->origin), axis, val, 1);
		i++;
	}
}

int	animate(void *param)
{
	struct window	*window;
	t_object		*cube_obj;
	t_img			*img;

	cube_obj = (t_object *)param;
	window = ((struct s_object *)param)->window;
	mlx_clear_window(window->mlx_ptr, window->win_ptr);
	rotate_obj(cube_obj, (t_vector){1, 1, 0}, .001);
	if (cube_obj->origin.x >= 500 || cube_obj->origin.x <= 250)
		cube_obj->speed.x = -cube_obj->speed.x;
	if (cube_obj->origin.y >= 500 || cube_obj->origin.y <= 250)
		cube_obj->speed.y = -cube_obj->speed.y;
	if (cube_obj->origin.z >= 1000 || cube_obj->origin.z <= 0)
		cube_obj->speed.z = -cube_obj->speed.z;
	translate_obj(cube_obj, (t_vector){1,0,0}, cube_obj->speed.x);
	translate_obj(cube_obj, (t_vector){0,1,0}, cube_obj->speed.y);
	translate_obj(cube_obj, (t_vector){0,0,1}, cube_obj->speed.z);
	draw_cube((t_object *)param, (void *)window);
	return (0);
}

int	main(void)
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_vector		**cube;
	struct window	window;
	t_object	cube_object;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 750, 750, "test");
	cube = create_cube((t_vector) {-125, -125, -125}, 250);
	window = (struct window){mlx_ptr, win_ptr};
	cube_object = (t_object){8, (t_vector){375, 375, 500}, (t_vector){0.03, -0.02, 0.01}, cube, &window};
	draw_cube(&cube_object, (void *) &window);
	mlx_loop_hook(mlx_ptr, animate, (void *) &cube_object);
	mlx_loop(mlx_ptr);
}
