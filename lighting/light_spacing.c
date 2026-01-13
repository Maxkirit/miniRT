/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_spacing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:45:50 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/13 11:40:48 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	is_in_sphere(t_tuple light, t_shape sphere)
{
	t_tuple	new;

	new = mat_tuple_mult(sphere.from_world, light);
	if (equal(pow(new.x, 2.0) + pow(new.y, 2.0) + pow(new.z, 2.0), 1.0))
		return (1);
	return (0);
}

int	is_in_plane(t_tuple light, t_shape plane)
{
	t_tuple	new;

	new = mat_tuple_mult(plane.from_world, light);
	if (equal(new.z, 0.0))
		return (1);
	return (0);
}

int	is_in_cyl(t_tuple light, t_shape cyl)
{
	t_tuple	new;
	double	radius;

	new = mat_tuple_mult(cyl.from_world, light);
	radius = pow(new.x, 2.0) + pow(new.z, 2.0);
	if (equal(radius, 1.0) && (new.y < 0.5 || equal(new.y, 0.5)
			|| new.y > -0.5 || equal(new.y, -0.5)))
		return (1);
	if (radius < 1.0 && (equal(new.y, -0.5) || equal(new.y, 0.5)))
		return (1);
	return (0);
}

//normal is normalised
void	add_epsilon(t_tuple *light, t_tuple normal)
{
	light->x += EPSILON * normal.x;
	light->y += EPSILON * normal.y;
	light->z += EPSILON * normal.z;
	return ;
}

//light can intersect multiple objects but incidence computed on first one
void	check_light_spacing (t_world *w)
{
	int 	i;
	int 	j;
	t_tuple	light;
	
	i = 0;
	j = 0;
	while (i < w->num_lights)
	{
		j = 0;
		light = w->lights[i].point;
		while (j < w->num_shapes)
		{
			if (is_in_sphere(light, w->shapes[j]))
				return (add_epsilon(&w->lights[i].point,
						surface_n_shere(&w->shapes[j], light)));
 			else if (is_in_plane(light, w->shapes[j]))
				return (add_epsilon(&w->lights[i].point,
						surface_n_plane(&w->shapes[j])));
			else if (is_in_cyl(light, w->shapes[j]))
				return (add_epsilon(&w->lights[i].point,
						surface_n_cylinder(&w->shapes[j], light)));
			j++;
		}
		i++;
	}
	return ;
}