/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_dumper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:33:34 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/18 17:33:34 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	map_dump_object(t_game_object object)
{
	if (object.type == OBJ_EMPTY)
		ft_putstr_fd("  ", OUT);
	else if (object.type == OBJ_WALL)
		ft_putstr_fd("O ", OUT);
	else if (object.type == OBJ_PLAYER)
		ft_putstr_fd("P ", OUT);
	else
	{
		ft_putnbr_fd(object.type, OUT);
		ft_putchar_fd(' ', OUT);
	}
}

void
	map_dump(t_map *map)
{
	int				i;
	int				j;

	i = 0;
	while (i < map->size.h)
	{
		j = 0;
		while (j < map->size.w)
		{
			map_dump_object(map->objs[i][j]);
			j++;
		}
		ft_putchar_fd('\n', OUT);
		i++;
	}
	ft_putchar_fd('\n', OUT);
}
