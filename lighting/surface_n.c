/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_n.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:02:14 by mkeerewe          #+#    #+#             */
/*   Updated: 2026/01/13 18:09:01 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_tuple	surface_n_shere(t_shape *sphere, t_tuple pt)
{
	t_tuple	obj_pt;
	t_tuple	obj_normal;
	t_mat	transp;
	t_tuple	w_normal;

	obj_pt = mat_tuple_mult(sphere->from_world, pt);
	obj_normal = substr_tuples(obj_pt, point(0, 0, 0));
	transp = transpose(sphere->from_world);
	w_normal = mat_tuple_mult(transp, obj_normal);
	w_normal.pt = 0;
	free(transp.data);
	return (vec_normalise(w_normal));
}

t_tuple	surface_n_plane(t_shape *plane)
{
	t_tuple	world_n;

	world_n = mat_tuple_mult(plane->to_world, vector(0, 0, 1));
	return (vec_normalise(world_n));
}

t_tuple	surface_n_cylinder(t_shape *cyl, t_tuple pt)
{
	double	dist;
	t_tuple	obj_pt;
	t_tuple	obj_normal;
	t_mat	transp;
	t_tuple	w_normal;

	obj_pt = mat_tuple_mult(cyl->from_world, pt);
	dist = pow(obj_pt.x, 2.0) + pow(obj_pt.z, 2.0);
	if (dist < 1 && obj_pt.y >= (0.5 - EPSILON))
		obj_normal = vector(0, 1, 0);
	else if (dist < 1 && obj_pt.y <= (-0.5 + EPSILON))
		obj_normal = vector(0, -1, 0);
	else
		obj_normal = vector(obj_pt.x, 0, obj_pt.z);
	transp = transpose(cyl->from_world);
	w_normal = mat_tuple_mult(transp, obj_normal);
	w_normal.pt = 0;
	free(transp.data);
	return (vec_normalise(w_normal));
}

t_tuple	set_surface_n(t_shape *shape, t_tuple cam_v, t_tuple pt)
{
	t_tuple	surface_n;

	if (shape->type == SPHERE)
		surface_n = surface_n_shere(shape, pt);
	else if (shape->type == PLANE)
		surface_n = surface_n_plane(shape);
	else
		surface_n = surface_n_cylinder(shape, pt);
	if (dot_product(surface_n, cam_v) < 0.0)
		surface_n = neg_tuples(surface_n);
	return (surface_n);
}
