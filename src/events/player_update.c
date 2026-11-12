/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msingh <msingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:04:02 by msingh            #+#    #+#             */
/*   Updated: 2026/06/20 13:43:38 by msingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_blocked_cell(t_game *game, int mx, int my)
{
	if (!game->map || mx < 0 || my < 0 || my >= game->map_height)
		return (1);
	if (!game->map[my] || mx >= (int)ft_strlen(game->map[my]))
		return (1);
	if (game->map[my][mx] == ' ')
		return (1);
	if (game->map[my][mx] == 'B')
	{
		bonus_touch_barrel(game, mx, my);
		return (bonus_is_barrel_blocking(game, mx, my));
	}
	if (bonus_is_blocking_cell(game, mx, my))
		return (1);
	return (0);
}

static int	can_move_to(t_game *game, double x, double y)
{
	double	pad;

	pad = 0.18;
	if (is_blocked_cell(game, (int)(x - pad), (int)(y - pad)))
		return (0);
	if (is_blocked_cell(game, (int)(x + pad), (int)(y - pad)))
		return (0);
	if (is_blocked_cell(game, (int)(x - pad), (int)(y + pad)))
		return (0);
	if (is_blocked_cell(game, (int)(x + pad), (int)(y + pad)))
		return (0);
	return (1);
}

static void	move_player(t_game *game, double dx, double dy)
{
	double	nx;
	double	ny;

	nx = game->player->pos_x + dx;
	ny = game->player->pos_y + dy;
	if (can_move_to(game, nx, game->player->pos_y))
		game->player->pos_x = nx;
	if (can_move_to(game, game->player->pos_x, ny))
		game->player->pos_y = ny;
}

void	update_player(t_game *game, double dt)
{
	double	move;
	double	rot;

	move = 2.8 * dt;
	rot = 2.2 * dt;
	if (game->player->key_turn_left)
		game->player->angle -= rot;
	if (game->player->key_turn_right)
		game->player->angle += rot;
	game->player->dir_x = cos(game->player->angle);
	game->player->dir_y = sin(game->player->angle);
	if (game->player->key_up)
		move_player(game, game->player->dir_x * move, game->player->dir_y
			* move);
	if (game->player->key_down)
		move_player(game, -game->player->dir_x * move, -game->player->dir_y
			* move);
	if (game->player->key_left)
		move_player(game, game->player->dir_y * move, -game->player->dir_x
			* move);
	if (game->player->key_right)
		move_player(game, -game->player->dir_y * move, game->player->dir_x
			* move);
}
