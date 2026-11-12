/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_hooks_render.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assistant <assistant@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 12:00:00 by assistant         #+#    #+#             */
/*   Updated: 2026/06/15 12:00:00 by assistant        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_bonus_textures(t_game *game)
{
	(void)game;
	return (0);
}

void	free_bonus_data(t_game *game)
{
	(void)game;
}

int	bonus_is_blocking_cell(t_game *game, int map_x, int map_y)
{
	(void)game;
	(void)map_x;
	(void)map_y;
	return (0);
}

t_texture	*bonus_select_texture(t_game *game, t_ray_hit *hit)
{
	(void)game;
	(void)hit;
	return (NULL);
}

void	draw_bonus_overlay(t_game *game)
{
	(void)game;
}
