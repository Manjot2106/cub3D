/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_barrels_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assistant <assistant@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 15:00:00 by assistant         #+#    #+#             */
/*   Updated: 2026/06/17 15:00:00 by assistant        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_sprite	*get_barrel(t_game *game, int map_x, int map_y)
{
	int	i;

	i = 0;
	while (i < game->sprite_count)
	{
		if (game->sprites[i].map_x == map_x
			&& game->sprites[i].map_y == map_y)
			return (&game->sprites[i]);
		i++;
	}
	return (NULL);
}

void	bonus_touch_barrel(t_game *game, int map_x, int map_y)
{
	t_sprite	*barrel;

	barrel = get_barrel(game, map_x, map_y);
	if (!barrel || barrel->state != 0)
		return ;
	barrel->state = 1;
	barrel->anim = 0.0;
}

int	bonus_is_barrel_blocking(t_game *game, int map_x, int map_y)
{
	t_sprite	*barrel;

	barrel = get_barrel(game, map_x, map_y);
	if (!barrel)
		return (1);
	return (barrel->state != 2);
}

void	update_barrels(t_game *game, double dt)
{
	int	i;

	i = 0;
	while (i < game->sprite_count)
	{
		if (game->sprites[i].state == 1)
		{
			game->sprites[i].anim += dt * BARREL_ANIM_SPEED;
			if (game->sprites[i].anim >= 1.0)
			{
				game->sprites[i].anim = 1.0;
				game->sprites[i].state = 2;
			}
		}
		i++;
	}
}
