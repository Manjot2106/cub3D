/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_update_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msingh <msingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 15:00:00 by assistant         #+#    #+#             */
/*   Updated: 2026/06/17 15:00:00 by assistant        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	player_is_in_cell(t_game *game, int map_x, int map_y)
{
	if (!game || !game->player)
		return (0);
	return ((int)game->player->pos_x == map_x
		&& (int)game->player->pos_y == map_y);
}

static void	set_door_target(t_game *game, t_door *door)
{
	if (door->target_open)
	{
		if (!player_is_in_cell(game, door->x, door->y))
			door->target_open = 0;
	}
	else
		door->target_open = 1;
	if (door->target_open)
		game->map[door->y][door->x] = 'O';
	else
		game->map[door->y][door->x] = 'D';
}

void	update_doors(t_game *game, double dt)
{
	int		i;
	double	step;

	if (!game || !game->doors)
		return ;
	step = dt * 2.4;
	i = 0;
	while (i < game->door_count)
	{
		if (game->doors[i].target_open)
			game->doors[i].progress += step;
		else
			game->doors[i].progress -= step;
		if (game->doors[i].progress < 0.0)
			game->doors[i].progress = 0.0;
		if (game->doors[i].progress > 1.0)
			game->doors[i].progress = 1.0;
		i++;
	}
}

void	toggle_door(t_game *game)
{
	double	dist;
	int		map_x;
	int		map_y;
	t_door	*door;

	if (!game || !game->player || !game->map)
		return ;
	dist = 0.25;
	while (dist <= 1.60)
	{
		map_x = (int)(game->player->pos_x + game->player->dir_x * dist);
		map_y = (int)(game->player->pos_y + game->player->dir_y * dist);
		door = get_door(game, map_x, map_y);
		if (door)
		{
			set_door_target(game, door);
			return ;
		}
		dist += 0.05;
	}
}
