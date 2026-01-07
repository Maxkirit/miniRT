/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:59:08 by mkeerewe          #+#    #+#             */
/*   Updated: 2026/01/07 14:23:47 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	point(double x, double y, double z)
{
	t_tuple	pt;

	pt.x = x;
	pt.y = y;
	pt.z = z;
	pt.pt = 1.0;
	return (pt);
}

// returns v = (x, y, z)
t_tuple	vector(double x, double y, double z)
{
	t_tuple	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	vec.pt = 0.0;
	return (vec);
}

//returns a + b
t_tuple	add_tuples(t_tuple a, t_tuple b)
{
	t_tuple	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	res.pt = a.pt + b.pt;
	return (res);
}


//returns a - b
t_tuple	substr_tuples(t_tuple a, t_tuple b)
{
	t_tuple	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	res.pt = a.pt - b.pt;
	return (res);
}

//returns -v
t_tuple	neg_tuples(t_tuple a)
{
	t_tuple	res;
	t_tuple	zero;

	zero = vector(0, 0, 0);
	res = substr_tuples(zero, a);
	return (res);
}
