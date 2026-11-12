/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_render_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msingh <msingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 15:00:00 by assistant         #+#    #+#             */
/*   Updated: 2026/06/17 15:00:00 by assistant        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clamp_sprite_screen(t_sprite_draw *d)
{
	if (d->start_y < 0)
		d->start_y = 0;
	if (d->end_y >= WIN_H)
		d->end_y = WIN_H - 1;
	if (d->start_x < 0)
		d->start_x = 0;
	if (d->end_x >= WIN_W)
		d->end_x = WIN_W - 1;
}

double	get_sprite_scale(t_sprite *sprite)
{
	(void)sprite;
	return (1.0);
}
