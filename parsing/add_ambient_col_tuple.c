/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_ambient_col_tuple.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:23:21 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/13 19:19:30 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	get_color(char *str, t_color *color)
{
	char	**parts;

	parts = ft_split(str, ',');
	if (parts == NULL || num_args(parts) != 3)
		return (free_args(parts), -1);
	color->r = ft_atoi(parts[0]);
	if (check_int_conversion(parts[0], (int) color->r) != 0
		|| color->r > 255 || color->r < 0)
		return (free_args(parts), -1);
	color->r = color->r / 255;
	color->g = ft_atoi(parts[1]);
	if (check_int_conversion(parts[1], (int) color->g) != 0
		|| color->g > 255 || color->g < 0)
		return (free_args(parts), -1);
	color->g = color->g / 255;
	color->b = ft_atoi(parts[2]);
	if (check_int_conversion(parts[2], (int) color->b) != 0
		||color->b > 255 || color->b < 0)
		return (free_args(parts), -1);
	color->b = color->b / 255;
	return (free_args(parts), 0);
}

int	get_tuple(char *str, t_tuple *tup, int pt)
{
	char	**parts;

	parts = ft_split(str, ',');
	if (parts == NULL || num_args(parts) != 3)
		return (free_args(parts), -1);
	if (ft_atod(parts[0], &(tup->x)) == -1)
		return (free_args(parts), -1);
	if (ft_atod(parts[1], &(tup->y)) == -1)
		return (free_args(parts), -1);
	if (ft_atod(parts[2], &(tup->z)) == -1)
		return (free_args(parts), -1);
	tup->pt = (double) pt;
	return (free_args(parts), 0);
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

// most conservative systems guarantee precision up to 15 decimal places
// --> error if 16 or more digits in mantissa
static int	check_mantissa(char *doub)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(doub);
	while (i < len)
	{
		if (doub[i] >= '0' && doub[i] <= '9')
			i++;
		else
			return (-1);
	}
	if (i > 15)
		return (-1);
	return (1);
}

int	ft_atod(char *str, double *doub)
{
	char	**parts;
	double	dec;
	int		i;

	i = 0;
	parts = ft_split(str, '.');
	if (parts == NULL || num_args(parts) > 2)
		return (free_args(parts), -1);
	if (parts[0][0] == '-' || parts[0][0] == '+')
		i++;
	*doub = (double) ft_atoi(&(parts[0][i]));
	if (check_int_conversion(&(parts[0][i]), (int) *doub) != 0)
		return (free_args(parts), -1);
	if (num_args(parts) == 2)
	{
		if (check_mantissa(parts[1]) == -1)
			return (free_args(parts), -1);
		dec = ((double) ft_atoi(parts[1]));
		*doub += dec / pow(10.0, (double) ft_strlen(parts[1]));
	}
	if (parts[0][0] == '-' || parts[0][0] == '+')
		*doub *= -1;
	return (free_args(parts), 0);
}
