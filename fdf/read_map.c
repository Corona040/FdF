/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:49:01 by ecorona-          #+#    #+#             */
/*   Updated: 2024/04/01 13:26:14 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// line and z_val have allocs -> need free
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
			map.x = 0;
			while (z_val[map.x])
				map.x++;
		}
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
	grid->v = create_gridv(map.x, map.y, GRID_STEP);
	grid->c = create_gridc(map.x, map.y);
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

int	xatoi(char *hex)
{
	int		result;

	result = 0;
	if (hex[0] != '0' || hex[1] != 'x')
		return (0);
	else
	{
		hex += 2;
		while (*hex)
		{
			if (*hex >= '0' && *hex <= '9')
				result = (result + (*hex - '0')) * 16;
			else if (*hex >= 'A' && *hex <= 'F')
				result = (result + (*hex - 'A' + 10)) * 16;
			else
				return (0);
			hex++;
		}
	}
	return (result / 16);
}

t_rgb	itoc(int i)
{
	t_rgb	rgb;

	rgb.r = (i & 0xFF0000) / (256 * 256);
	rgb.g = (i & 0x00FF00) / (256);
	rgb.b = i & 0x0000FF;
	return (rgb);
}

int	ctoi(t_rgb rgb)
{
	int	i;

	i = 0;
	i += rgb.r * 256 * 256;
	i += rgb.g * 256;
	i += rgb.b;
	return (i);
}
