/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:57:04 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/13 19:20:11 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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

void	print_error(int mode)
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

int	is_zero(t_tuple tup)
{
	if (equal(tup.x, 0.0) && equal(tup.y, 0.0) && equal(tup.z, 0.0))
		return (1);
	return (0);
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
	return (free_args(parts), 0);
}
