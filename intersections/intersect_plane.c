/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:36:23 by mkeerewe          #+#    #+#             */
/*   Updated: 2026/01/13 17:36:41 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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
