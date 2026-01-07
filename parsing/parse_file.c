/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:25:06 by mkeerewe          #+#    #+#             */
/*   Updated: 2026/01/07 16:08:22 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	process_args(char **args, t_world *world)
{
	if (ft_strcmp(args[0], "A") == 0)
		add_ambient(args, world);
	else if (ft_strcmp(args[0], "C") == 0)
		add_camera(args, world);
	else if (ft_strcmp(args[0], "C") == 0)
		add_camera(args, world);
	else if (ft_strcmp(args[0], "C") == 0)
		add_camera(args, world);
	else if (ft_strcmp(args[0], "C") == 0)
		add_camera(args, world);
	else if (ft_strcmp(args[0], "C") == 0)
		add_camera(args, world);
}

int	parse_file(char *file, t_world *world)
{
	int		fd;
	char	*line;
	char	**args;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strlen(line) != 0)
		{
			args = ft_split(line, ' ');
			if (args == NULL)
				return (free(line), -1);
			process_args(args, world);
		}
		free(line);
	}
}
