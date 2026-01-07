/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 11:26:47 by mkeerewe          #+#    #+#             */
/*   Updated: 2026/01/07 11:37:52 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	determinant(t_mat mat)
{
	return (get_data(mat, 0, 0) * get_data(mat, 1, 1) -
		get_data(mat, 0, 1) * get_data(mat, 1, 0));
}

// // check if new_matrix successful in calling function
// t_mat	submatrix(t_mat mat, int row, int col)
// {
// 	t_mat	res;
// 	int		i;
// 	int		j;

// 	res = new_matrix(mat.rows - 1, mat.cols - 1);
// 	if (res.data == NULL)
// 		return (res);
// 	i = 0;
// 	while (i < res.rows)
// 	{
// 		j = 0;
// 		while (j < res.cols)
// 		{
			
// 		}
		
// 	}
	
// }
