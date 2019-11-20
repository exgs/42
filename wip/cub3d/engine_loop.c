/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:54:24 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/12 15:54:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	engine_loop(t_engine *engine)
{
	int		has_moved;

	render_scene_smart(engine, RENDER_SHOW_STATS);
	has_moved = player_handle_mouvement(engine->map, &(engine->player));
	engine->dirty = engine->dirty || has_moved;
	return (0);
}