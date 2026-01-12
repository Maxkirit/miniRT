/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:18:59 by mkeerewe          #+#    #+#             */
/*   Updated: 2026/01/09 15:18:12 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ray_for_pixel(t_world *w, double px, double py)
{
	t_ray	ray;
	t_tuple	pixel_pos; // on canvas

	ray.origin = point(0, 0, 0);
	pixel_pos = point((w->cam.half_width * -1.0) + ((px + 0.5) * w->cam.pixel_step), w->cam.half_height + ((py + 0.5) * w->cam.pixel_step), 1.0);
	ray.dir = substr_tuples(pixel_pos, ray.origin);
	return (ray);
}

t_color	run_raytracer(t_world *w, int x, int y)
{
	t_ray	cam_ray;
	t_intersection	hit;
	t_color	color;

	cam_ray = ray_for_pixel(w, (double) x , (double) y); // in camera-space
	if (intersections(cam_ray, *w, &hit) == -1)
	{
		free_world(w);
		exit(1);
	}
	if (hit.shape == NULL)
	{
		color.r = 0;
		color.g = 0;
		color.b = 0;
	}
	else
	{
		color.r = 1;
		color.g = 0;
		color.b = 0;
	}
	return (color);
}
