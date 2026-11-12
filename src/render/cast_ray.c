/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msingh <msingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 11:13:01 by akaddo            #+#    #+#             */
/*   Updated: 2026/06/18 13:36:19 by msingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_steps(t_game *game, t_raycast *ray)
{
	if (ray->ray_x < 0.0)
	{
		ray->step_x = -1;
		ray->side_x = (game->player->pos_x - (double)ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = ((double)(ray->map_x + 1) - game->player->pos_x)
			* ray->delta_x;
	}
	if (ray->ray_y < 0.0)
	{
		ray->step_y = -1;
		ray->side_y = (game->player->pos_y - (double)ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = ((double)(ray->map_y + 1) - game->player->pos_y)
			* ray->delta_y;
	}
}

static void	step_ray(t_raycast *ray, t_ray_hit *hit)
{
	if (ray->side_x < ray->side_y)
	{
		ray->side_x += ray->delta_x;
		ray->map_x += ray->step_x;
		hit->side = HIT_X;
	}
	else
	{
		ray->side_y += ray->delta_y;
		ray->map_y += ray->step_y;
		hit->side = HIT_Y;
	}
}

static void	perform_dda(t_game *game, t_raycast *ray, t_ray_hit *hit,
		t_ray_hit *skip)
{
	while (1)
	{
		step_ray(ray, hit);
		if (skip && ray->map_x == skip->map_x && ray->map_y == skip->map_y)
			continue ;
		if (get_door(game, ray->map_x, ray->map_y))
		{
			if (try_hit_door(game, ray, hit))
				break ;
			continue ;
		}
		if (is_wall_cell(game, ray->map_x, ray->map_y))
		{
			hit->map_x = ray->map_x;
			hit->map_y = ray->map_y;
			break ;
		}
	}
}

static void	calculate_hit(t_game *game, t_raycast *ray, t_ray_hit *hit)
{
	if (hit->is_door)
		return ;
	if (hit->side == HIT_X)
		hit->dist = (ray->map_x - game->player->pos_x + (1 - ray->step_x) / 2.0)
			/ ray->ray_x;
	else
		hit->dist = (ray->map_y - game->player->pos_y + (1 - ray->step_y) / 2.0)
			/ ray->ray_y;
	if (hit->dist < 0.0001)
		hit->dist = 0.0001;
	if (hit->side == HIT_X)
		hit->wall_x = game->player->pos_y + hit->dist * ray->ray_y;
	else
		hit->wall_x = game->player->pos_x + hit->dist * ray->ray_x;
	hit->wall_x -= floor(hit->wall_x);
	hit->ray_x = ray->ray_x;
	hit->ray_y = ray->ray_y;
}

void	cast_ray_with_skip(t_game *game, double angle, t_ray_hit *hit,
		t_ray_hit *skip)
{
	t_raycast	ray;

	hit->is_door = 0;
	init_ray(game, angle, &ray);
	init_steps(game, &ray);
	perform_dda(game, &ray, hit, skip);
	calculate_hit(game, &ray, hit);
}
