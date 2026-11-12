/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_closed_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddo <akaddo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 15:13:24 by akaddo            #+#    #+#             */
/*   Updated: 2026/06/09 14:34:07 by akaddo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| bonus_is_walkable(c));
}

static int	is_outside_or_space(t_game *game, int y, int x)
{
	if (y < 0 || y >= game->map_height)
		return (1);
	if (x < 0 || x >= (int)ft_strlen(game->map[y]))
		return (1);
	if (game->map[y][x] == ' ' || game->map[y][x] == '\0')
		return (1);
	return (0);
}

static int	check_walkable_cell(t_game *game, int y, int x)
{
	if (is_outside_or_space(game, y - 1, x))
		return (1);
	if (is_outside_or_space(game, y + 1, x))
		return (1);
	if (is_outside_or_space(game, y, x - 1))
		return (1);
	if (is_outside_or_space(game, y, x + 1))
		return (1);
	return (0);
}

int	validate_closed_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (is_walkable(game->map[y][x]))
			{
				if (check_walkable_cell(game, y, x))
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
