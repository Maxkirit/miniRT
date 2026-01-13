/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:16:42 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/13 17:37:28 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	is_hit(t_intersection solutions[2], int sol_size, t_intersection *hit)
{
	int	i;

	i = 0;
	while (i < sol_size)
	{
		if (solutions[i].t > 0.0 && (hit->shape == NULL
				|| solutions[i].t < hit->t))
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
