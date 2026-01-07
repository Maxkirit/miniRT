/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 08:43:46 by mkeerewe          #+#    #+#             */
/*   Updated: 2026/01/07 09:59:44 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	mult_vec_scalar(t_tuple vec, double scal)
{
	t_tuple	res;

	res.x = vec.x * scal;
	res.y = vec.y * scal;
	res.z = vec.z * scal;
	res.pt = vec.pt * scal;
	return (res);
}

double	vec_magnitude(t_tuple vec)
{
	double sum;

	sum = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.pt * vec.pt;
	return (sqrt(sum));
}

t_tuple	vec_normalise(t_tuple vec)
{
	t_tuple	res;
	double	mag;

	mag = vec_magnitude(vec);
	res.x = vec.x / mag;
	res.y = vec.y / mag;
	res.z = vec.z / mag;
	res.pt = vec.pt / mag;
	return (res);
}

double	dot(t_tuple a, t_tuple b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.pt * b.pt);
}

t_tuple	cross_product(t_tuple a, t_tuple b)
{
	return (vector(a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x));
}
