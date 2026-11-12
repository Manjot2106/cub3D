/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msingh <msingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:06:57 by msingh            #+#    #+#             */
/*   Updated: 2026/06/17 17:35:11 by msingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_time_seconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.0);
}

int	key_press(int key, void *param)
{
	t_game		*game;
	t_player	*p;

	game = (t_game *)param;
	p = game->player;
	if (key == XK_Escape)
		free_exit(game, 0);
	if (key == XK_w)
		p->key_up = true;
	if (key == XK_s)
		p->key_down = true;
	if (key == XK_a)
		p->key_left = true;
	if (key == XK_d)
		p->key_right = true;
	if (key == XK_Left)
		p->key_turn_left = true;
	if (key == XK_Right)
		p->key_turn_right = true;
	bonus_key_press(game, key);
	return (0);
}

int	release(int key, void *param)
{
	t_game		*game;
	t_player	*p;

	game = (t_game *)param;
	p = game->player;
	if (key == XK_w)
		p->key_up = false;
	if (key == XK_s)
		p->key_down = false;
	if (key == XK_a)
		p->key_left = false;
	if (key == XK_d)
		p->key_right = false;
	if (key == XK_Left)
		p->key_turn_left = false;
	if (key == XK_Right)
		p->key_turn_right = false;
	return (0);
}

int	game_loop(void *param)
{
	t_game	*game;
	double	now;
	double	dt;

	game = (t_game *)param;
	now = get_time_seconds();
	if (game->player->last_frame_time == 0.0)
		game->player->last_frame_time = now;
	dt = now - game->player->last_frame_time;
	if (dt < 0.0)
		dt = 0.0;
	if (dt > 0.05)
		dt = 0.05;
	game->player->last_frame_time = now;
	update_player(game, dt);
	update_doors(game, dt);
	update_barrels(game, dt);
	render_first_frame(game);
	return (0);
}
