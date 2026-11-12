/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray_doors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msingh <msingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 15:00:00 by assistant         #+#    #+#             */
/*   Updated: 2026/06/18 10:05:00 by assistant        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	center_door_hit(double *local)
{
	double	width;

	if (*local < DOOR_HIT_MARGIN || *local > 1.0 - DOOR_HIT_MARGIN)
		return (0);
	width = 1.0 - (DOOR_HIT_MARGIN * 2.0);
	*local = (*local - DOOR_HIT_MARGIN) / width;
	return (1);
}

static int	hit_vertical_door(t_game *game, t_raycast *ray, t_ray_hit *hit,
		t_door *door)
{
	double	dist;
	double	local;

	if (fabs(ray->ray_x) < 1e-8)
		return (0);
	dist = ((double)door->x + 0.5 - game->player->pos_x) / ray->ray_x;
	if (dist < 0.0001)
		return (0);
	local = game->player->pos_y + dist * ray->ray_y - (double)door->y;
	if (!center_door_hit(&local))
		return (0);
	hit->dist = dist;
	hit->wall_x = local;
	hit->side = HIT_X;
	return (1);
}

static int	hit_horizontal_door(t_game *game, t_raycast *ray, t_ray_hit *hit,
		t_door *door)
{
	double	dist;
	double	local;

	if (fabs(ray->ray_y) < 1e-8)
		return (0);
	dist = ((double)door->y + 0.5 - game->player->pos_y) / ray->ray_y;
	if (dist < 0.0001)
		return (0);
	local = game->player->pos_x + dist * ray->ray_x - (double)door->x;
	if (!center_door_hit(&local))
		return (0);
	hit->dist = dist;
	hit->wall_x = local;
	hit->side = HIT_Y;
	return (1);
}

int	try_hit_door(t_game *game, t_raycast *ray, t_ray_hit *hit)
{
	t_door	*door;

	door = get_door(game, ray->map_x, ray->map_y);
	if (!door)
		return (0);
	if (is_door_vertical(game, door->x, door->y))
	{
		if (!hit_vertical_door(game, ray, hit, door))
			return (0);
	}
	else if (!hit_horizontal_door(game, ray, hit, door))
		return (0);
	hit->map_x = ray->map_x;
	hit->map_y = ray->map_y;
	hit->ray_x = ray->ray_x;
	hit->ray_y = ray->ray_y;
	hit->is_door = 1;
	return (1);
}
