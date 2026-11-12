/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_render_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msingh <msingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 12:00:00 by assistant         #+#    #+#             */
/*   Updated: 2026/06/18 13:31:05 by msingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_texture_frames(t_game *game, t_texture *frames, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		destroy_game_texture(game, &frames[i]);
		i++;
	}
}

static int	load_texture_frames(t_game *game, t_texture *frames, int count,
		char *(*get_path)(int))
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (load_game_texture(game, &frames[i], get_path(i)) != 0)
		{
			destroy_texture_frames(game, frames, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	load_bonus_textures(t_game *game)
{
	if (load_texture_frames(game, game->door_frames, DOOR_FRAME_COUNT,
			get_door_frame_path) != 0)
		return (1);
	if (load_texture_frames(game, game->barrel_frames, BARREL_FRAME_COUNT,
			get_barrel_frame_path) != 0)
	{
		destroy_texture_frames(game, game->door_frames, DOOR_FRAME_COUNT);
		return (1);
	}
	return (0);
}

void	free_bonus_data(t_game *game)
{
	destroy_texture_frames(game, game->door_frames, DOOR_FRAME_COUNT);
	destroy_texture_frames(game, game->barrel_frames, BARREL_FRAME_COUNT);
	if (game->doors)
		free(game->doors);
	if (game->sprites)
		free(game->sprites);
	game->doors = NULL;
	game->sprites = NULL;
	game->door_count = 0;
	game->sprite_count = 0;
}

t_texture	*select_door_frame(t_game *game, t_ray_hit *hit)
{
	t_door	*door;
	int		index;

	door = get_door(game, hit->map_x, hit->map_y);
	if (!door)
		return (&game->door_frames[0]);
	index = (int)(door->progress * (double)(DOOR_FRAME_COUNT - 1) + 0.5);
	if (index < 0)
		index = 0;
	if (index >= DOOR_FRAME_COUNT)
		index = DOOR_FRAME_COUNT - 1;
	return (&game->door_frames[index]);
}
