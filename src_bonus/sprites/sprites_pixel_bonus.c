/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_pixel_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msingh <msingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 15:00:00 by assistant         #+#    #+#             */
/*   Updated: 2026/06/18 13:30:36 by msingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_texture	*get_barrel_frame(t_game *game, t_sprite *sprite)
{
	int	frame;

	frame = 0;
	if (sprite->state == 1)
	{
		frame = 1 + (int)(sprite->anim * (BARREL_FRAME_COUNT - 1));
		if (frame >= BARREL_FRAME_COUNT)
			frame = BARREL_FRAME_COUNT - 1;
	}
	return (&game->barrel_frames[frame]);
}

int	get_sprite_pixel(t_game *game, t_sprite_draw *d, t_sprite *sprite,
		int pos[2])
{
	t_texture	*tex;
	int			tex_x;
	int			tex_y;
	int			color;

	if (sprite->state == 2)
		return (-1);
	tex = get_barrel_frame(game, sprite);
	if (!tex->addr)
		return (-1);
	tex_x = (int)(256 * (pos[0] - (-d->width / 2 + d->screen_x)) * tex->width
			/ d->width) / 256;
	tex_y = (((pos[1] * 256 - WIN_H * 128 + d->height * 128) * tex->height)
			/ d->height) / 256;
	color = get_texture_pixel(tex, tex_x, tex_y);
	if (!is_transparent(color))
		return (color);
	return (-1);
}
