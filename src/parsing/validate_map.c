/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddo <akaddo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:13:57 by akaddo            #+#    #+#             */
/*   Updated: 2026/06/09 15:06:39 by akaddo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || is_player(c)
		|| bonus_is_map_char(c));
}

static int	validate_chars_and_players(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	game->player_count = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (!is_map_char(game->map[y][x]))
				return (game->error_msg = "Invalid map character", 1);
			if (is_player(game->map[y][x]))
				game->player_count++;
			x++;
		}
		y++;
	}
	if (game->player_count != 1)
		return (game->error_msg = "Map must contain exactly one player", 1);
	return (0);
}

static int	validate_size(t_game *game)
{
	if (!game->map || game->map_height < 3 || game->map_width < 3)
		return (1);
	return (0);
}

int	validate_map(t_game *game)
{
	if (validate_size(game))
		return (game->error_msg = "Map too small", 1);
	if (validate_chars_and_players(game))
		return (1);
	if (validate_closed_map(game))
		return (game->error_msg = "Map is not closed", 1);
	return (0);
}
