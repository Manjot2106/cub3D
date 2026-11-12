/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddo <akaddo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 18:33:43 by akaddo            #+#    #+#             */
/*   Updated: 2026/06/10 18:43:01 by akaddo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	map_cell_color(char cell)
{
	if (cell == '1' || cell == ' ')
		return (0x4a3a34);
	if (cell == 'D' || cell == 'A' || cell == 'C')
		return (0x8b4513);
	if (cell == 'O')
		return (0xe0a96d);
	if (cell == 'B')
		return (0x7b4b2a);
	return (0xd9ceb6);
}

static void	set_map_box(t_minimap *m, t_rect *box, int c, int r)
{
	box->x = m->origin_x + c * m->cell_size;
	box->y = m->origin_y + r * m->cell_size;
	box->w = m->cell_size;
	box->h = m->cell_size;
}

void	draw_map_layer(t_game *game, t_minimap *m)
{
	int		r;
	int		c;
	t_rect	box;

	r = 0;
	while (game->map && game->map[r])
	{
		c = 0;
		while (game->map[r][c])
		{
			set_map_box(m, &box, c, r);
			box.color = map_cell_color(game->map[r][c]);
			draw_box(game, &box);
			c++;
		}
		r++;
	}
}

void	draw_player_dir(t_game *game, int px, int py, int size)
{
	int	p[4];

	p[0] = px;
	p[1] = py;
	p[2] = px + (int)(game->player->dir_x * (size / 2));
	p[3] = py + (int)(game->player->dir_y * (size / 2));
	draw_line(game, p, 0x00334c);
}
