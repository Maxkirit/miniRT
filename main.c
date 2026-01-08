/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:24:39 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/08 11:04:30 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int main(void)
{
    t_mlx   test;

    init_mlx(&test, 1600, 900);
    int i = 0;
    int j = 0;
    test.img.pointer = mlx_new_image(test.mlx_ptr, 1600, 900);
    if (!test.img.pointer)
        error(&test);
    test.img.pixels = mlx_get_data_addr(test.img.pointer, &test.img.bpp, &test.img.line_size, &test.img.endian);
    if (!test.img.pixels)
        error(&test);
    while (i < 1600)
    {
        j = 0;
        while (j < 900)
        {
            my_pixel_put(&test.img, i, j, 0xca03fc);
            j++;
        }
        i++;
    }
    mlx_put_image_to_window(test.mlx_ptr, test.win, test.img.pointer, 0, 0);
    mlx_destroy_image(test.mlx_ptr, test.img.pointer);
    mlx_loop(test.mlx_ptr);
	mlx_destroy_window(test.mlx_ptr, test.win);
	mlx_destroy_display(test.mlx_ptr);
	free(test.mlx_ptr);
    return (0);
}