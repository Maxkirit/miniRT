/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:02:13 by mkeerewe          #+#    #+#             */
/*   Updated: 2026/01/07 15:18:58 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

// multiply two 4x4 matrices
// a is left and b is right
// check if new_matrix successful in calling function
t_mat	mat_mult(t_mat a, t_mat b)
{
	t_mat	res;
	int		i;
	int		j;

	res = new_matrix(a.rows, a.cols);
	if (res.data == NULL)
		return (res);
	i = 0;
	while (i < res.rows)
	{
		j = 0;
		while (j < res.cols)
		{
			set_data(res, i, j, dot(mat_get_row(a, i), mat_get_col(b, j)));
			j++;
		}
		i++;
	}
	return (res);
}

t_tuple	mat_tuple_mult(t_mat mat, t_tuple tup)
{
	t_tuple	res;

	res.x = dot(mat_get_row(mat, 0), tup);
	res.y = dot(mat_get_row(mat, 1), tup);
	res.z = dot(mat_get_row(mat, 2), tup);
	res.pt = dot(mat_get_row(mat, 3), tup);
	return (res);
}

// check if new_matrix successful in calling function
t_mat	identity(void)
{
	t_mat	res;
	int		i;

	res = new_matrix(4, 4);
	if (res.data == NULL)
		return (res);
	i = 0;
    set_data(res, 0, 0, 1.0);
    set_data(res, 1, 1, 1.0);
    set_data(res, 2, 2, 1.0);
    set_data(res, 3, 3, 1.0);
	return (res);
}

// check if new_matrix successful in calling function
t_mat	transpose(t_mat mat)
{
	t_mat	res;
	t_tuple	col;
	int		i;

	res = new_matrix(mat.rows, mat.cols);
	if (res.data == NULL)
		return (res);
	i = 0;
	while (i < res.rows)
	{
		col = mat_get_col(mat, i);
		set_data(res, i, 0, col.x);
		set_data(res, i, 1, col.y);
		set_data(res, i, 2, col.z);
		set_data(res, i, 3, col.pt);
		i++;
	}
	return (res);
}
