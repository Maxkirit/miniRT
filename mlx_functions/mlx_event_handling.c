/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 18:10:43 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/08 13:29:47 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//destroy image beforehand 
void	end_program(t_mlx *data)
{
	if (data->win)
		mlx_destroy_window(data->mlx_ptr, data->win);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	exit(0);
}

// called by mlx_hook(pack->screen->mlx_win, 17, 0, close_with_x, data);
static int	close_with_x(t_mlx *data)
{
	end_program(data);
	return (1);
}

//called by mlx_key_hook(pack->screen->mlx_win, key_handle, pack);
static int	key_handle(int keycode, t_mlx *data)
{
	if (keycode == 65307)
		end_program(data);
	return (0);
}
void	error(t_mlx *data)
{
	//free non mlx related shit here if needed
	if (data->img.pointer)
		mlx_destroy_image(data->mlx_ptr, data->img.pointer);
	if (data->mlx_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	exit(1);
}

void	init_mlx(t_mlx *data, int screen_x, int screen_y)
{
	data->x= screen_x;
	data->y = screen_y;
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		//free non mlx stuff here
		error(data);
	}
	data->win = mlx_new_window(data->mlx_ptr, data->x, data->y, "~.miniRT.~");
	if (!data->win)
	{
		//free non mlx stuff here
		error(data);
	}
	mlx_key_hook(data->win, key_handle, data);
	mlx_hook(data->win, 17, 0, close_with_x, data);
}