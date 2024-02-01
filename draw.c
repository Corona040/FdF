/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:59 by ecorona-          #+#    #+#             */
/*   Updated: 2024/02/01 18:33:20 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "minilibx-linux/mlx.h"

void	draw_point(t_vector *p, void *param)
{
	struct window	*window;
	t_vector		*coords;

	window = (struct window *) param;
	coords = v_planeproj(p, 1, 0);
	mlx_pixel_put(window->mlx_ptr, window->win_ptr, (int) coords->x, (int) coords->y, 0xffffffff);
	free(coords);
}

void	connect_vertices(t_vector *vertice1, t_vector *vertice2, void *param)
{
	float_t			dist;
	t_vector		step;
	t_vector		point;
	struct window	*window;

	window = (struct window *) param;
	point.x = vertice1->x;
	point.y = vertice1->y;
	point.z = vertice1->z;
	dist = distance(vertice1, vertice2);
	step.x = -((vertice1->x - vertice2->x) / dist);
	step.y = -((vertice1->y - vertice2->y) / dist);
	step.z = -((vertice1->z - vertice2->z) / dist);
	while ((int) distance(&point, vertice2) > 1)
	{
		point.x += step.x;
		point.y += step.y;
		point.z += step.z;
		draw_point(&point, param);
	}
}

t_vector	**create_cube(t_vector origin, float_t len)
{
	t_vector	**cube_vertices;
	int			i;

	cube_vertices = ft_calloc(8, sizeof(t_vector *));
	i = 0;
	while (i < 8)
		cube_vertices[i++] = ft_calloc(1, sizeof(**cube_vertices));
	v_assign(cube_vertices[0], origin, 1);
	v_assign(cube_vertices[1], (t_vector) {origin.x, origin.y, origin.z + len}, 1);
	v_assign(cube_vertices[2], (t_vector) {origin.x + len, origin.y, origin.z + len}, 1);
	v_assign(cube_vertices[3], (t_vector) {origin.x + len, origin.y, origin.z}, 1);
	v_assign(cube_vertices[4], (t_vector) {origin.x, origin.y + len, origin.z}, 1);
	v_assign(cube_vertices[5], (t_vector) {origin.x, origin.y + len, origin.z + len}, 1);
	v_assign(cube_vertices[6], (t_vector) {origin.x + len, origin.y + len, origin.z + len}, 1);
	v_assign(cube_vertices[7], (t_vector) {origin.x + len, origin.y + len, origin.z}, 1);
	return (cube_vertices);
}

void	draw_cube(t_vector **cube, void *param)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		connect_vertices(cube[i], cube[(i + 1) % 4], param);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		connect_vertices(cube[i + 4], cube[(i + 1) % 4 + 4], param);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		connect_vertices(cube[i], cube[i + 4], param);
		i++;
	}
}

void	rotate_cube(t_vector **cube, float_t a, int axis)
{
	int	i = 0;

	while (i < 8)
		v_rotate(cube[i++], a, axis, 1);
}

void	translate_cube(t_vector **cube, int axis, float_t val)
{
	int	i = 0;

	while (i < 8)
	{
		if (axis == 1)
			cube[i]->z = cube[i]->z + val;
		else if (axis == 2)
			cube[i]->y = cube[i]->y + val;
		else if (axis == 3)
			cube[i]->x = cube[i]->x + val;
		i++;
	}
}

struct s_object
{
	t_vector		**cube;
	struct window	*window;
};

int	animate(void *param)
{
	struct window	*window;
	t_vector		**cube;

	cube = ((struct s_object *)param)->cube;
	window = ((struct s_object *)param)->window;
	mlx_clear_window(window->mlx_ptr, window->win_ptr);
	rotate_cube(cube, .0001, 2);
	translate_cube(cube, 3, 250);
	translate_cube(cube, 2, 250);
	draw_cube(cube, (void *) window);
	translate_cube(cube, 3, -250);
	translate_cube(cube, 2, -250);
	return (0);
}

int	main(void)
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_vector		**cube;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "test");
	struct window	window = {mlx_ptr, win_ptr};
	cube = create_cube((t_vector) {-125, -125, -125}, 250);
	rotate_cube(cube, .1, 1);
	rotate_cube(cube, .1, 3);
	struct s_object	cube_object = {cube, &window};
	mlx_loop_hook(mlx_ptr, animate, (void *) &cube_object);
	mlx_loop(mlx_ptr);
}
