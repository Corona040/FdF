/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorona- <ecorona-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:36:54 by ecorona-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/04 21:08:00 by ecorona-         ###   ########.fr       */
=======
/*   Updated: 2024/02/07 18:12:23 by ecorona-         ###   ########.fr       */
>>>>>>> 0bb12c1 (Fix unnecessary alloc)
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	int			fd;
	char		*line;
	char		**z_val;
	char		**z_vals[1000];
	void		*mlx_ptr;
	void		*win_ptr;
	t_win		win;
	t_vector	**grid;
	int			grid_x;
	int			grid_y;
	t_obj		obj;
	t_img		*img;
	t_cam		cam;
	t_scene		scene;

	char		*aux;

	grid_y = 0;
	grid_x = 0;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd > 2)
		{
			grid_y = 0;
			line = get_next_line(fd);
			while (line)
			{
				z_val = ft_split(line, ' ');
				free(line);
				z_vals[grid_y] = z_val;
				grid_y++;
				line = get_next_line(fd);
				grid_x = 0;
				while (z_val[grid_x])
				{
					// free(z_val[grid_x]);
					grid_x++;
				}
				// free(z_val);
			}
		}
		close(fd);
		mlx_ptr = mlx_init();
		win_ptr = mlx_new_window(mlx_ptr, WIN_X, WIN_Y, "FdF by ecorona-");
		win = (t_win){mlx_ptr, win_ptr};
		grid = create_grid(grid_x, grid_y, GRID_STEP);
		for (int i = 0; i < grid_y; i++)
		{
			for (int j = 0; z_vals[i][j]; j++)
			{
				aux = ft_strchr(z_vals[i][j], ',');
				if (aux)
					*aux = '\0';
				grid[grid_x - j - 1][i].y = -ft_atoi(z_vals[i][j]) * Z_FACTOR;
			}
		}
		img = create_img(win.mlx_ptr, IMG_X, IMG_Y, NULL);
		img->x = (float_t)(WIN_X - IMG_X) / 2;
		img->y = (float_t)(WIN_Y - IMG_Y) / 2;
		obj = (t_obj){(t_vector){(float_t)IMG_X / 2, (float_t)IMG_Y / 2, 0}, grid_x, grid_y, grid, img, &win};
		cam = (t_cam){(t_vector){0, 0, CAM_POS}, FOV};
		scene = (t_scene){&obj, &cam, (t_vector){0, 0, 0}, 0};
		// obj_rotate(scene.obj, (t_vector){0, 1, 0}, 3 * M_PI / 4);
		// obj_rotate(scene.obj, (t_vector){1, 0, 0}, M_PI / 4);
		obj_rotate(scene.obj, (t_vector){1, 0, 0}, M_PI / 2);
		obj_rotate(scene.obj, (t_vector){0, 0, 1}, M_PI);
		mlx_do_key_autorepeatoff(mlx_ptr);
		mlx_hook(win_ptr, DestroyNotify, StructureNotifyMask, quit, (void *)&scene);
		mlx_hook(win_ptr, ButtonPress, ButtonPressMask, mouse_press_hook, (void *)&scene);
		mlx_hook(win_ptr, ButtonRelease, ButtonReleaseMask, mouse_release_hook, (void *)&scene);
		mlx_key_hook(win_ptr, key_hook, (void *)&scene);
		mlx_loop_hook(mlx_ptr, animate, (void *)&scene);
		mlx_loop(mlx_ptr);
	}
}
