/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 09:09:02 by mkeerewe          #+#    #+#             */
/*   Updated: 2026/01/12 20:06:37 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_shape	*shape_realloc(t_shape *old, int new_size)
{
	t_shape	*new;

	new = malloc(new_size * sizeof(t_shape));
	if (new == NULL)
		return (old);
	if (old == NULL)
		return (new);
	ft_memmove(new, old, (new_size - 1) * sizeof(t_shape));
	free(old);
	return (new);
}

t_light	*light_realloc(t_light *old, int new_size)
{
	t_light	*new;

	new = malloc(new_size * sizeof(t_light));
	if (new == NULL)
		return (old);
	if (old == NULL)
		return (new);
	ft_memmove(new, old, (new_size - 1) * sizeof(t_light));
	free(old);
	return (new);
}

int	check_int_conversion(char *str, int num)
{
	char	*comp;
	int		ret;

	comp = ft_itoa(num);
	if (comp == NULL)
		return (-1);
	ret = 0;
	if (ft_strcmp(str, comp) != 0)
		ret = -1;
	free(comp);
	return (ret);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
