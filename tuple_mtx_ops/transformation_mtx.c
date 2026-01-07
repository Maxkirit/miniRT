/* ************************************************************************** */
/*	                                                                         */
/*                                                        :::      ::::::::   */
/*   transformation_mtx.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 12:42:41 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/07 13:59:24 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
Set of functions that create transformation matrices.
They go from object or camera space to world space,
i.e. the objects/camera are created w/ their centers at (0,0,0)
then the transformation places them at the correct spot and rotation.
We are using a left handed coordinate system with z going through the screen
opposite to the user.
*/

// Scales to right size. For sphere, x=y=z=R.
// For cylinder, x=z=R and y=H/2
// if (!res.data)--> malloc error
t_mat	scale_mtx(double x, double y, double z)
{
	t_mat	res;

	res = new_matrix(4, 4);
	if (!res.data)
		return (res);
	set_data(res, 0, 0, x);
	set_data(res, 1, 1, y);
	set_data(res, 2, 2, z);
	set_data(res, 3, 3, 1);
	return (res);
}

// dest must be a point
// if (!res.data)--> malloc error
t_mat	translate_mtx(t_tuple dest)
{
	t_mat	res;

	res = identity();
	if (!res.data)
		return (res);
	set_data(res, 0, 3, dest.x);
	set_data(res, 1, 3, dest.y);
	set_data(res, 2, 3, dest.z);
	return (res);
}

static t_mat	build_rot_mtx(t_tuple x, t_tuple y, t_tuple z)
{
	t_mat	res;

	res = new_matrix(4, 4);
	if (!res.data)
		return (res);
	set_data(res, 0, 0, x.x);
	set_data(res, 0, 1, y.x);
	set_data(res, 0, 2, z.x);
	set_data(res, 1, 0, x.y);
	set_data(res, 1, 1, y.y);
	set_data(res, 1, 2, z.y);
	set_data(res, 2, 0, x.z);
	set_data(res, 2, 1, y.z);
	set_data(res, 2, 2, z.z);
	set_data(res, 3, 3, 1.0);
	return (res);
}

// dest_axis is the direction of the new up.
// base up is (0, 1, 0): cylinder axis or normal vect to plane
// a = (0, 0, 1) is another vector to compute first axis of new base
// we are building a new orthonormal base for the rotation matrix
// if (!res.data)--> malloc error
t_mat	rotation_mtx(t_tuple dest_axis)
{
	t_tuple	y_new;
	t_tuple	x_new;
	t_tuple	z_new;
	t_tuple	a;

	y_new = dest_axis;
    if (equal(dest_axis.z, 1.0) || equal(dest_axis.z, -1.0))
        a = vector(1.0, 0.0, 0.0);
    else
	    a = vector(0.0, 0.0, 1.0);
	x_new = cross_product(a, y_new);
	x_new = mult_vec_scalar(x_new, 1 / vec_magnitude(x_new));
	z_new = cross_product(y_new, x_new);
	return (build_rot_mtx(x_new, y_new, z_new));
}
