/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 18:03:31 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/09 15:32:44 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//guarantees pixel is put in right place by adding offset 
//for data alignement to addess
//img->pointer is top left of image
void	my_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->pixels + (y * img->line_size + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
	return ;
}

// Returns an int value of the color
// Values of rgb from 0 to 255 inputted as [0.0, 1.0]
// If value > 1, capped at 1. If value < 0, floor at 0
int	rgb_color(double r, double g, double b)
{
	int	round_r;
	int	round_g;
	int	round_b;
	int	ret;

	ret = 0;
	round_r = (int)(r * 255 + 0.5);
	round_r = (int) fminf(255.0f, fmaxf(0.0f, (float) round_r));
	round_g = (int)(g * 255 + 0.5);
	round_g = (int) fminf(255.0f, fmaxf(0.0f, (float) round_g));
	round_b = (int)(b * 255 + 0.5);
	round_b = (int) fminf(255.0f, fmaxf(0.0f, (float) round_b));
	ret = (round_r << 16) | (round_g << 8) | round_b;
	return (ret);
}

//mlx_new_img each time new render needed
// int	draw_lines_to_img(t_mlx *data)
// {
// 	data->img.pointer = mlx_new_image(data->mlx_ptr, data->x, data->y);
// 	if (!data->img.pointer)
// 		return (0);
// 	data->img.pixels = mlx_get_data_addr(data->img.pointer, &data->bpp,
// 			&data->img.line_size, &data->img.endian);
// 	if (!data->img.pixels)
//     {
//         mlx_destroy_image(data->mlx_ptr, data->img.pointer);
//         return (0);
//     }
// 	if (/*draw pixel on data->img->pointer with my_pixel_put*/)
// 	{
// 		mlx_destroy_image(data->mlx_ptr, data->img.pointer);
// 		return (0);
// 	}
// 	mlx_put_image_to_window(data->mlx_ptr, data->win, data->img.pointer, 0, 0);
// 	mlx_destroy_image(data->mlx_ptr, data->img.pointer);
// 	return (1);
// }
