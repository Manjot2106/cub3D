/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_setup_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msingh <msingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 15:55:00 by assistant         #+#    #+#             */
/*   Updated: 2026/06/13 15:55:00 by assistant        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_doors(t_game *game)
{
	int	y;
	int	x;
	int	count;

	y = 0;
	count = 0;
	while (game->map && game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'D' || game->map[y][x] == 'O')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	init_door(t_game *game, int id, int x, int y)
{
	game->doors[id].x = x;
	game->doors[id].y = y;
	game->doors[id].target_open = (game->map[y][x] == 'O');
	if (game->doors[id].target_open)
		game->doors[id].progress = 1.0;
	else
		game->doors[id].progress = 0.0;
}

static void	fill_doors(t_game *game)
{
	int	y;
	int	x;
	int	id;

	y = 0;
	id = 0;
	while (game->map && game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'D' || game->map[y][x] == 'O')
				init_door(game, id++, x, y);
			x++;
		}
		y++;
	}
}

int	setup_doors(t_game *game)
{
	if (!game)
		return (1);
	game->door_count = count_doors(game);
	if (game->door_count == 0)
		return (0);
	game->doors = malloc(sizeof(t_door) * game->door_count);
	if (!game->doors)
		return (1);
	fill_doors(game);
	return (0);
}
