/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 18:10:43 by mturgeon          #+#    #+#             */
/*   Updated: 2026/01/13 17:10:36 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//destroy image beforehand 
void	end_program(t_data *data)
{
	if (data->win)
		mlx_destroy_window(data->mlx_ptr, data->win);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free_world(data->w);
	exit(0);
}

// called by mlx_hook(pack->screen->mlx_win, 17, 0, close_with_x, data);
static int	close_with_x(t_data *data)
{
	end_program(data);
	return (1);
}

//called by mlx_key_hook(pack->screen->mlx_win, key_handle, pack);
static int	key_handle(int keycode, t_data *data)
{
	if (keycode == 65307)
		end_program(data);
	return (0);
}
void	error(t_data *data)
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
	free_world(data->w);
	exit(1);
}

void	init_mlx(t_data *data, int screen_x, int screen_y)
{
	data->x= screen_x;
	data->y = screen_y;
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		error(data);
	data->win = mlx_new_window(data->mlx_ptr, data->x, data->y, "~.miniRT.~");
	if (!data->win)
		error(data);
	mlx_key_hook(data->win, key_handle, data);
	mlx_hook(data->win, 17, 0, close_with_x, data);
}