/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddo <akaddo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 11:18:00 by akaddo            #+#    #+#             */
/*   Updated: 2026/06/09 11:30:08 by akaddo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_floor_row(t_game *game, t_floor_cast *f, int y)
{
	double	pos_z;

	pos_z = 0.5 * (double)WIN_H;
	f->row_dist = pos_z / (double)(y - (WIN_H / 2));
	f->step_x = f->row_dist * (f->ray_x1 - f->ray_x0) / (double)WIN_W;
	f->step_y = f->row_dist * (f->ray_y1 - f->ray_y0) / (double)WIN_W;
	f->floor_x = game->player->pos_x + f->row_dist * f->ray_x0;
	f->floor_y = game->player->pos_y + f->row_dist * f->ray_y0;
}

static void	init_floor_cast(t_game *game, t_floor_cast *f)
{
	double	plane;

	plane = tan(FOV_RAD / 2.0);
	f->ray_x0 = game->player->dir_x + game->player->dir_y * plane;
	f->ray_y0 = game->player->dir_y - game->player->dir_x * plane;
	f->ray_x1 = game->player->dir_x - game->player->dir_y * plane;
	f->ray_y1 = game->player->dir_y + game->player->dir_x * plane;
}

static int	get_floor_color(t_game *game,
			double floor_x, double floor_y)
{
	int	tx;
	int	ty;

	if (!game->ground_tex.addr
		|| game->ground_tex.width <= 0
		|| game->ground_tex.height <= 0)
		return (game->config.floor.hex);
	tx = (int)((floor_x - floor(floor_x))
			* game->ground_tex.width);
	ty = (int)((floor_y - floor(floor_y))
			* game->ground_tex.height);
	return (get_texture_pixel(&game->ground_tex, tx, ty));
}

static void	draw_floor_row(t_game *game, t_floor_cast *f, int y)
{
	int	x;

	x = 0;
	while (x < WIN_W)
	{
		put_pixel_to_frame(game, x, y, get_floor_color(game, f->floor_x,
				f->floor_y));
		f->floor_x += f->step_x;
		f->floor_y += f->step_y;
		x++;
	}
}

void	draw_floor_perspective(t_game *game)
{
	t_floor_cast	f;
	int				y;

	init_floor_cast(game, &f);
	y = (WIN_H / 2) + 1;
	while (y < WIN_H)
	{
		init_floor_row(game, &f, y);
		draw_floor_row(game, &f, y);
		y++;
	}
}
