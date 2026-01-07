/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:24:39 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/07 18:50:31 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
Placeholder
*/

int main(void)
{
    t_mlx   test;

    init_mlx(&test, 1600, 900);
    mlx_loop(test.mlx_ptr);
	mlx_destroy_window(test.mlx_ptr, test.win);
	mlx_destroy_display(test.mlx_ptr);
	free(test.mlx_ptr);
    return (0);
}