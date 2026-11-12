/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msingh <msingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 17:14:38 by msingh            #+#    #+#             */
/*   Updated: 2026/06/18 13:24:47 by msingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall_cell(t_game *game, int map_x, int map_y)
{
	if (map_y < 0 || map_y >= game->map_height || map_x < 0)
		return (1);
	if (!game->map[map_y] || map_x >= (int)ft_strlen(game->map[map_y]))
		return (1);
	if (game->map[map_y][map_x] == '1' || game->map[map_y][map_x] == ' ')
		return (1);
	if (bonus_is_blocking_cell(game, map_x, map_y))
		return (1);
	return (0);
}

static void	draw_sky(t_game *game)
{
	int	x;
	int	y;
	int	color;

	color = game->config.ceiling.hex;
	y = 0;
	while (y < WIN_H / 2)
	{
		x = 0;
		while (x < WIN_W)
		{
			put_pixel_to_frame(game, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_background(t_game *game)
{
	draw_sky(game);
	draw_floor_perspective(game);
}

t_texture	*select_wall_texture(t_game *game, t_ray_hit *hit)
{
	t_texture	*tex;

	tex = bonus_select_texture(game, hit);
	if (tex)
		return (tex);
	if (hit->side == HIT_X)
	{
		if (hit->ray_x > 0.0)
			return (&game->wall_we_tex);
		return (&game->wall_ea_tex);
	}
	if (hit->ray_y > 0.0)
		return (&game->wall_no_tex);
	return (&game->wall_so_tex);
}

void	draw_3d_view(t_game *game)
{
	int			x;
	double		ray_angle;
	t_ray_hit	hit;
	double		corrected_dist;

	x = 0;
	while (x < WIN_W)
	{
		ray_angle = game->player->angle - (FOV_RAD / 2.0) + ((double)x
				/ (double)WIN_W) * FOV_RAD;
		cast_ray(game, ray_angle, &hit);
		corrected_dist = get_corrected_dist(game, ray_angle, hit.dist);
		if (hit.is_door)
			draw_behind_door(game, x, ray_angle, &hit);
		game->zbuffer[x] = corrected_dist;
		draw_wall_column(game, x, &hit, corrected_dist);
		x++;
	}
}
