/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:24:47 by ecorona-          #+#    #+#             */
/*   Updated: 2024/04/10 08:54:51 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_matrix(void **m, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(m[i++]);
	free(m);
}

void	free_obj(t_obj *obj)
{
	if (obj)
	{
		if (obj->win)
			free(obj->win);
		if (obj->img)
			free(obj->img);
		if (obj->grid)
		{
			if (obj->grid->v)
				free_matrix((void **)obj->grid->v, obj->grid->xy[0]);
			if (obj->grid->c)
				free_matrix((void **)obj->grid->c, obj->grid->xy[0]);
			free(obj->grid);
		}
		free(obj);
	}
}

void	free_scene(t_scene *scene)
{
	if (scene)
	{
		if (scene->obj)
			free_obj(scene->obj);
		if (scene->cam)
			free(scene->cam);
	}
}

void	free_map(t_map *map, int one_more)
{
	int	i;
	int	j;

	i = 0;
	if (map->vals)
	{
		while (i < map->y + one_more)
		{
			j = 0;
      while (map->vals[i][j])
      {
        free(map->vals[i][j]);
        j++;
      }
			if (map->vals[i])
				free(map->vals[i]);
			i++;
		}
		free(map->vals);
	}
}
