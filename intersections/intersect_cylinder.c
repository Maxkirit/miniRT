/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:37:14 by mkeerewe          #+#    #+#             */
/*   Updated: 2026/01/13 17:37:20 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	handle_cyl_height(t_ray ray, t_intersection res[2])
{
	double	y;
	int		i;
	int		ret;

	i = 0;
	ret = 2;
	y = ray.origin.y + res[i].t * ray.dir.y;
	i++;
	if (y < -0.5 || y > 0.5)
	{
		res[0].t = res[1].t;
		i--;
		ret--;
	}
	y = ray.origin.y + res[i].t * ray.dir.y;
	if (y < -0.5 || y > 0.5)
	{
		if (i == 0)
			return (0);
		ret--;
	}
	return (ret);
}

int	check_cap(t_ray ray, double t)
{
	double	x;
	double	z;

	x = ray.origin.x + t * ray.dir.x;
	z = ray.origin.z + t * ray.dir.z;
	return ((pow(x, 2.0) + pow(z, 2.0)) < (1.0 + EPSILON));
}

int	intersect_caps(t_shape *cyl, t_ray ray, t_intersection res[2])
{
	int		i;
	double	t;

	i = 0;
	ray.dir = mat_tuple_mult(cyl->from_world, ray.dir);
	ray.origin = mat_tuple_mult(cyl->from_world, ray.origin);
	res[0].shape = NULL;
	if (equal(ray.dir.y, 0.0))
		return (0);
	t = (0.5 - ray.origin.y) / ray.dir.y;
	if (check_cap(ray, t))
	{
		res[i].shape = cyl;
		res[i].t = t;
		i++;
	}
	t = (-0.5 - ray.origin.y) / ray.dir.y;
	if (check_cap(ray, t))
	{
		res[i].shape = cyl;
		res[i].t = t;
		i++;
	}
	return (i);
}

// in object space, cyl is vertical along y axis
// radius == 1, height == 1
int	intersect_cyl(t_shape *cyl, t_ray ray, t_intersection res[2])
{
	double	a;
	double	b;
	double	c;
	double	discriminant;

	ray.dir = mat_tuple_mult(cyl->from_world, ray.dir);
	ray.origin = mat_tuple_mult(cyl->from_world, ray.origin);
	a = pow(ray.dir.x, 2.0) + pow(ray.dir.z, 2.0);
	if (equal(a, 0.0))
		return (0);
	b = 2.0 * ray.origin.x * ray.dir.x + 2.0 * ray.origin.z * ray.dir.z;
	c = pow(ray.origin.x, 2.0) + pow(ray.origin.z, 2.0) - 1.0;
	discriminant = pow(b, 2.0) - 4 * a * c;
	if (discriminant < 0.0)
		return (0);
	res[0].shape = cyl;
	res[0].t = (double)((b * -1.0) - sqrt(discriminant)) / (2.0 * a);
	res[1].shape = cyl;
	res[1].t = (double)((b * -1.0) + sqrt(discriminant)) / (2.0 * a);
	return (handle_cyl_height(ray, res));
}
