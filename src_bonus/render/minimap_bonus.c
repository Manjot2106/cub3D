/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msingh <msingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 12:50:58 by akaddo            #+#    #+#             */
/*   Updated: 2026/06/15 16:38:36 by msingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_minimap(t_game *game, t_minimap *m)
{
	int	biggest;

	biggest = game->map_row;
	if (game->map_cols > biggest)
		biggest = game->map_cols;
	if (biggest <= 0)
		biggest = 1;
	m->cell_size = MINIMAP_SIZE / biggest;
	if (m->cell_size < 3)
		m->cell_size = 3;
	if (m->cell_size > 18)
		m->cell_size = 18;
	m->origin_x = MINIMAP_MARGIN;
	m->origin_y = MINIMAP_MARGIN;
	m->width = game->map_cols * m->cell_size;
	m->height = game->map_row * m->cell_size;
}

static void	draw_minimap_bg(t_game *game, t_minimap *m)
{
	t_rect	box;

	box.x = m->origin_x - 4;
	box.y = m->origin_y - 4;
	box.w = m->width + 8;
	box.h = m->height + 8;
	box.color = 0x0d1117;
	draw_box(game, &box);
}

void	draw_player_marker(t_game *game, int size, int off_x, int off_y)
{
	int		px;
	int		py;
	t_rect	box;

	px = off_x + (int)(game->player->pos_x * size);
	py = off_y + (int)(game->player->pos_y * size);
	box.x = px - 3;
	box.y = py - 3;
	box.w = 7;
	box.h = 7;
	box.color = 0x00c2ff;
	draw_box(game, &box);
	draw_player_dir(game, px, py, size);
}

void	draw_minimap(t_game *game)
{
	t_minimap	minimap;

	init_minimap(game, &minimap);
	draw_minimap_bg(game, &minimap);
	draw_map_layer(game, &minimap);
	draw_rays(game, minimap.cell_size, minimap.origin_x, minimap.origin_y);
	draw_player_marker(game, minimap.cell_size, minimap.origin_x,
		minimap.origin_y);
}
