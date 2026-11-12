/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddo <akaddo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 12:49:26 by akaddo            #+#    #+#             */
/*   Updated: 2026/06/10 18:59:02 by akaddo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_to_frame(t_game *game, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return ;
	pixel = game->frame_tex.addr + (y * game->frame_tex.line_len) + (x
			* (game->frame_tex.bpp / 8));
	*(unsigned int *)pixel = (unsigned int)color;
}

int	get_texture_pixel(t_texture *tex, int x, int y)
{
	char	*pixel;

	if (!tex || !tex->addr || tex->width <= 0 || tex->height <= 0)
		return (0xAAAAAA);
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= tex->width)
		x = tex->width - 1;
	if (y >= tex->height)
		y = tex->height - 1;
	pixel = tex->addr + (y * tex->line_len) + (x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}

int	darken_color(int color)
{
	return ((color & 0xFEFEFE) >> 1);
}
