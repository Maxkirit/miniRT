/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:16:42 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/13 16:32:56 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//discrimant == 0 when 1 solution so we can compress code like that
int	intersect_sphere(t_shape *sphere, t_ray ray, t_intersection res[2])
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
	res[0].shape = sphere;
	res[0].t = (double) ((b * -1.0) - sqrt(discriminant)) / (2.0 * a);
	if (num == 2)
	{
		res[1].shape = sphere;
		res[1].t = (double) ((b * -1.0) + sqrt(discriminant)) / (2.0 * a);
	}
	return (num);
}

int	intersect_plane(t_shape *plane, t_ray ray, t_intersection res[2])
{
	ray.dir = mat_tuple_mult(plane->from_world, ray.dir);
	ray.origin = mat_tuple_mult(plane->from_world, ray.origin);
	if (fabs(ray.dir.z) < EPSILON)
		return (0);
	res[0].shape = plane;
	res[0].t = (ray.origin.z * -1.0) / ray.dir.z;
	return (1);
}

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
	if (discriminant < 0.0) // check if only one t is possible
		return (0);
	res[0].shape = cyl;
	res[0].t = (double) ((b * -1.0) - sqrt(discriminant)) / (2.0 * a);
	res[1].shape = cyl;
	res[1].t = (double) ((b * -1.0) + sqrt(discriminant)) / (2.0 * a);
	return (handle_cyl_height(ray, res));
}

void	is_hit(t_intersection solutions[2], int sol_size, t_intersection *hit)
{
	int	i;

	i = 0;
	while (i < sol_size)
	{
		if (solutions[i].t > 0.0 && (hit->shape == NULL || solutions[i].t < hit->t))
		{
			hit->shape = solutions[i].shape;
			hit->t = solutions[i].t;
		}
		i++;
	}
}

// Iterates over all objects of the world to check intersections
// *hit is result t passed by reference
// Returns -1 on error, 1 on success
void	intersections(t_ray ray, t_world world, t_intersection *hit)
{
	t_intersection	solutions[2];
	int				sol_size;
	int				i;

	//for each shape, call intersect_shape which return int array with between 0 and n solutions
	//realloc t array and add results
	//find smallest positive t in array
	i = 0;
	sol_size = 0;
	while (i < world.num_shapes)
	{
		if (world.shapes[i].type == SPHERE)
			sol_size = intersect_sphere(&(world.shapes[i]), ray, solutions);
		else if (world.shapes[i].type == PLANE)
			sol_size = intersect_plane(&(world.shapes[i]), ray, solutions);
		else if (world.shapes[i].type == CYLINDER)
		{
			sol_size = intersect_cyl(&(world.shapes[i]), ray, solutions);
			is_hit(solutions, sol_size, hit);
			sol_size = intersect_caps(&(world.shapes[i]), ray, solutions);
		}
		is_hit(solutions, sol_size, hit);
		i++;
	}
}
