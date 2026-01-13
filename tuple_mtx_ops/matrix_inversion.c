/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 11:26:47 by mkeerewe          #+#    #+#             */
/*   Updated: 2026/01/13 13:45:11 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// check if new_matrix successful in calling function
t_mat	submatrix(t_mat mat, int row, int col)
{
	t_mat	res;
	int		i;
	int		j;
	int		k;

	res = new_matrix(mat.rows - 1, mat.cols - 1);
	if (res.data == NULL)
		return (res);
	i = 0;
	k = 0;
	while (i < mat.rows)
	{
		j = 0;
		if (i == row)
		{
			i++;
			continue ;
		}
		while (j < mat.cols)
		{
			if (j != col)
			{
				res.data[k] = get_data(mat, i, j);
				k++;
			}
			j++;
		}
		i++;
	}
	return (res);
}

double	minor(t_mat mat, int row, int col)
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
		return (get_data(mat, 0, 0) * get_data(mat, 1, 1) -
			get_data(mat, 0, 1) * get_data(mat, 1, 0));
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

// check if new_matrix successful in calling function
t_mat	inverse(t_mat mat)
{
	t_mat	res;
	double	det;
	int		i;
	int		j;

	res = new_matrix(mat.rows, mat.cols);
	if (res.data == NULL)
		return (res);
	det = determinant(mat);
	if (equal(det, 0.0))
	{
		// printf("Unable to inverse matrix\n");
		free(res.data);
		res.data = NULL;
		return (res);
	}
	i = 0;
	while (i < mat.rows)
	{
		j = 0;
		while (j < mat.cols)
		{
			set_data(res, j, i, cofactor(mat, i, j) / det);
			j++;
		}
		i++;
	}
	return (res);
}
