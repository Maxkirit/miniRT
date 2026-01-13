/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:03:46 by mkeerewe          #+#    #+#             */
/*   Updated: 2026/01/13 19:33:44 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_tuple	reflect(t_tuple in, t_tuple normal_n)
{
	t_tuple	temp;

	temp = mult_vec_scalar(mult_vec_scalar(normal_n, 2),
			dot(in, normal_n));
	return (substr_tuples(in, temp));
}

int	is_in_shadow(t_world *w, t_tuple pt, t_light light)
{
	t_ray			shadow_ray;
	double			dist;
	t_intersection	hit;

	shadow_ray.origin = pt;
	shadow_ray.dir = substr_tuples(light.point, pt);
	dist = vec_magnitude(shadow_ray.dir);
	hit.shape = NULL;
	shadow_ray.dir = vec_normalise(shadow_ray.dir);
	intersections(shadow_ray, *w, &hit);
	if (hit.shape == NULL || hit.t > dist)
		return (0);
	return (1);
}

double	ref_dot_cam(t_tuple light_v, t_tuple surface_n, t_tuple cam_v)
{
	t_tuple	reflect_v;
	double	reflect_dot_cam;

	reflect_v = reflect(neg_tuples(light_v), surface_n);
	reflect_dot_cam = dot(reflect_v, cam_v);
	return (reflect_dot_cam);
}
