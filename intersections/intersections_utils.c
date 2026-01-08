/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:37:41 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/08 16:07:51 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	*res_realloc(double *res, int size, t_intersect sol)
{
	double	*temp;
	int		i;

	if (!res)
	{
		temp = (double *)malloc(sol.size * sizeof(double));
		if (!temp)
			return (NULL);
	}
	else
	{
		temp = (double *)malloc((size + sol.size) * sizeof(double));
		if (!temp)
			return (NULL);
		ft_memmove((void *)temp, (void *)sol.table, sol.size * sizeof(double));
	}
	i = 0;
	while (i < sol.size)
	{
		temp[size + i] = sol.table[i];
		i++;
	}
	return (temp);
}
