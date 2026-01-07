/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_transfo_mtx.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:45:53 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/07 16:46:26 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mat	sphere_mtx(t_shape obj)
{
	t_mat	scale;
	t_mat	translate;
	double	radius;

	radius = obj.obj.sphere.radius;
	scale = scale_mtx(radius, radius, radius);
	if (!scale.data)
		return (scale);
	translate = translate_mtx(obj.obj.sphere.centre);
	if (!translate.data)
		return (translate);
	return (mat_mult(translate, scale));
}

t_mat	plane_mtx(t_shape obj)
{
	t_mat	rotate;
	t_mat	translate;

	rotate = rotation_mtx(obj.obj.plane.normal_n);
	if (!rotate.data)
		return (rotate);
	translate = translate_mtx(obj.obj.plane.point);
	if (!translate.data)
		return (translate);
	return (mat_mult(translate, rotate));
}

t_mat	cyl_mtx(t_shape obj)
{
	t_mat	scale;
	t_mat	translate;
	t_mat	rotate;
	double	radius;
	double	height;

	radius = obj.obj.cyl.radius;
	height = obj.obj.cyl.height;
	scale = scale_mtx(radius, height, radius);
	if (!scale.data)
		return (scale);
	translate = translate_mtx(obj.obj.cyl.centre);
	if (!translate.data)
		return (translate);
	rotate = rotation_mtx(obj.obj.cyl.axis_n);
	if (!rotate.data)
		return (rotate);
	scale = mat_mult(rotate, scale);
	return (mat_mult(translate, scale));
}

//returns the transformation matrix for this object
//if (!res.data)--> malloc error
t_mat	build_transfo(t_shape obj)
{
	if (obj.type == SPHERE)
		return (sphere_mtx(obj));
	if (obj.type == PLANE)
		return (plane_mtx(obj));
	else
		return (cyl_mtx(obj));
}