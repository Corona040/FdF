/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 01:43:00 by ecorona-          #+#    #+#             */
/*   Updated: 2024/02/01 01:43:02 by ecorona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	draw(void *param)
{
	struct window	*window;
	int				x;
	int				y;

	window = (struct window *) param;
	mlx_mouse_get_pos(window->mlx_ptr, window->win_ptr, &x, &y);
	mlx_pixel_put(window->mlx_ptr, window->win_ptr, x, y, 0xffffffff);
	return (0);
}

int	start_draw(int button, int x, int y, void *param)
{
	struct window	*window;

	(void) x;
	(void) y;
	window = (struct window *) param;
	if (button == 1)
		mlx_loop_hook(window->mlx_ptr, draw, (void *) window);
	if (button == 3)
		mlx_clear_window(window->mlx_ptr, window->win_ptr);
	return (0);
}

int	end_draw(int button, int x, int y, void *param)
{
	struct window	*window;

	(void) x;
	(void) y;
	window = (struct window *) param;
	if (button == 1)
		mlx_loop_hook(window->mlx_ptr, NULL, NULL);
	return (0);
}

int	quit(void *param)
{
	struct window	*window;

	window = (struct window *) param;
	mlx_loop_end(window->mlx_ptr);
	mlx_destroy_window(window->mlx_ptr, window->win_ptr);
	return (0);
}

int	escape(int keycode, void *param)
{
	if (keycode == XK_Escape)
		quit(param);
	return (0);
}


int	main(void)
{
	void			*mlx_ptr;
	void			*win_ptr;
	struct window	window;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		ft_printf("mlx_init fail\n");
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "title");
	if (!win_ptr)
		ft_printf("mlx_new_window fail\n");
	window.mlx_ptr = mlx_ptr;
	window.win_ptr = win_ptr;
	mlx_hook(win_ptr, DestroyNotify, StructureNotifyMask, quit, (void *) &window);
	mlx_hook(win_ptr, ButtonPress, ButtonPressMask, start_draw, (void *) &window);
	mlx_hook(win_ptr, ButtonRelease, ButtonReleaseMask, end_draw, (void *) &window);
	mlx_key_hook(win_ptr, escape, (void *) &window);
	mlx_loop(mlx_ptr);
}
