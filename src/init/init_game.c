/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msingh <msingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 11:30:47 by msingh            #+#    #+#             */
/*   Updated: 2026/06/15 16:45:59 by msingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game)
{
	if (!game)
		return ;
	if (!game->map)
	{
		game->map_x = 0;
		game->map_y = 0;
		game->map_row = 0;
		game->map_cols = 0;
		game->map_max_x = 0;
		game->map_max_y = 0;
		game->map_pos = 0;
	}
	game->mlx = NULL;
	game->player = NULL;
}

void	init_ray(t_game *game, double angle, t_raycast *ray)
{
	ray->ray_x = cos(angle);
	ray->ray_y = sin(angle);
	ray->map_x = (int)game->player->pos_x;
	ray->map_y = (int)game->player->pos_y;
	ray->delta_x = 1e30;
	ray->delta_y = 1e30;
	if (fabs(ray->ray_x) > 1e-8)
		ray->delta_x = fabs(1.0 / ray->ray_x);
	if (fabs(ray->ray_y) > 1e-8)
		ray->delta_y = fabs(1.0 / ray->ray_y);
}
