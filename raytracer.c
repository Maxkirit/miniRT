/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:18:59 by mkeerewe          #+#    #+#             */
/*   Updated: 2026/01/08 16:28:19 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ray_for_pixel(t_world *w, double px, double py)
{
	t_ray	ray;
	t_tuple	pixel_pos; // on canvas

	ray.origin = point(0, 0, 0);
	pixel_pos = point((w->cam.half_width * -1.0) + ((px + 0.5) * w->cam.pixel_step), -1, w->cam.half_height - ((py + 0.5) * w->cam.pixel_step));
	ray.dir = substr_tuples(pixel_pos, ray.origin);
	return (ray);
}

t_color	run_raytracer(t_world *w, int x, int y)
{
	t_ray	cam_ray;

	cam_ray = ray_for_pixel(w, (double) x , (double) y); // in camera-space
	// add intersect function here
}
