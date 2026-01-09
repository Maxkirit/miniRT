/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:37:41 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/09 10:38:57 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_intersection	*inter_realloc(t_intersection *old, int old_size, t_intersection *sol, int num_sol)
{
	int				i;
	t_intersection	*new;

	i = 0;
	new = (t_intersection *) malloc((old_size + num_sol) * sizeof(t_intersection));
	if (!new)
		return (NULL);
	if (old_size > 0)
		ft_memmove(new, old, old_size * sizeof(t_intersection));
	while (i < num_sol)
	{
		new[old_size + i] = sol[i];
		i++;
	}
	free(old);
	return (new);
}

// double	*res_realloc(double *res, int size, t_intersect sol)
// {
// 	double	*temp;
// 	int		i;

// 	if (!res)
// 	{
// 		temp = (double *)malloc(sol.size * sizeof(double));
// 		if (!temp)
// 			return (NULL);
// 	}
// 	else
// 	{
// 		temp = (double *)malloc((size + sol.size) * sizeof(double));
// 		if (!temp)
// 			return (NULL);
// 		ft_memmove((void *)temp, (void *)sol.table, sol.size * sizeof(double));
// 	}
// 	i = 0;
// 	while (i < sol.size)
// 	{
// 		temp[size + i] = sol.table[i];
// 		i++;
// 	}
// 	return (temp);
// }
