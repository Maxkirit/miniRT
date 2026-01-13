/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:53:32 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/13 18:16:32 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_tuple	mat_get_col(t_mat mat, int col)
{
	t_tuple	ret;

	ret.x = get_data(mat, 0, col);
	ret.y = get_data(mat, 1, col);
	ret.z = get_data(mat, 2, col);
	ret.pt = get_data(mat, 3, col);
	return (ret);
}

t_tuple	mat_get_row(t_mat mat, int row)
{
	t_tuple	ret;

	ret.x = get_data(mat, row, 0);
	ret.y = get_data(mat, row, 1);
	ret.z = get_data(mat, row, 2);
	ret.pt = get_data(mat, row, 3);
	return (ret);
}

static double	minor(t_mat mat, int row, int col)
{
	t_mat	submat;
	double	ret;

	submat = submatrix(mat, row, col);
	ret = determinant(submat);
	free(submat.data);
	return (ret);
}

double	cofactor(t_mat mat, int row, int col)
{
	double	min;

	min = minor(mat, row, col);
	if ((row + col) % 2 == 0)
		return (min);
	else
		return (min * -1.0);
}

double	determinant(t_mat mat)
{
	double	res;
	int		i;

	if (mat.rows == 2)
		return (get_data(mat, 0, 0) * get_data(mat, 1, 1)
			- get_data(mat, 0, 1) * get_data(mat, 1, 0));
	else
	{
		i = 0;
		res = 0;
		while (i < mat.cols)
		{
			res += get_data(mat, 0, i) * cofactor(mat, 0, i);
			i++;
		}
	}
	return (res);
}
