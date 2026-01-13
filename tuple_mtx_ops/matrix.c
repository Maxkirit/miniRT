/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:51:02 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/13 18:15:30 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// if malloc fails handle in calling function
t_mat	new_matrix(int rows, int cols)
{
	t_mat	mat;

	mat.data = (double *)ft_calloc(rows * cols, sizeof(double));
	mat.rows = rows;
	mat.cols = cols;
	return (mat);
}

void	destroy_matrix(t_mat mat)
{
	free(mat.data);
}

double	get_data(t_mat mat, int i, int j)
{
	return (mat.data[mat.cols * i + j]);
}

void	set_data(t_mat mat, int i, int j, double input)
{
	mat.data[mat.cols * i + j] = input;
}

int	mat_equal(t_mat a, t_mat b)
{
	int	i;
	int	j;

	i = 0;
	while (i < a.rows)
	{
		j = 0;
		while (j < a.cols)
		{
			if (equal(get_data(a, i, j), get_data(b, i, j)) != 1)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
