/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:49:01 by ecorona-          #+#    #+#             */
/*   Updated: 2024/04/05 09:09:47 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	read_map_file(char *path)
{
	t_map	map;
	int		fd;
	char	**z_val;
	char	*line;

	map.y = 0;
	map.x = 0;
	map.vals = 0;
	fd = open(path, O_RDONLY);
	if (fd > 2)
	{
		map.y = 0;
		line = get_next_line(fd);
		while (line)
		{
			z_val = ft_split(line, ' ');
			free(line);
			if (map_append(&map, z_val) == -1)
			{
				free_map(&map);
				exit(EXIT_FAILURE);
			}
			map.y++;
			line = get_next_line(fd);
		}
		map.x = 0;
		while (z_val[map.x])
			map.x++;
	}
	else
	{
		close(fd);
		exit(EXIT_SUCCESS);
	}
	close(fd);
	return (map);
}

int	map_append(t_map *map, char **z_val)
{
	char	***temp;
	int		i;

	temp = map->vals;
	map->vals = ft_calloc(map->y + 1, sizeof(char **));
	if (!map->vals)
		return (-1);
	if (temp)
	{
		i = 0;
		while (i < map->y)
		{
			map->vals[i] = temp[i];
			i++;
		}
		map->vals[i] = z_val;
		free(temp);
	}
	else
		map->vals[0] = z_val;
	return (0);
}

t_grid	*get_grid_from_map(t_map map)
{
	t_grid	*grid;
	char	*aux;
	int		i;
	int		j;

	grid = ft_calloc(1, sizeof(*grid));
	if (!grid)
		return (NULL);
	grid->v = create_gridv(map.x, map.y, GRID_STEP);
	if (!grid->v)
		return (NULL);
	grid->c = create_gridc(map.x, map.y);
	if (!grid->c)
		return (NULL);
	i = 0;
	while (i < map.y)
	{
		j = 0;
		while (map.vals[i][j])
		{
			aux = ft_strchr(map.vals[i][j], ',');
			grid->c[map.x - j - 1][i] = itoc(0xFFFFFF);
			if (aux)
			{
				*aux = '\0';
				grid->c[map.x - j - 1][i] = itoc(xatoi(aux + 1));
			}
			grid->v[map.x - j - 1][i].y = -ft_atoi(map.vals[i][j]) * Z_FACTOR;
			j++;
		}
		i++;
	}
	grid->xy[0] = map.x;
	grid->xy[1] = map.y;
	free_map(&map);
	return (grid);
}
