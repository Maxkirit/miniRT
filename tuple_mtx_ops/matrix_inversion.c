/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 11:26:47 by mkeerewe          #+#    #+#             */
/*   Updated: 2026/01/13 18:03:45 by mturgeon         ###   ########.fr       */
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
	i = -1;
	k = 0;
	while (++i < mat.rows)
	{
		j = -1;
		if (i == row)
			continue ;
		while (++j < mat.cols)
		{
			if (j != col)
			{
				res.data[k] = get_data(mat, i, j);
				k++;
			}
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
		free(res.data);
		res.data = NULL;
		return (res);
	}
	i = 0;
	while (i < mat.rows)
	{
		j = -1;
		while (++j < mat.cols)
			set_data(res, j, i, cofactor(mat, i, j) / det);
		i++;
	}
	return (res);
}
