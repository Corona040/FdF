/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:59 by ecorona-          #+#    #+#             */
/*   Updated: 2024/04/05 08:59:48 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_point(t_vector *p, t_rgb color, t_img *img)
{
	t_vector	coords;

	v_assign(&coords, *p, 1);
	if (!v_planeproj(&coords, (t_vector){0, 0, 1}, 1))
		exit(EXIT_FAILURE);
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

void	connect_vertices(t_arc arc, t_img *img)
{
	float_t		dist;
	t_vector	step;
	t_vector	point;
	t_rgb		gradient;

	point.x = arc.v1->x;
	point.y = arc.v1->y;
	point.z = arc.v1->z;
	dist = v_distance(arc.v1, arc.v2);
	gradient = get_gradient(arc.c1, arc.c2, dist);
	step.x = -((arc.v1->x - arc.v2->x) / dist);
	step.y = -((arc.v1->y - arc.v2->y) / dist);
	step.z = -((arc.v1->z - arc.v2->z) / dist);
	while ((int) v_distance(&point, arc.v2) > 1)
	{
		point.x += step.x;
		point.y += step.y;
		point.z += step.z;
		arc.c1.r += gradient.r;
		arc.c1.g += gradient.g;
		arc.c1.b += gradient.b;
		draw_point(&point, arc.c1, img);
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
					connect_vertices((t_arc){&node[1], &node[0], obj->grid->c[i - 1][j], obj->grid->c[i][j]}, obj->img);
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
					connect_vertices((t_arc){&node[1], &node[0], obj->grid->c[i][j - 1], obj->grid->c[i][j]}, obj->img);
				}
			}
			j++;
		}
		i++;
	}
}
