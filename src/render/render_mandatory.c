/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mandatory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msingh <msingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 18:49:12 by akaddo            #+#    #+#             */
/*   Updated: 2026/06/18 13:32:36 by msingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clear_frame(t_game *game)
{
	if (!game->frame_tex.addr || game->frame_tex.line_len <= 0)
		return ;
	ft_bzero(game->frame_tex.addr, game->frame_tex.line_len * WIN_H);
}

int	render_first_frame(t_game *game)
{
	if (!game || !game->mlx || !game->player || !game->map)
		return (1);
	if (!game->frame_tex.img_ptr || !game->frame_tex.addr)
		return (1);
	clear_frame(game);
	draw_background(game);
	draw_3d_view(game);
	draw_bonus_overlay(game);
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win_ptr,
		game->frame_tex.img_ptr, 0, 0);
	return (0);
}

double	get_corrected_dist(t_game *game, double ray_angle, double dist)
{
	double	corrected_dist;

	corrected_dist = dist * cos(ray_angle - game->player->angle);
	if (corrected_dist < 0.0001)
		corrected_dist = 0.0001;
	return (corrected_dist);
}

void	draw_behind_door(t_game *game, int x, double ray_angle,
		t_ray_hit *door_hit)
{
	t_ray_hit	behind;
	double		dist;

	cast_ray_skip_hit(game, ray_angle, &behind, door_hit);
	dist = get_corrected_dist(game, ray_angle, behind.dist);
	draw_wall_column(game, x, &behind, dist);
}
