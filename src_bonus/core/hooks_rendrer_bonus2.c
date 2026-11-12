/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_rendrer_bonus2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msingh <msingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:26:20 by msingh            #+#    #+#             */
/*   Updated: 2026/06/18 13:34:44 by msingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_barrel_frame_path(int index)
{
	if (index == 0)
		return ("./textures/barrel_explosion_00_idle.xpm");
	if (index == 1)
		return ("./textures/barrel_explosion_01_spark.xpm");
	if (index == 2)
		return ("./textures/barrel_explosion_02_pop.xpm");
	if (index == 3)
		return ("./textures/barrel_explosion_03_blast.xpm");
	if (index == 4)
		return ("./textures/barrel_explosion_04_full.xpm");
	if (index == 5)
		return ("./textures/barrel_explosion_05_smoke.xpm");
	if (index == 6)
		return ("./textures/barrel_explosion_06_fade.xpm");
	if (index == 7)
		return ("./textures/barrel_explosion_07_end.xpm");
	return (NULL);
}

char	*get_door_frame_path(int index)
{
	if (index == 0)
		return ("./textures/door_opening_large_00_closed.xpm");
	if (index == 1)
		return ("./textures/door_opening_large_01_crack.xpm");
	if (index == 2)
		return ("./textures/door_opening_large_02_ajar.xpm");
	if (index == 3)
		return ("./textures/door_opening_large_03_opening.xpm");
	if (index == 4)
		return ("./textures/door_opening_large_04_half_open.xpm");
	if (index == 5)
		return ("./textures/door_opening_large_05_wide.xpm");
	if (index == 6)
		return ("./textures/door_opening_large_06_almost_open.xpm");
	if (index == 7)
		return ("./textures/door_opening_large_07_open.xpm");
	return (NULL);
}

t_texture	*bonus_select_texture(t_game *game, t_ray_hit *hit)
{
	if (hit->is_door && game->door_frames[0].addr)
		return (select_door_frame(game, hit));
	return (NULL);
}

void	draw_bonus_overlay(t_game *game)
{
	draw_sprites(game);
	draw_minimap(game);
}

int	bonus_is_blocking_cell(t_game *game, int map_x, int map_y)
{
	return (is_door_blocking(game, map_x, map_y));
}
