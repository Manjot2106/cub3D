/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msingh <msingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:23:23 by msingh            #+#    #+#             */
/*   Updated: 2026/06/18 13:23:36 by msingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_ray(t_game *game, double angle, t_ray_hit *hit)
{
	cast_ray_with_skip(game, angle, hit, NULL);
}

void	cast_ray_skip_hit(t_game *game, double angle, t_ray_hit *hit,
		t_ray_hit *skip)
{
	cast_ray_with_skip(game, angle, hit, skip);
}
