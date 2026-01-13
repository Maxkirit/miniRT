/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:02:13 by mkeerewe          #+#    #+#             */
/*   Updated: 2026/01/13 17:58:10 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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
			set_data(res, i, j, dot_product(mat_get_row(a, i),
					mat_get_col(b, j)));
			j++;
		}
		i++;
	}
	return (res);
}

t_tuple	mat_tuple_mult(t_mat mat, t_tuple tup)
{
	t_tuple	res;

	res.x = dot_product(mat_get_row(mat, 0), tup);
	res.y = dot_product(mat_get_row(mat, 1), tup);
	res.z = dot_product(mat_get_row(mat, 2), tup);
	res.pt = dot_product(mat_get_row(mat, 3), tup);
	return (res);
}

// check if new_matrix successful in calling function
t_mat	identity(void)
{
	t_mat	res;

	res = new_matrix(4, 4);
	if (res.data == NULL)
		return (res);
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
