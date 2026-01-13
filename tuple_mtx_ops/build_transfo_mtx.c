/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_transfo_mtx.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:45:53 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/13 14:59:51 by mkeerewe         ###   ########.fr       */
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

static void	free_cyl_mtx(t_cyl_mtx *vars)
{
	free(vars->translate.data);
	free(vars->scale.data);
	free(vars->scale1.data);
	free(vars->rotate1.data);
	free(vars->rotate2.data);
	free(vars->rotate.data);
}

// apply translation of -h/2 on y before scale rotate translate
// to account for centered around orign.
static t_mat	cyl_mtx(t_shape obj)
{
	t_cyl_mtx	vars;

	vars.radius = obj.obj.cyl.radius;
	vars.height = obj.obj.cyl.height;
	vars.scale = scale_mtx(vars.radius, vars.height, vars.radius);
	if (!vars.scale.data)
		return (vars.scale);
	vars.translate = translate_mtx(obj.obj.cyl.centre);
	if (!vars.translate.data)
		return (free(vars.scale.data), vars.translate);
	vars.rotate1 = rotation_mtx(vector(0.0, 1.0, 0.0));
	if (!vars.rotate1.data)
		return (free(vars.scale.data), free(vars.translate.data), vars.rotate1);
	vars.rotate = rotation_mtx(obj.obj.cyl.axis_n);
	if (!vars.rotate.data)
		return (free(vars.scale.data), free(vars.translate.data), free(vars.rotate1.data), vars.rotate);
	vars.rotate2 = mat_mult(vars.rotate, vars.rotate1);
	if (!vars.rotate2.data)
		return (free(vars.scale.data), free(vars.translate.data), free(vars.rotate1.data), vars.rotate2);
	vars.scale1 = mat_mult(vars.rotate2, vars.scale);
	if (!vars.scale1.data)
		return (free(vars.scale.data), free(vars.rotate.data), free(vars.translate.data), free(vars.rotate1.data), free(vars.rotate2.data), vars.scale1);
	vars.ret = mat_mult(vars.translate, vars.scale1);
	free_cyl_mtx(&vars);
	return (vars.ret);
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