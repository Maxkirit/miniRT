/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:18:59 by mkeerewe          #+#    #+#             */
/*   Updated: 2026/01/10 11:13:56 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ray_for_pixel(t_world *w, double px, double py)
{
	t_ray	ray;
	t_tuple	pixel_pos; // on canvas

	ray.origin = mat_tuple_mult(w->cam.to_world, point(0, 0, 0));
	pixel_pos = point((w->cam.half_width * -1.0) + ((px + 0.5) * w->cam.pixel_step), -1.0, w->cam.half_height - ((py + 0.5) * w->cam.pixel_step));
	pixel_pos = mat_tuple_mult(w->cam.to_world, pixel_pos);
	ray.dir = vec_normalise(substr_tuples(pixel_pos, ray.origin));
	return (ray);
}

t_color	run_raytracer(t_world *w, int x, int y)
{
	t_ray	cam_ray;
	t_intersection	hit;
	t_color	color;

	cam_ray = ray_for_pixel(w, (double) x , (double) y); // in world-space
	if (intersections(cam_ray, *w, &hit) == -1)
	{
		free_world(w);
		exit(1);
	}
	if (hit.shape == NULL)
	{
		color.r = 0.0;
		color.g = 0.0;
		color.b = 0.0;
	}
	else
	{
		color = lighting(w, hit.shape, neg_tuples(cam_ray.dir), add_tuples(cam_ray.origin, mult_vec_scalar(cam_ray.dir, hit.t)));
		// color.r = hit.shape->mat.color.r;
		// color.g = hit.shape->mat.color.g;
		// color.b = hit.shape->mat.color.b;
	}
	return (color);
}
