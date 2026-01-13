/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:24:39 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/13 17:49:16 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_world(t_world *w)
{
	int	i;

	i = 0;
	free(w->cam.to_world.data);
	free(w->cam.from_world.data);
	while (i < w->num_shapes)
	{
		free(w->shapes[i].to_world.data);
		free(w->shapes[i].from_world.data);
		i++;
	}
	free(w->shapes);
	free(w->lights);
}

static double	compute_pixel_step(t_cam *cam, int hor, int ver)
{
	double	half_view;
	double	aspect;

	half_view = tan(((cam->fov * 3.14159) / 180.0) / 2.0);
	aspect = (double)hor / (double)ver;
	if (aspect > 1 || equal(aspect, 1.0))
	{
		cam->half_width = half_view;
		cam->half_height = half_view / aspect;
	}
	else
	{
		cam->half_width = half_view * aspect;
		cam->half_height = half_view;
	}
	return ((cam->half_width * 2.0) / (double) hor);
}

static void	mlx_logic_handling(t_data *mlx)
{
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.pointer, 0, 0);
	printf("Done with raytracing\n");
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.pointer);
	mlx_loop(mlx->mlx_ptr);
	end_program(mlx);
}

int	main(int argc, char *argv[])
{
	t_data	mlx;
	t_world	w;
	int		i;
	int		j;
	t_color	color;

	i = 0;
	if (argc != 2)
		return (1);
	if (init_program(&w, &mlx, argv))
		return (1);
	w.cam.pixel_step = compute_pixel_step(&w.cam, mlx.x, mlx.y);
	while (i < mlx.x)
	{
		j = 0;
		while (j < mlx.y)
		{
			color = run_raytracer(&w, i, j);
			my_pixel_put(&mlx.img, i, j, rgb_color(color.r, color.g, color.b));
			j++;
		}
		i++;
	}
	mlx_logic_handling(&mlx);
	return (0);
}
