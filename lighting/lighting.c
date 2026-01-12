/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:03:15 by mkeerewe          #+#    #+#             */
/*   Updated: 2026/01/12 10:47:24 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_tuple	surface_n_shere(t_shape *sphere, t_tuple pt)
{
	t_tuple	obj_pt;
	t_tuple	obj_normal;
	t_tuple	w_normal;

	obj_pt = mat_tuple_mult(sphere->from_world, pt);
	obj_normal = substr_tuples(obj_pt, point(0, 0, 0));
	w_normal = mat_tuple_mult(transpose(sphere->from_world), obj_normal);
	w_normal.pt = 0;
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
	t_tuple	obj_pt;
	t_tuple	obj_normal;
	t_tuple	w_normal;

	obj_pt = mat_tuple_mult(cyl->from_world, pt);
	obj_normal = vector(pt.x, 0, pt.y);
	w_normal = mat_tuple_mult(cyl->to_world, obj_normal);
	return (vec_normalise(w_normal));
}

t_tuple	reflect(t_tuple in, t_tuple normal_n)
{
	t_tuple	temp;

	temp = mult_vec_scalar(mult_vec_scalar(normal_n, 2), dot_product(in, normal_n));
	return (substr_tuples(in, temp));
}

t_color	set_ambient(t_world *w, t_shape *shape)
{
	t_color color;

	color.r = w->ambient.ratio * w->ambient.color.r * shape->mat.color.r;
	color.g = w->ambient.ratio * w->ambient.color.g * shape->mat.color.g;
	color.b = w->ambient.ratio * w->ambient.color.b * shape->mat.color.b;
	return (color);
}

// add light color to diffuse formula ??
void	set_diffuse(t_shape *shape, t_light light, double light_dot_normal, t_color *color)
{
	if (!(light_dot_normal < 0.0))
	{
		color->r += shape->mat.diffuse * shape->mat.color.r * light_dot_normal * light.color.r;
		color->g += shape->mat.diffuse * shape->mat.color.g * light_dot_normal * light.color.g;
		color->b += shape->mat.diffuse * shape->mat.color.b * light_dot_normal * light.color.b;
	}
}

void	set_specular(t_light light, t_shape *shape, double reflect_dot_cam, t_color *color)
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

int	is_in_shadow(t_world *w, t_tuple pt, t_light light)
{
	t_ray			shadow_ray;
	t_intersection	hit;

	shadow_ray.origin = pt;
	shadow_ray.dir = vec_normalise(substr_tuples(light.point, pt));
	if (intersections(shadow_ray, *w, &hit) == -1)
	{
		free_world(w);
		exit(1);
	}
	if (hit.shape == NULL)
		return (0);
	return (1);
}

t_color	lighting(t_world *w, t_shape *shape, t_tuple cam_v, t_tuple pt)
{
	int		i;
	t_color	color;
	t_tuple	surface_n;
	t_tuple	light_v;
	double	light_dot_normal;
	t_tuple	reflect_v;
	double	reflect_dot_cam;

 	i = 0;
	if (shape->type == SPHERE)
		surface_n = surface_n_shere(shape, pt);
	else // handle surface normal calculation for other shapes
		surface_n = surface_n_plane(shape);
	if (dot_product(surface_n, cam_v) < 0.0)
		surface_n = neg_tuples(surface_n);
	color = set_ambient(w, shape);
	while (i < w->num_lights)
	{
		if (!is_in_shadow(w, add_tuples(pt, mult_vec_scalar(surface_n, EPSILON)), w->lights[i]))
		{
			light_v = vec_normalise(substr_tuples(w->lights[i].point, pt));
			light_dot_normal = dot_product(light_v, surface_n);
			if (!(light_dot_normal < 0))
			{
				set_diffuse(shape, w->lights[i], light_dot_normal, &color);
				reflect_v = reflect(neg_tuples(light_v), surface_n);
				reflect_dot_cam = dot_product(reflect_v, cam_v);
				set_specular(w->lights[i], shape, reflect_dot_cam, &color);
			}
		}
		i++;
	}
	return (color);
}
