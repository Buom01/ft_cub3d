/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 22:14:45 by badam             #+#    #+#             */
/*   Updated: 2020/07/07 17:46:51 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_speed_ratio(t_state *state)
{
	if (state->crouch)
		return (0.03);
	else
		return (0.08);
}

void			move_forward(t_state *state, int direction)
{
	double	speed_ratio;

	speed_ratio = get_speed_ratio(state);
	state->move_x += SIN(state->yaw * TORAD) * direction * speed_ratio;
	state->move_z -= COS(state->yaw * TORAD) * direction * speed_ratio;
}

void			move_side(t_state *state, int direction)
{
	double	speed_ratio;

	speed_ratio = get_speed_ratio(state);
	state->move_x -= COS(state->yaw * TORAD) * direction * speed_ratio;
	state->move_z -= SIN(state->yaw * TORAD) * direction * speed_ratio;
}

void			jump(t_state *state)
{
	if (!state->crouch)
	{
		if (state->pos.y < 0)
			state->pos.y = 0;
		if (!state->jumping)
		{
			state->jump_velocity = 0.05;
			state->jumping = true;
		}
	}
}

void			move_update(t_state *state)
{
	if (state->crouch && !state->jumping)
		state->pos.y = 0.35;
	else if (state->jumping)
	{
		state->jump_velocity -= 0.006;
		state->pos.y += state->jump_velocity;
		if (state->pos.y <= 0.5)
		{
			state->jumping = false;
			state->pos.y = 0.5;
		}
	}
	else
		state->pos.y = 0.5;
}
