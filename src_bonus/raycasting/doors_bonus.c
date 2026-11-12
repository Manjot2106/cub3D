/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msingh <msingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 14:58:45 by msingh            #+#    #+#             */
/*   Updated: 2026/06/17 15:00:00 by assistant        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_map_wall(t_game *game, int x, int y)
{
	if (!game || !game->map || y < 0 || y >= game->map_height || x < 0)
		return (1);
	if (!game->map[y] || x >= (int)ft_strlen(game->map[y]))
		return (1);
	return (game->map[y][x] == '1' || game->map[y][x] == ' ');
}

int	is_door_vertical(t_game *game, int x, int y)
{
	if (is_map_wall(game, x, y - 1) && is_map_wall(game, x, y + 1))
		return (1);
	if (is_map_wall(game, x - 1, y) && is_map_wall(game, x + 1, y))
		return (0);
	return (1);
}

double	door_ease(double t)
{
	if (t < 0.0)
		t = 0.0;
	if (t > 1.0)
		t = 1.0;
	return (t * t * (3.0 - 2.0 * t));
}

int	is_door_blocking(t_game *game, int map_x, int map_y)
{
	t_door	*door;

	if (!game || !game->map || map_x < 0 || map_y < 0)
		return (0);
	if (map_y >= game->map_height || !game->map[map_y])
		return (0);
	if (map_x >= (int)ft_strlen(game->map[map_y]))
		return (0);
	if (game->map[map_y][map_x] != 'D' && game->map[map_y][map_x] != 'O')
		return (0);
	door = get_door(game, map_x, map_y);
	if (!door)
		return (game->map[map_y][map_x] == 'D');
	return (door->progress < 0.96);
}

t_door	*get_door(t_game *game, int map_x, int map_y)
{
	int	i;

	if (!game || !game->doors)
		return (NULL);
	i = 0;
	while (i < game->door_count)
	{
		if (game->doors[i].x == map_x && game->doors[i].y == map_y)
			return (&game->doors[i]);
		i++;
	}
	return (NULL);
}
