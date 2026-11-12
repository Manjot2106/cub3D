/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msingh <msingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:06:50 by msingh            #+#    #+#             */
/*   Updated: 2026/06/15 12:00:00 by assistant        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_mlx_cb	to_loop_cb(int (*f)(void *))
{
	t_mlx_cb	cb;

	ft_memcpy(&cb, &f, sizeof(cb));
	return (cb);
}

static t_mlx_cb	to_key_cb(int (*f)(int, void *))
{
	t_mlx_cb	cb;

	ft_memcpy(&cb, &f, sizeof(cb));
	return (cb);
}

static t_mlx_cb	to_mouse_cb(int (*f)(int, int, void *))
{
	t_mlx_cb	cb;

	ft_memcpy(&cb, &f, sizeof(cb));
	return (cb);
}

static int	close_window_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	free_exit(game, 0);
	return (0);
}

int	setup_hooks(t_game *game)
{
	if (setup_bonus_features(game) != 0)
		return (1);
	mlx_loop_hook(game->mlx->mlx_ptr, to_loop_cb(game_loop), game);
	mlx_hook(game->mlx->win_ptr, 2, 1L << 0, to_key_cb(key_press), game);
	mlx_hook(game->mlx->win_ptr, 3, 1L << 1, to_key_cb(release), game);
	mlx_hook(game->mlx->win_ptr, 6, 1L << 6, to_mouse_cb(mouse_move), game);
	mlx_hook(game->mlx->win_ptr, 17, 0, to_loop_cb(close_window_hook), game);
	setup_bonus_hooks(game);
	return (0);
}
