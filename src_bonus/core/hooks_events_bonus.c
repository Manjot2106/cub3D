/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_events_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msingh <msingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 12:00:00 by assistant         #+#    #+#             */
/*   Updated: 2026/06/20 14:26:22 by msingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	bonus_key_press(t_game *game, int key)
{
	if (key == XK_e || key == XK_E)
		toggle_door(game);
	return (0);
}

int	setup_bonus_features(t_game *game)
{
	if (setup_doors(game) != 0)
		return (1);
	if (setup_sprites(game) != 0)
	{
		if (game->doors)
			free(game->doors);
		game->doors = NULL;
		game->door_count = 0;
		return (1);
	}
	return (0);
}

void	setup_bonus_hooks(t_game *game)
{
	mlx_mouse_move(game->mlx->mlx_ptr, game->mlx->win_ptr,
		WIN_W / 2, WIN_H / 2);
}

int	mouse_move(int x, int y, void *param)
{
	t_game	*game;
	int		delta;

	game = (t_game *)param;
	if (!game || !game->mlx || !game->mlx->mlx_ptr
		|| !game->mlx->win_ptr || !game->player)
		return (0);
	if (x == (WIN_W / 2) && y == (WIN_H / 2))
		return (0);
	delta = x - (WIN_W / 2);
	if (delta != 0)
		game->player->angle += (double)delta * MOUSE_SENSITIVITY;
	mlx_mouse_move(game->mlx->mlx_ptr, game->mlx->win_ptr,
		WIN_W / 2, WIN_H / 2);
	return (0);
}
