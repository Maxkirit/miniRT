/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:25:06 by mkeerewe          #+#    #+#             */
/*   Updated: 2026/01/13 19:07:13 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static int	process_args(char **args, t_world *w)
{
	if (ft_strcmp(args[0], "A") == 0)
		return (add_ambient(args, w));
	else if (ft_strcmp(args[0], "C") == 0)
		return (add_camera(args, w));
	else if (ft_strcmp(args[0], "L") == 0)
		return (add_light(args, w));
	else if (ft_strcmp(args[0], "sp") == 0)
		return (add_sphere(args, w));
	else if (ft_strcmp(args[0], "pl") == 0)
		return (add_plane(args, w));
	else if (ft_strcmp(args[0], "cy") == 0)
		return (add_cylinder(args, w));
	else
		return (print_error(1), -1);
}

static void	set_ambient(t_world *world)
{
	world->ambient.ratio = 0;
	world->ambient.color.r = 0;
	world->ambient.color.g = 0;
	world->ambient.color.b = 0;
}

static int	file_setup(int *fd, char *file)
{
	if (check_file_type(file) == -1)
		return (-1);
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
		return (-1);
	return (1);
}

static int	parsing_core(char ***args, char **line, t_world *world)
{
	if ((*line)[ft_strlen(*line) - 1] == '\n')
		(*line)[ft_strlen(*line) - 1] = '\0';
	*args = ft_split(*line, ' ');
	if (args == NULL)
	{
		get_next_line(-1);
		return (free(*line), -1);
	}
	if (process_args(*args, world) == -1)
	{
		get_next_line(-1);
		return (free_args(*args), free(*line), -1);
	}
	free_args(*args);
	return (1);
}

int	parse_file(char *file, t_world *world)
{
	int		fd;
	char	*line;
	char	**args;

	if (file_setup(&fd, file) == -1)
		return (-1);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strlen(line) != 0 && line[0] != '\n')
			if (parsing_core(&args, &line, world) == -1)
				return (-1);
		free(line);
	}
	if (world->cam.fov == -1)
		return (print_error(3), -1);
	if (world->ambient.ratio == -1)
		set_ambient(world);
	return (0);
}
