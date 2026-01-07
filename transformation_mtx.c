/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_mtx.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 12:42:41 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/07 13:59:24 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
Set of functions that create transformation matrices.
They go from object or camera space to world space,
i.e. the objects/camera are created w/ their centers at (0,0,0)
then the transformation places them at the correct spot and rotation.
We are using a left handed coordinate system with z going through the screen
opposite to the user.
*/

//Scales to right size. For sphere, x=y=z=R.
//For cylinder, x=z=R and y=H/2
//if (!res.data)--> malloc error
t_mat	scale_mtx(double x, double y, double z)
{
    t_mat   res;

    res = new_matrix(4, 4);
    if (!res.data)
        return (res);
    set_data(res, 0, 0, x);
    set_data(res, 1, 1, y);
    set_data(res, 2, 2, z);
    set_data(res, 3, 3, 1);
    return (res);
}

//dest must be a point
//if (!res.data)--> malloc error
t_mat   translate_mtx(t_tuple dest)
{
    t_mat   res;

    res = identity();
    if (!res.data)
        return (res);
    set_data(res, 0, 3, dest.x);
    set_data(res, 1, 3, dest.y);
    set_data(res, 2, 3, dest.z);
    return (res);
}

