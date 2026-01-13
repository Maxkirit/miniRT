/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:32:58 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/13 17:49:48 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	init_mlx_infra(t_data *mlx)
{
	init_mlx(mlx, SCREEN_W, SCREEN_H);
	mlx->img.pointer = mlx_new_image(mlx->mlx_ptr, SCREEN_W, SCREEN_H);
	if (!mlx->img.pointer)
		error(mlx);
	mlx->img.pixels = mlx_get_data_addr(mlx->img.pointer, &mlx->img.bpp,
			&mlx->img.line_size, &mlx->img.endian);
	if (!mlx->img.pixels)
		error(mlx);
}

static void	init_world(t_world *w)
{
	w->num_lights = 0;
	w->num_shapes = 0;
	w->lights = NULL;
	w->shapes = NULL;
	w->ambient.ratio = -1;
	w->cam.fov = -1;
	w->cam.to_world.data = NULL;
	w->cam.from_world.data = NULL;
}

static int	set_transfo_mtx(t_world *w)
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

int	init_program(t_world *w, t_data *mlx, char **argv)
{
	init_world(w);
	if (parse_file(argv[1], w) == -1)
		return (free_world(w), 1);
	if (set_transfo_mtx(w) == -1)
		return (free_world(w), 1);
	check_light_spacing(w);
	mlx->w = w;
	init_mlx_infra(mlx);
	return (0);
}
