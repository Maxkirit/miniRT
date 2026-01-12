/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:24:39 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/09 14:31:57 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_mlx_infra(t_mlx *mlx)
{
	init_mlx(mlx, 1600, 900);
	mlx->img.pointer = mlx_new_image(mlx->mlx_ptr, 1600, 900);
	if (!mlx->img.pointer)
		error(mlx);
	mlx->img.pixels = mlx_get_data_addr(mlx->img.pointer, &mlx->img.bpp, &mlx->img.line_size, &mlx->img.endian);
	if (!mlx->img.pixels)
		error(mlx);
}

void	init_world(t_world *w)
{
	w->num_lights = 0;
	w->num_shapes = 0;
	w->lights = NULL;
	w->shapes = NULL;
	w->ambient.ratio = -1;
	w->cam.fov = -1;
}

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
	free(w->lights);
}

int	set_transfo_mtx(t_world *w)
{
	int	i;

	i = 0;
	w->cam.to_world = build_transfo_cam(w->cam);
	if (w->cam.to_world.data == NULL)
		return (-1);
	w->cam.from_world = inverse(w->cam.to_world);
	if (w->cam.from_world.data == NULL)
		return (free(w->cam.to_world.data), -1);
	while (i < w->num_shapes)
	{
		w->shapes[i].to_world = build_transfo(w->shapes[i]);
		if (w->shapes[i].to_world.data == NULL)
			return (-1);
		w->shapes[i].from_world = inverse(w->shapes[i].to_world);
		if (w->shapes[i].from_world.data == NULL)
			return (-1);
		i++;
	}
	return (0);
}

double	compute_pixel_step(t_cam *cam, int hor, int ver)
{
	double	half_view;
	double	aspect;

	half_view = tan(cam->fov / 2.0);
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

int	main(int argc, char *argv[])
{
	t_mlx	mlx;
	t_world	w;
	int		i;
	int		j;
	t_color	color;

	i = 0;
	if (argc != 2)
		return (1);
	init_world(&w);
	if (parse_file(argv[1], &w) == -1)
		return (free_world(&w), 1);
	if (set_transfo_mtx(&w) == -1)
		return (free_world(&w), 1);
	init_mlx_infra(&mlx);
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
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.pointer, 0, 0);
	mlx_destroy_image(mlx.mlx_ptr, mlx.img.pointer);
	mlx_loop(mlx.mlx_ptr);
	end_program(&mlx);
	return (0);
}
