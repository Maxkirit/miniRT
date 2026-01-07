/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 18:03:31 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/07 18:46:28 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//guarantees pixel is put in right place by adding offset 
//for data alignement to addess
//img->pointer is top left of image
void	my_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->pointer + (y * img->line_size + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return ;
}

//mlx_new_img each time new render needed
// int	draw_lines_to_img(t_mlx *data)
// {
// 	data->img.pointer = mlx_new_image(data->mlx_ptr, data->x, data->y);
// 	if (!data->img.pointer)
// 		return (0);
// 	data->img.pixels = mlx_get_data_addr(data->img.pointer, &data->img.bits_per_pixel,
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
