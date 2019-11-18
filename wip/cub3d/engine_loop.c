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

	if (engine->dirty)
	{
		render_scene(engine);
		mlx_put_image_to_window(engine->ctx.mlx, engine->ctx.win,
								engine->canvas->ptr, 0, 0);
	}
	engine->player.move_speed = 0.01 * 5.0;
	engine->player.rot_speed = 0.01 * 5.0;
	has_moved = player_handle_mouvement(engine->map, &(engine->player));
	engine->dirty = engine->dirty || has_moved;
	return (0);
}
