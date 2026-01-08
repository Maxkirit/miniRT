/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:25:06 by mkeerewe          #+#    #+#             */
/*   Updated: 2026/01/08 16:49:30 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	print_error(int	mode)
{
	if (mode == 0)
		printf("Error\nWrong file type\n");
	else if (mode == 1)
		printf("Error\nUnknown identifier\n");
	else if (mode == 2)
		printf("Error\nIssue with ambient lighting configurations\n");
	else if (mode == 3)
		printf("Error\nIssue with camera configurations\n");
	else if (mode == 4)
		printf("Error\nIssue with light configurations\n");
	else if (mode == 5)
		printf("Error\nIssue with sphere configurations\n");
	else if (mode == 6)
		printf("Error\nIssue with plane configurations\n");
	else if (mode == 7)
		printf("Error\nIssue with cylinder configurations\n");
	else if (mode == 8)
		printf("Malloc failed\n");
}

int	num_args(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
		i++;
	return (i);
}

int	ft_atod(char *str, double *doub)
{
	char	**parts;
	double	dec;

	parts = ft_split(str, '.');
	if (parts == NULL || num_args(parts) > 2)
		return (-1);
	*doub = (double) ft_atoi(parts[0]);
	if (check_int_conversion(parts[0], (int) *doub) != 0)
		return (-1);
	if (num_args(parts) == 2)
	{
		dec = ((double) ft_atoi(parts[1]));
		if (check_int_conversion(parts[1], (int) dec) != 0)
			return (-1);
		*doub += dec / pow(10.0, (double) ft_strlen(parts[1]));
	}
	return (0);
}

int	get_color(char *str, t_color *color)
{
	char	**parts;

	parts = ft_split(str, ',');
	if (parts == NULL || num_args(parts) != 3)
		return (-1);
	color->r = ft_atoi(parts[0]);
	if (check_int_conversion(parts[0], (int) color->r) != 0 ||
		color->r > 255 || color->r < 0)
		return (-1);
	color->r = color->r / 255;
	color->g = ft_atoi(parts[1]);
	if (check_int_conversion(parts[1], (int) color->g) != 0 ||
		color->g > 255 || color->g < 0)
		return (-1);
	color->g = color->g / 255;
	color->b = ft_atoi(parts[2]);
	if (check_int_conversion(parts[2], (int) color->b) != 0 ||
		color->b > 255 || color->b < 0)
		return (-1);
	color->b = color->b / 255;
	return (0);
}

int	get_tuple(char *str, t_tuple *tup, int pt)
{
	char	**parts;

	parts = ft_split(str, ',');
	if (parts == NULL || num_args(parts) != 3)
		return (-1);
	if (ft_atod(parts[0], &(tup->x)) == -1)
		return (-1);
	if (ft_atod(parts[1], &(tup->y)) == -1)
		return (-1);
	if (ft_atod(parts[2], &(tup->z)) == -1)
		return (-1);
	tup->pt = (double) pt;
	return (0);
}

int	is_normal(t_tuple tup)
{
	if (tup.x > 1.0 || tup.x < -1.0)
		return (-1);
	else if (tup.y > 1.0 || tup.y < -1.0)
		return (-1);
	else if (tup.z > 1.0 || tup.z < -1.0)
		return (-1);
	if (vec_magnitude(tup) != 1)
		return (-1);
	return (0);
}

int	init_shape(t_world *w)
{
	w->num_shapes++;
	w->shapes = shape_realloc(w->shapes, w->num_shapes);
	if (w->shapes == NULL && w->num_shapes != 1)
		return (print_error(8), -1);
	w->shapes[w->num_shapes - 1].mat.diffuse = 0.9;
	w->shapes[w->num_shapes - 1].mat.specular = 0.9;
	w->shapes[w->num_shapes - 1].mat.shine = 200.0;
	w->shapes[w->num_shapes - 1].to_world.data = NULL;
	w->shapes[w->num_shapes - 1].from_world.data = NULL;
	return (0);
}

int	add_ambient(char **args, t_world *w)
{
	if (w->ambient.ratio != -1 || num_args(args) != 3)
		return (print_error(2), -1);
	if (ft_atod(args[1], &(w->ambient.ratio)) == -1)
		return (print_error(2), -1);
	if (w->ambient.ratio > 1.0 || w->ambient.ratio < 0.0)
		return (print_error(2), -1);
	if (get_color(args[2], &(w->ambient.color)) == -1)
		return (print_error(2), -1);
	return (0);
}

int	add_camera(char **args, t_world *w)
{
	if (w->cam.fov != -1 || num_args(args) != 4)
		return (print_error(3), -1);
	if (get_tuple(args[1], &(w->cam.viewpoint), 1) == -1)
		return (print_error(3), -1);
	if (get_tuple(args[2], &(w->cam.normal_n), 0) == -1 || is_normal(w->cam.normal_n) == -1)
		return (print_error(3), -1);
	w->cam.fov = ft_atoi(args[3]);
	if (check_int_conversion(args[3], w->cam.fov) == -1 || w->cam.fov > 180 || w->cam.fov < 0)
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
	if (w->shapes == NULL && w->num_lights != 1)
		return (print_error(4), -1);
	if (get_tuple(args[1], &(w->lights[w->num_lights - 1].point), 1) == -1)
		return (print_error(4), -1);
	if (ft_atod(args[2], &(w->lights[w->num_lights - 1].bright)) == -1 ||
		w->lights[w->num_lights - 1].bright < 0.0 || w->lights[w->num_lights - 1].bright > 1.0)
		return (print_error(4), -1);
	if (get_color(args[3], &(w->lights[w->num_lights - 1].color)) == -1)
		return (print_error(4), -1);
	return (0);
}

int	add_sphere(char **args, t_world *w)
{
	if (num_args(args) != 4)
		return (print_error(5), -1);
	if (init_shape(w) == -1)
		return (-1);
	w->shapes[w->num_shapes - 1].type = SPHERE;
	if (get_tuple(args[1], &(w->shapes[w->num_shapes - 1].obj.sphere.centre), 1) == -1)
		return (print_error(5), -1);
	if (ft_atod(args[2], &(w->shapes[w->num_shapes - 1].obj.sphere.radius)) == -1 || w->shapes[w->num_shapes - 1].obj.sphere.radius < 0.0)
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
	if (get_tuple(args[1], &(w->shapes[w->num_shapes - 1].obj.plane.point), 1) == -1)
		return (print_error(6), -1);
	if (get_tuple(args[2], &(w->shapes[w->num_shapes - 1].obj.plane.normal_n), 0) == -1 || is_normal(w->shapes[w->num_shapes - 1].obj.plane.normal_n) == -1)
		return (print_error(6), -1);
	if (get_color(args[3], &(w->shapes[w->num_shapes - 1].mat.color)) == -1)
		return (print_error(6), -1);
	return (0);
}

int	add_cylinder(char **args, t_world *w)
{
	if (num_args(args) != 6)
		return (print_error(7), -1);
	if (init_shape(w) == -1)
		return (-1);
	if (get_tuple(args[1], &(w->shapes[w->num_shapes - 1].obj.cyl.centre), 1) == -1)
		return (print_error(7), -1);
	if (get_tuple(args[2], &(w->shapes[w->num_shapes - 1].obj.cyl.axis_n), 0) == -1 ||
		is_normal(w->shapes[w->num_shapes - 1].obj.cyl.axis_n) == -1)
		return (print_error(7), -1);
	if (ft_atod(args[3], &(w->shapes[w->num_shapes - 1].obj.cyl.radius)) == -1 ||
		w->shapes[w->num_shapes - 1].obj.cyl.radius < 0.0)
		return (print_error(7), -1);
	w->shapes[w->num_shapes - 1].obj.cyl.radius /= 2;
	if (ft_atod(args[4], &(w->shapes[w->num_shapes - 1].obj.cyl.height)) == -1 ||
		w->shapes[w->num_shapes - 1].obj.cyl.height < 0.0)
		return (print_error(7), -1);
	if (get_color(args[5], &(w->shapes[w->num_shapes - 1].mat.color)) == -1)
		return (print_error(7), -1);
	return (0);
}

int	process_args(char **args, t_world *w)
{
	if (ft_strcmp(args[0], "A") == 0)
		return (add_ambient(args, w));
	else if (ft_strcmp(args[0], "C") == 0)
		return (add_camera(args, w));
	else if (ft_strcmp(args[0], "L") == 0)
		return (add_light(args, w));
	else if (ft_strcmp(args[0], "sp") == 0)
		return (add_sphere(args, w));
	else if (ft_strcmp(args[0], "pl") == 0)
		return (add_plane(args, w));
	else if (ft_strcmp(args[0], "cy") == 0)
		return (add_cylinder(args, w));
	else
		return (print_error(1), -1);
}

int	check_file_type(char *file)
{
	char	**parts;

	parts = ft_split(file, '.');
	if (parts == NULL)
		return (print_error(0), -1);
	if (num_args(parts) != 2)
		return (print_error(0), free_args(parts), -1);
	if (ft_strcmp(parts[1], "rt") != 0)
		return (free_args(parts), print_error(0), -1);
	return (0);
}

int	parse_file(char *file, t_world *world)
{
	int		fd;
	char	*line;
	char	**args;

	if (check_file_type(file) == -1)
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strlen(line) != 0 && line[0] != '\n')
		{
			if (line[ft_strlen(line) - 1] == '\n')
				line[ft_strlen(line) - 1] = '\0';
			args = ft_split(line, ' ');
			if (args == NULL)
				return (free(line), -1);
			if (process_args(args, world) == -1)
				return (free_args(args), free(line), -1);
			free_args(args);
		}
		free(line);
	}
	if (world->cam.fov == -1)
		return (print_error(3), -1);
	return (0);
}

// int	main(int argc, char *argv[])
// {
// 	t_world	world;

// 	if (argc != 2)
// 		return (1);
// 	world.num_lights = 0;
// 	world.num_shapes = 0;
// 	world.lights = NULL;
// 	world.shapes = NULL;
// 	world.ambient.ratio = -1;
// 	world.cam.fov = -1;
// 	parse_file(argv[1], &world);
// 	return (0);
// }
