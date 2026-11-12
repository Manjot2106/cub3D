/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddo <akaddo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 12:54:02 by akaddo            #+#    #+#             */
/*   Updated: 2026/06/09 12:55:29 by akaddo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_wall_draw(t_wall_draw *d, t_ray_hit *hit, double dist)
{
	d->line_h = (int)((double)WIN_H / dist);
	if (d->line_h < 1)
		d->line_h = 1;
	d->start = (WIN_H - d->line_h) / 2;
	d->end = (WIN_H + d->line_h) / 2;
	if (d->start < 0)
		d->start = 0;
	if (d->end >= WIN_H)
		d->end = WIN_H - 1;
	d->tex_x = (int)(hit->wall_x * d->tex->width);
}

static void	init_texture_column(t_wall_draw *d, t_ray_hit *hit)
{
	if (hit->side == HIT_X && hit->ray_x > 0.0)
		d->tex_x = d->tex->width - d->tex_x - 1;
	if (hit->side == HIT_Y && hit->ray_y < 0.0)
		d->tex_x = d->tex->width - d->tex_x - 1;
	d->step = (double)d->tex->height / (double)d->line_h;
	d->tex_pos = (d->start - (WIN_H / 2) + (d->line_h / 2)) * d->step;
}

static void	draw_wall_pixels(t_game *game, t_wall_draw *d, t_ray_hit *hit)
{
	d->y = d->start;
	while (d->y <= d->end)
	{
		d->tex_y = (int)d->tex_pos;
		d->tex_pos += d->step;
		d->color = get_texture_pixel(d->tex, d->tex_x, d->tex_y);
		if (hit->is_door && is_transparent(d->color))
		{
			d->y++;
			continue ;
		}
		if (hit->side == HIT_Y)
			d->color = darken_color(d->color);
		put_pixel_to_frame(game, d->x, d->y, d->color);
		d->y++;
	}
}

void	draw_wall_column(t_game *game, int x, t_ray_hit *hit, double dist)
{
	t_wall_draw	d;

	d.x = x;
	d.tex = select_wall_texture(game, hit);
	if (!d.tex || !d.tex->addr)
		d.tex = &game->wall_no_tex;
	init_wall_draw(&d, hit, dist);
	init_texture_column(&d, hit);
	draw_wall_pixels(game, &d, hit);
}
