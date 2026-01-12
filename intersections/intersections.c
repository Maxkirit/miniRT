/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:16:42 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/12 10:39:17 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//discrimant == 0 when 1 solution so we can compress code like that
int	intersect_sphere(t_shape *sphere, t_ray ray, t_intersection **res)
{
	t_ray			ray_obj;
	t_tuple			sphere_to_ray;
	double			a;
	double			b;
	double			c;
	double			discriminant;
	int				num;

	ray_obj.dir = mat_tuple_mult(sphere->from_world, ray.dir);
	ray_obj.origin = mat_tuple_mult(sphere->from_world, ray.origin);
	sphere_to_ray = substr_tuples(ray_obj.origin, point(0, 0, 0));
	a = dot_product(ray_obj.dir, ray_obj.dir);
	b = 2 * dot_product(ray_obj.dir, sphere_to_ray);
	c = dot_product(sphere_to_ray, sphere_to_ray) - 1.0;
	discriminant = pow(b, 2.0) - 4 * a * c;
	if (discriminant < 0)
		return (0);
	if (equal(discriminant, 0.0))
		num = 1;
	else
		num = 2;
	*res = (t_intersection *) malloc(num * sizeof(t_intersection));
	if (!(*res))
		return (-1);
	(*res)[0].shape = sphere;
	(*res)[0].t = (double) ((b * -1) - sqrt(discriminant)) / (2.0 * a);
	if (num == 2)
	{
		(*res)[1].shape = sphere;
		(*res)[1].t = (double) ((b * -1) + sqrt(discriminant)) / (2.0 * a);
	}
	return (num);
}

int	intersect_plane(t_shape *plane, t_ray ray, t_intersection **res)
{
	ray.dir = mat_tuple_mult(plane->from_world, ray.dir);
	ray.origin = mat_tuple_mult(plane->from_world, ray.origin);
	if (fabs(ray.dir.y) < EPSILON)
		return (0);
	*res = (t_intersection *) malloc(1 * sizeof(t_intersection));
	if (!(*res))
		return (-1);
	(*res)[0].shape = plane;
	(*res)[0].t = (ray.origin.z * -1.0) / ray.dir.z;
	return (1);
}

int	intersect_cylinder(t_shape *sphere, t_ray ray, t_intersection **res)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;

	a = pow(ray.dir.x, 2.0) + pow(ray.dir.z, 2.0);
	if (equal(a, 0.0))
		return (0);
	b = 2.0 * ray.origin.x * ray.dir.x + 2 * ray.origin.z * ray.dir.z;
	c = pow(ray.origin.x, 2.0) + pow(ray.origin.z, 2.0) - 1.0;
	discriminant = pow(b, 2.0) - 4 * a * c;
	if (discriminant < 0.0)
		return (0);
	*res = (t_intersection *) malloc(2 * sizeof(t_intersection));
	if (!(*res))
		return (-1);
	(*res)[0].shape = sphere;
	(*res)[0].t = (double) ((b * -1) - sqrt(discriminant)) / (2.0 * a);
	(*res)[1].shape = sphere;
	(*res)[1].t = (double) ((b * -1) + sqrt(discriminant)) / (2.0 * a);
	return (2);
}

static int	find_min_t(t_intersect *res, int size, t_intersection *hit)
{
	int	i;
	int	lowest_t;

	i = 0;
	lowest_t = -1;
	while (i < size)
	{
		if (res->table[i].t > 0.0 && (res->table[i].t < lowest_t || lowest_t == -1))
		{
			lowest_t = res->table[i].t ;
			*hit = res->table[i];
		}
		i++;
	}
	if (lowest_t == -1)
		hit->shape = NULL;
	return (1);
}

// Iterates over all objects of the world to check intersections
// *hit is result t passed by reference
// Returns -1 on error, 1 on success
int	intersections(t_ray ray, t_world world, t_intersection *hit)
{
	t_intersection	*solutions;
	int				sol_size;
	t_intersect 	inter;
	int				i;

	//for each shape, call intersect_shape which return int array with between 0 and n solutions
	//realloc t array and add results
	//find smallest positive t in array
	inter.size = 0;
	inter.table	= NULL;
	i = 0;
	sol_size = 0;
	while (i < world.num_shapes)
	{
		solutions = NULL;
		if (world.shapes[i].type == SPHERE)
			sol_size = intersect_sphere(&(world.shapes[i]), ray, &solutions);
		if (world.shapes[i].type == PLANE)
			sol_size = intersect_plane(&(world.shapes[i]), ray, &solutions);
		// if (world.shapes[i].type == CYLINDER)
		// 	solutions = intersect_cyl(world.shapes[i], ray_world);
		if (sol_size == -1)
			return (-1);
		if (sol_size > 0)
		{
			inter.table = inter_realloc(inter.table, inter.size, solutions, sol_size);
			if (inter.table == NULL)
				return (-1);
			inter.size += sol_size;
			free(solutions);
		}
		i++;
	}
	return (find_min_t(&inter, inter.size, hit));
}
