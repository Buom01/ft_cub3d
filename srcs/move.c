/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 22:14:45 by badam             #+#    #+#             */
/*   Updated: 2020/06/10 17:12:54 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_state *state, int direction)
{
	state->pos.x += SIN(state->yaw * TORAD) * direction * 0.1;
	state->pos.z += COS(state->yaw * TORAD) * direction * 0.1;
}

void	move_side(t_state *state, int direction)
{
	state->pos.x -= COS(state->yaw * TORAD) * direction * 0.1;
	state->pos.z += SIN(state->yaw * TORAD) * direction * 0.1;
}

void	jump(t_state *state)
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

void	move_update(t_state *state)
{
	if (state->crouch && !state->jumping)
		state->pos.y = 0.35;
	else if (state->jumping)
	{
		state->jump_velocity -= 0.008;
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
