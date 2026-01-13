/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:19:21 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/13 19:18:39 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	add_camera(char **args, t_world *w)
{
	if (w->cam.fov != -1 || num_args(args) != 4)
		return (print_error(3), -1);
	if (get_tuple(args[1], &(w->cam.viewpoint), 1) == -1)
		return (print_error(3), -1);
	if (get_tuple(args[2], &(w->cam.normal_n), 0) == -1
		|| is_zero(w->cam.normal_n))
		return (print_error(3), -1);
	w->cam.normal_n = vec_normalise(w->cam.normal_n);
	w->cam.fov = ft_atoi(args[3]);
	if (check_int_conversion(args[3], w->cam.fov) == -1
		|| w->cam.fov > 180 || w->cam.fov < 0)
		return (print_error(3), -1);
	w->cam.to_world.data = NULL;
	w->cam.from_world.data = NULL;
	return (0);
}

int	add_light(char **args, t_world *w)
{
	if (num_args(args) != 4)
		return (print_error(4), -1);
	w->num_lights++;
	w->lights = light_realloc(w->lights, w->num_lights);
	if (w->lights == NULL)
		return (print_error(4), -1);
	if (get_tuple(args[1], &(w->lights[w->num_lights - 1].point), 1) == -1)
		return (print_error(4), -1);
	if (ft_atod(args[2], &(w->lights[w->num_lights - 1].bright)) == -1
		|| w->lights[w->num_lights - 1].bright < 0.0
		|| w->lights[w->num_lights - 1].bright > 1.0)
		return (print_error(4), -1);
	if (get_color(args[3], &(w->lights[w->num_lights - 1].color)) == -1)
		return (print_error(4), -1);
	w->lights[w->num_lights - 1].color.r *= w->lights[w->num_lights - 1].bright;
	w->lights[w->num_lights - 1].color.g *= w->lights[w->num_lights - 1].bright;
	w->lights[w->num_lights - 1].color.b *= w->lights[w->num_lights - 1].bright;
	return (0);
}

int	add_sphere(char **args, t_world *w)
{
	if (num_args(args) != 4)
		return (print_error(5), -1);
	if (init_shape(w) == -1)
		return (-1);
	w->shapes[w->num_shapes - 1].type = SPHERE;
	if (get_tuple(args[1],
			&(w->shapes[w->num_shapes - 1].obj.sphere.centre), 1) == -1)
		return (print_error(5), -1);
	if (ft_atod(args[2],
			&(w->shapes[w->num_shapes - 1].obj.sphere.radius)) == -1
		|| w->shapes[w->num_shapes - 1].obj.sphere.radius < 0.0)
		return (print_error(5), -1);
	w->shapes[w->num_shapes - 1].obj.sphere.radius /= 2.0;
	if (get_color(args[3], &(w->shapes[w->num_shapes - 1].mat.color)) == -1)
		return (print_error(5), -1);
	return (0);
}

int	add_plane(char **args, t_world *w)
{
	if (num_args(args) != 4)
		return (print_error(6), -1);
	if (init_shape(w) == -1)
		return (-1);
	w->shapes[w->num_shapes - 1].type = PLANE;
	if (get_tuple(args[1],
			&(w->shapes[w->num_shapes - 1].obj.plane.point), 1) == -1)
		return (print_error(6), -1);
	if (get_tuple(args[2],
			&(w->shapes[w->num_shapes - 1].obj.plane.normal_n), 0) == -1
		|| is_zero(w->shapes[w->num_shapes - 1].obj.plane.normal_n))
		return (print_error(6), -1);
	w->shapes[w->num_shapes - 1].obj.plane.normal_n
		= vec_normalise(w->shapes[w->num_shapes - 1].obj.plane.normal_n);
	if (get_color(args[3], &(w->shapes[w->num_shapes - 1].mat.color)) == -1)
		return (print_error(6), -1);
	return (0);
}

int	add_cylinder(char **av, t_world *w)
{
	if (num_args(av) != 6)
		return (print_error(7), -1);
	if (init_shape(w) == -1)
		return (-1);
	w->shapes[w->num_shapes - 1].type = CYLINDER;
	if (get_tuple(av[1],
			&(w->shapes[w->num_shapes - 1].obj.cyl.centre), 1) == -1)
		return (print_error(7), -1);
	if (get_tuple(av[2],
			&(w->shapes[w->num_shapes - 1].obj.cyl.axis_n), 0) == -1
		|| is_zero(w->shapes[w->num_shapes - 1].obj.cyl.axis_n))
		return (print_error(7), -1);
	w->shapes[w->num_shapes - 1].obj.cyl.axis_n
		= vec_normalise(w->shapes[w->num_shapes - 1].obj.cyl.axis_n);
	if (ft_atod(av[3], &(w->shapes[w->num_shapes - 1].obj.cyl.radius)) == -1
		|| w->shapes[w->num_shapes - 1].obj.cyl.radius < 0.0)
		return (print_error(7), -1);
	w->shapes[w->num_shapes - 1].obj.cyl.radius /= 2.0;
	if (ft_atod(av[4], &(w->shapes[w->num_shapes - 1].obj.cyl.height)) == -1
		|| w->shapes[w->num_shapes - 1].obj.cyl.height < 0.0)
		return (print_error(7), -1);
	if (get_color(av[5], &(w->shapes[w->num_shapes - 1].mat.color)) == -1)
		return (print_error(7), -1);
	return (0);
}
