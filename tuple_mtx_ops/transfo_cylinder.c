/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfo_cylinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:13:09 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/13 18:17:07 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	free_cyl_mtx(t_cyl_mtx *vars)
{
	free(vars->translate.data);
	free(vars->scale.data);
	free(vars->scale1.data);
	free(vars->rotate1.data);
	free(vars->rotate2.data);
	free(vars->rotate.data);
}

static void	free1(t_cyl_mtx *vars)
{
	free(vars->scale.data);
	free(vars->translate.data);
	free(vars->rotate1.data);
}

static void	free2(t_cyl_mtx *vars)
{
	free(vars->scale.data);
	free(vars->rotate.data);
	free(vars->translate.data);
	free(vars->rotate1.data);
	free(vars->rotate2.data);
}

// apply translation of -h/2 on y before scale rotate translate
// to account for centered around orign.
t_mat	cyl_mtx(t_shape obj)
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
		return (free1(&vars), vars.rotate);
	vars.rotate2 = mat_mult(vars.rotate, vars.rotate1);
	if (!vars.rotate2.data)
		return (free1(&vars), vars.rotate2);
	vars.scale1 = mat_mult(vars.rotate2, vars.scale);
	if (!vars.scale1.data)
		return (free2(&vars), vars.scale1);
	vars.ret = mat_mult(vars.translate, vars.scale1);
	free_cyl_mtx(&vars);
	return (vars.ret);
}
