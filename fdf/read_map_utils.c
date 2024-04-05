/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:08:47 by ecorona-          #+#    #+#             */
/*   Updated: 2024/04/05 09:08:52 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
