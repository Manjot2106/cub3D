/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_hooks_events_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assistant <assistant@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 15:00:00 by assistant         #+#    #+#             */
/*   Updated: 2026/06/17 15:00:00 by assistant        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_door_blocking(t_game *game, int map_x, int map_y)
{
	(void)game;
	(void)map_x;
	(void)map_y;
	return (0);
}

t_door	*get_door(t_game *game, int map_x, int map_y)
{
	(void)game;
	(void)map_x;
	(void)map_y;
	return (NULL);
}

void	update_barrels(t_game *game, double dt)
{
	(void)game;
	(void)dt;
}

int	bonus_is_barrel_blocking(t_game *game, int map_x, int map_y)
{
	(void)game;
	(void)map_x;
	(void)map_y;
	return (1);
}

void	bonus_touch_barrel(t_game *game, int map_x, int map_y)
{
	(void)game;
	(void)map_x;
	(void)map_y;
}
