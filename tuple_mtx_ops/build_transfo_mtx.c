/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_transfo_mtx.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:45:53 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/13 18:15:23 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static t_mat	sphere_mtx(t_shape obj)
{
	t_mat	scale;
	t_mat	translate;
	double	radius;
	t_mat	ret;

	radius = obj.obj.sphere.radius;
	scale = scale_mtx(radius, radius, radius);
	if (!scale.data)
		return (scale);
	translate = translate_mtx(obj.obj.sphere.centre);
	if (!translate.data)
		return (free(scale.data), translate);
	ret = mat_mult(translate, scale);
	free(scale.data);
	free(translate.data);
	return (ret);
}

static t_mat	plane_mtx(t_shape obj)
{
	t_mat	rotate;
	t_mat	translate;
	t_mat	ret;

	rotate = rotation_mtx(obj.obj.plane.normal_n);
	if (!rotate.data)
		return (rotate);
	translate = translate_mtx(obj.obj.plane.point);
	if (!translate.data)
		return (free(rotate.data), translate);
	ret = mat_mult(translate, rotate);
	free(rotate.data);
	free(translate.data);
	return (ret);
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

//inverse direction vector so that the camera vector
//describes the direction the camera looks towards
t_mat	build_transfo_cam(t_cam cam)
{
	t_mat	rotate;
	t_mat	translate;
	t_mat	ret;

	rotate = rotation_mtx(cam.normal_n);
	if (!rotate.data)
		return (rotate);
	translate = translate_mtx(cam.viewpoint);
	if (!translate.data)
		return (free(rotate.data), translate);
	ret = mat_mult(translate, rotate);
	free(rotate.data);
	free(translate.data);
	return (ret);
}
