/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:36:27 by mkeerewe          #+#    #+#             */
/*   Updated: 2026/01/13 19:36:22 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	sphere_det(double a, double b, t_tuple s_to_r)
{
	double	c;
	double	discriminant;

	c = dot(s_to_r, s_to_r) - 1.0;
	discriminant = pow(b, 2.0) - 4 * a * c;
	return (discriminant);
}

//discrimant == 0 when 1 solution so we can compress code like that
int	intersect_sphere(t_shape *sphere, t_ray ray, t_intersection res[2])
{
	t_ray	ray_o;
	t_tuple	s_to_r;
	double	b;
	double	d;
	int		num;

	ray_o.dir = mat_tuple_mult(sphere->from_world, ray.dir);
	ray_o.origin = mat_tuple_mult(sphere->from_world, ray.origin);
	s_to_r = substr_tuples(ray_o.origin, point(0, 0, 0));
	b = 2 * dot(ray_o.dir, s_to_r);
	d = sphere_det(dot(ray_o.dir, ray_o.dir), b, s_to_r);
	if (d < 0)
		return (0);
	if (equal(d, 0.0))
		num = 1;
	else
		num = 2;
	res[0].shape = sphere;
	res[0].t = ((b * -1.0) - sqrt(d)) / (2.0 * dot(ray_o.dir, ray_o.dir));
	if (num == 2)
	{
		res[1].shape = sphere;
		res[1].t = ((b * -1.0) + sqrt(d)) / (2.0 * dot(ray_o.dir, ray_o.dir));
	}
	return (num);
}
