/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_render_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msingh <msingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:10:00 by assistant         #+#    #+#             */
/*   Updated: 2026/06/18 13:30:22 by msingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_sprite_transform(t_game *game, t_sprite *sprite,
		t_sprite_draw *d)
{
	double	plane_x;
	double	plane_y;
	double	inv_det;
	double	sprite_x;
	double	sprite_y;

	plane_x = -game->player->dir_y * tan(FOV_RAD / 2.0);
	plane_y = game->player->dir_x * tan(FOV_RAD / 2.0);
	inv_det = 1.0 / (plane_x * game->player->dir_y - game->player->dir_x
			* plane_y);
	sprite_x = sprite->x - game->player->pos_x;
	sprite_y = sprite->y - game->player->pos_y;
	d->transform_x = inv_det * (game->player->dir_y * sprite_x
			- game->player->dir_x * sprite_y);
	d->transform_y = inv_det * (-plane_y * sprite_x + plane_x * sprite_y);
}

static void	init_sprite_screen(t_sprite_draw *d, t_sprite *sprite)
{
	d->screen_x = (int)((WIN_W / 2) * (1 + d->transform_x / d->transform_y));
	d->height = abs((int)(((double)WIN_H / d->transform_y)
				* get_sprite_scale(sprite)));
	if (d->height < 1)
		d->height = 1;
	d->width = d->height;
	d->start_y = -d->height / 2 + WIN_H / 2;
	d->end_y = d->height / 2 + WIN_H / 2;
	d->start_x = -d->width / 2 + d->screen_x;
	d->end_x = d->width / 2 + d->screen_x;
	clamp_sprite_screen(d);
}

static void	draw_sprite_stripe(t_game *game, t_sprite_draw *d, t_sprite *sprite,
		int stripe)
{
	int	y;
	int	color;
	int	pos[2];

	y = d->start_y;
	while (y <= d->end_y)
	{
		pos[0] = stripe;
		pos[1] = y;
		color = get_sprite_pixel(game, d, sprite, pos);
		if (color != -1)
			put_pixel_to_frame(game, stripe, y, color);
		y++;
	}
}

static void	draw_one_sprite(t_game *game, t_sprite *sprite)
{
	int				stripe;
	t_sprite_draw	d;

	if (sprite->state == 2)
		return ;
	init_sprite_transform(game, sprite, &d);
	if (d.transform_y <= 0.05)
		return ;
	init_sprite_screen(&d, sprite);
	stripe = d.start_x;
	while (stripe <= d.end_x)
	{
		if (d.transform_y > 0.0 && stripe > 0 && stripe < WIN_W
			&& d.transform_y < game->zbuffer[stripe])
			draw_sprite_stripe(game, &d, sprite, stripe);
		stripe++;
	}
}

void	draw_sprites(t_game *game)
{
	int	i;

	if (!game->sprites || !game->barrel_frames[0].addr)
		return ;
	sort_sprites(game);
	i = 0;
	while (i < game->sprite_count)
	{
		draw_one_sprite(game, &game->sprites[i]);
		i++;
	}
}
