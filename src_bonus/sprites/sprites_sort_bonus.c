/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_sort_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assistant <assistant@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 15:00:00 by assistant         #+#    #+#             */
/*   Updated: 2026/06/17 15:00:00 by assistant        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_sprite_distances(t_game *game)
{
	int		i;
	double	dx;
	double	dy;

	i = -1;
	while (++i < game->sprite_count)
	{
		dx = game->player->pos_x - game->sprites[i].x;
		dy = game->player->pos_y - game->sprites[i].y;
		game->sprites[i].dist = dx * dx + dy * dy;
	}
}

void	sort_sprites(t_game *game)
{
	int			i;
	int			j;
	t_sprite	tmp;

	set_sprite_distances(game);
	i = -1;
	while (++i < game->sprite_count - 1)
	{
		j = i;
		while (++j < game->sprite_count)
		{
			if (game->sprites[i].dist < game->sprites[j].dist)
			{
				tmp = game->sprites[i];
				game->sprites[i] = game->sprites[j];
				game->sprites[j] = tmp;
			}
		}
	}
}
