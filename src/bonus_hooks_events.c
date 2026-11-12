/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_hooks_events.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assistant <assistant@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 12:00:00 by assistant         #+#    #+#             */
/*   Updated: 2026/06/17 15:00:00 by assistant        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	bonus_key_press(t_game *game, int key)
{
	(void)game;
	(void)key;
	return (0);
}

int	setup_bonus_features(t_game *game)
{
	(void)game;
	return (0);
}

void	setup_bonus_hooks(t_game *game)
{
	(void)game;
}

int	mouse_move(int x, int y, void *param)
{
	(void)x;
	(void)y;
	(void)param;
	return (0);
}

void	update_doors(t_game *game, double dt)
{
	(void)game;
	(void)dt;
}
