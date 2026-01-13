/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:03:15 by mkeerewe          #+#    #+#             */
/*   Updated: 2026/01/13 19:23:38 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_color	set_ambient(t_world *w, t_shape *shape)
{
	t_color	color;

	color.r = w->ambient.ratio * w->ambient.color.r * shape->mat.color.r;
	color.g = w->ambient.ratio * w->ambient.color.g * shape->mat.color.g;
	color.b = w->ambient.ratio * w->ambient.color.b * shape->mat.color.b;
	return (color);
}

void	set_diffuse(t_shape *shape, t_light light, double light_dot_normal,
			t_color *color)
{
	if (!(light_dot_normal < 0.0))
	{
		color->r += shape->mat.diffuse * shape->mat.color.r
			* light_dot_normal * light.color.r;
		color->g += shape->mat.diffuse * shape->mat.color.g
			* light_dot_normal * light.color.g;
		color->b += shape->mat.diffuse * shape->mat.color.b
			* light_dot_normal * light.color.b;
	}
}

void	set_specular(t_light light, t_shape *shape, double reflect_dot_cam,
			t_color *color)
{
	double	factor;

	if (reflect_dot_cam > 0)
	{
		factor = pow(reflect_dot_cam, shape->mat.shine);
		color->r += light.color.r * shape->mat.specular * factor;
		color->g += light.color.g * shape->mat.specular * factor;
		color->b += light.color.b * shape->mat.specular * factor;
	}
}

t_color	lighting(t_world *w, t_shape *shape, t_tuple cam_v, t_tuple pt)
{
	int		i;
	t_color	color;
	t_tuple	surface_n;
	t_tuple	light_v;
	double	light_dot_normal;

	i = -1;
	surface_n = set_surface_n(shape, cam_v, pt);
	color = set_ambient(w, shape);
	while (++i < w->num_lights)
	{
		if (!is_in_shadow(w, add_tuples(pt,
					mult_vec_scalar(surface_n, EPSILON)), w->lights[i]))
		{
			light_v = vec_normalise(substr_tuples(w->lights[i].point, pt));
			light_dot_normal = dot_product(light_v, surface_n);
			if (!(light_dot_normal < 0))
			{
				set_diffuse(shape, w->lights[i], light_dot_normal, &color);
				set_specular(w->lights[i], shape,
					ref_dot_cam(light_v, surface_n, cam_v), &color);
			}
		}
	}
	return (color);
}
