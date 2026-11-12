/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_setup_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assistant <assistant@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:10:00 by assistant         #+#    #+#             */
/*   Updated: 2026/06/17 15:00:00 by assistant        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_sprites(t_game *game)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (game->map && game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'B')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	init_barrel_sprite(t_sprite *sprite, int x, int y)
{
	sprite->x = (double)x + 0.5;
	sprite->y = (double)y + 0.5;
	sprite->dist = 0.0;
	sprite->anim = 0.0;
	sprite->map_x = x;
	sprite->map_y = y;
	sprite->state = 0;
}

static void	fill_sprites(t_game *game)
{
	int	y;
	int	x;
	int	i;

	i = 0;
	y = -1;
	while (game->map && game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
			if (game->map[y][x] == 'B')
				init_barrel_sprite(&game->sprites[i++], x, y);
		}
	}
}

int	setup_sprites(t_game *game)
{
	game->sprite_count = count_sprites(game);
	if (game->sprite_count == 0)
		return (0);
	game->sprites = malloc(sizeof(t_sprite) * game->sprite_count);
	if (!game->sprites)
		return (1);
	fill_sprites(game);
	return (0);
}
