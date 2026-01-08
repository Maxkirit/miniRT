/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:16:42 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/08 16:17:35 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static t_intersect	no_solution(t_intersect res)
{
	res.size = 0;
	res.table = NULL;
	return (res);
}

//discrimant == 0 when 1 solution so we can compress code like that
t_intersect	intersect_sphere(t_shape sphere, t_ray ray)
{
	t_ray		ray_obj;
	t_intersect	res;
	double		v_norm;
	double		v_dot_o;
	double		discriminant;

	ray_obj.dir = mat_tuple_mult(sphere.from_world, ray.dir);
	ray_obj.origin = mat_tuple_mult(sphere.from_world, ray.origin);
	v_norm = vec_magnitude(ray_obj.dir);
	v_dot_o = dot_product(ray_obj.dir, ray_obj.origin);
	discriminant = 4.0 * square(v_dot_o) - 4.0 * square(v_norm)
			* (square(vec_magnitude(ray_obj.origin)) - 1.0);
	if (discriminant < 0)
		return (no_solution(res));
	if (equal(discriminant, 0.0))
		res.size = 1;
	else
		res.size = 2;
	res.table = (double *)malloc(res.size * sizeof(double));
	if (!res.table)
		return (res);
	res.table[0] = (-1 * 2.0 * v_dot_o - sqrt(discriminant)) / (2 * square(v_norm));
	if (res.size == 2)
		res.table[1] = (-1 * 2.0 * v_dot_o + sqrt(discriminant)) / (2 * square(v_norm));
	return (res);
}

static int	find_min_t(double *res, int size, double *hit)
{
	int	i;
	int	lowest_pos;

	i = 0;
	lowest_pos = 0;
	while (i < size)
	{
		if (res[i] > 0.0 && res[i] < res[lowest_pos])
			lowest_pos = i;
		i++;
	}
	*hit = res[lowest_pos];
	return (1);
}

// Iterates over all objects of the world to check intersections
// *hit is result t passed by reference
// Returns -1 on error, 1 on success
int	intersections(t_ray ray, t_world world, double *hit)
{
	t_intersect solutions;
	t_ray		ray_world;
	double      *res;
	int         i;
	int			size;
	//create an array of t.
	//transform ray from camera to world and from world to object
	//for each shape, call intersect_shape which return int array with between 0 and n solutions
	//realloc t array and add results
	//find smallest positive t in array
	size = 0;
	ray_world.dir = mat_tuple_mult(world.cam.to_world, ray.dir);
	ray_world.origin = mat_tuple_mult(world.cam.to_world, ray.origin);
	i = 0;
	while (i < world.num_shapes)
	{
		if (world.shapes[i].type == SPHERE)
			solutions = intersect_sphere(world.shapes[i], ray_world);
		// if (world.shapes[i].type == PLANE)
		// 	solutions = intersect_plane(world.shapes[i], ray_world);
		// if (world.shapes[i].type == CYLINDER)
		// 	solutions = intersect_cyl(world.shapes[i], ray_world);
		if (!solutions.table && solutions.size != 0)
			return (-1);
		if (solutions.size > 0)
		{
			res = res_realloc(res, size, solutions);
			if (!res)
				return (-1);
		}
		size += solutions.size;
		i++;
	}
	return (find_min_t(res, size, hit));
}
