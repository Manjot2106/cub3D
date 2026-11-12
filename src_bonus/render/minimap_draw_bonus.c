/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msingh <msingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 12:00:00 by assistant         #+#    #+#             */
/*   Updated: 2026/06/17 11:23:01 by msingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_box(t_game *game, t_rect *box)
{
	int	i;
	int	j;

	i = 0;
	while (i < box->h)
	{
		j = 0;
		while (j < box->w)
		{
			put_pixel_to_frame(game, box->x + j, box->y + i, box->color);
			j++;
		}
		i++;
	}
}

static void	init_line(t_line *l, int p[4])
{
	l->dx = abs(p[2] - p[0]);
	l->sx = 1;
	if (p[0] > p[2])
		l->sx = -1;
	l->dy = -abs(p[3] - p[1]);
	l->sy = 1;
	if (p[1] > p[3])
		l->sy = -1;
	l->err = l->dx + l->dy;
}

void	draw_line(t_game *game, int p[4], int color)
{
	t_line	l;

	init_line(&l, p);
	while (1)
	{
		put_pixel_to_frame(game, p[0], p[1], color);
		if (p[0] == p[2] && p[1] == p[3])
			break ;
		l.e2 = 2 * l.err;
		if (l.e2 >= l.dy)
		{
			l.err += l.dy;
			p[0] += l.sx;
		}
		if (l.e2 <= l.dx)
		{
			l.err += l.dx;
			p[1] += l.sy;
		}
	}
}

static void	draw_ray_segment(t_game *game, int p[2], double angle, double dist)
{
	int	line[4];

	line[0] = p[0];
	line[1] = p[1];
	line[2] = p[0] + (int)(cos(angle) * dist);
	line[3] = p[1] + (int)(sin(angle) * dist);
	draw_line(game, line, 0x6ea3ff);
}

void	draw_rays(t_game *game, int size, int off_x, int off_y)
{
	int			i;
	double		angle;
	t_ray_hit	hit;
	int			p[2];

	p[0] = off_x + (int)(game->player->pos_x * size);
	p[1] = off_y + (int)(game->player->pos_y * size);
	i = 0;
	while (i < RAY_COUNT)
	{
		angle = game->player->angle - (FOV_RAD / 2.0) + ((double)i / (RAY_COUNT
					- 1)) * FOV_RAD;
		cast_ray(game, angle, &hit);
		draw_ray_segment(game, p, angle, hit.dist * size);
		i++;
	}
}
