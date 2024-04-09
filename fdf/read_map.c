/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:49:01 by ecorona-          #+#    #+#             */
/*   Updated: 2024/04/09 21:51:32 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	read_map_file(char *path)
{
	t_map	map;
	int		fd;

	map.y = 0;
	map.x = 0;
	map.vals = 0;
	fd = open(path, O_RDONLY);
	if (fd > 2)
		file_to_map(&map, fd);
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

	grid = ft_calloc(1, sizeof(*grid));
	if (!grid)
		return (NULL);
	grid->v = create_gridv(map.x, map.y, GRID_STEP);
	if (!grid->v)
		return (NULL);
	grid->c = create_gridc(map.x, map.y);
	if (!grid->c)
		return (NULL);
	grid_to_map(grid, &map);
	grid->xy[0] = map.x;
	grid->xy[1] = map.y;
	free_map(&map);
	return (grid);
}

void	file_to_map(t_map *map, int fd)
{
	char	**z_val;
	char	*line;
	int		n_nl;

	map->y = 0;
	line = get_next_line(fd);
	while (line)
	{
		z_val = ft_split(line, ' ');
		free(line);
		if (map_append(map, z_val) == -1 || check_zval(z_val, &n_nl) == -1)
			map_failure(map);
		map->y++;
		line = get_next_line(fd);
	}
	if (n_nl > 0 && n_nl != map->y)
		map_failure(map);
	map->x = 0;
	while (z_val[map->x])
		map->x++;
}
