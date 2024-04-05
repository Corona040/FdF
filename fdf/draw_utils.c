/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:33:26 by ecorona-          #+#    #+#             */
/*   Updated: 2024/04/05 10:45:19 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_arcx(t_scene *scene, t_vector *node, int i, int j)
{
	t_obj	*obj;
	t_cam	*cam;

	obj = scene->obj;
	cam = scene->cam;
	v_assign(&node[1], obj->grid->v[i - 1][j], 1);
	v_sum(&node[1], &cam->origin, 1);
	if (scene->perspective)
		add_perspective(&node[1], scene, 1);
	if (node[1].z > cam->dist && node[0].z > cam->dist)
	{
		v_sum(&node[1], &obj->origin, 1);
		connect_vertices((t_arc){&node[1], \
								&node[0], \
								obj->grid->c[i - 1][j], \
								obj->grid->c[i][j]}, \
						obj->img);
	}
}

void	draw_arcy(t_scene *scene, t_vector *node, int i, int j)
{
	t_obj	*obj;
	t_cam	*cam;

	obj = scene->obj;
	cam = scene->cam;
	v_assign(&node[1], obj->grid->v[i][j - 1], 1);
	v_sum(&node[1], &cam->origin, 1);
	if (scene->perspective)
		add_perspective(&node[1], scene, 1);
	if (node[1].z > cam->dist && node[0].z > cam->dist)
	{
		v_sum(&node[1], &obj->origin, 1);
		connect_vertices((t_arc){&node[1], \
								&node[0], \
								obj->grid->c[i][j - 1], \
								obj->grid->c[i][j]}, \
						obj->img);
	}
}
