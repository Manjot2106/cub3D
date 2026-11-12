/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddo <akaddo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:22:30 by msingh            #+#    #+#             */
/*   Updated: 2026/06/11 13:37:55 by akaddo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	spawn_angle(char c)
{
	if (c == 'N')
		return (-M_PI / 2.0);
	if (c == 'S')
		return (M_PI / 2.0);
	if (c == 'E')
		return (0.0);
	return (M_PI);
}

void	set_spawn_data(t_game *game, int i, int j, char c)
{
	game->player->pos_x = (double)j + 0.5;
	game->player->pos_y = (double)i + 0.5;
	game->player->angle = 0.0;
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		game->player->angle = spawn_angle(c);
		game->map[i][j] = '0';
	}
}

int	set_spawn_from_map(t_game *game)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (game->map && game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			c = game->map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				return (set_spawn_data(game, i, j, c), 0);
			j++;
		}
		i++;
	}
	return (1);
}

void	init_player_controls(t_player *player)
{
	player->new_pos_x = 0;
	player->new_pos_y = 0;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->key_turn_left = false;
	player->key_turn_right = false;
	player->last_frame_time = 0.0;
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
	player->mouse_prev_x = 0;
	player->mouse_init = false;
}

int	init_player_data(t_game *game)
{
	t_player	*player;

	if (!game)
		return (1);
	if (!game->player)
	{
		game->player = malloc(sizeof(t_player));
		if (!game->player)
			return (1);
	}
	player = game->player;
	player->angle = 0.0;
	if (set_spawn_from_map(game) != 0)
		return (1);
	init_player_controls(player);
	return (0);
}
