/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddo <akaddo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 12:43:35 by msingh            #+#    #+#             */
/*   Updated: 2026/06/09 14:32:59 by akaddo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_image_buffer(t_game *game)
{
	if (!game || !game->mlx || !game->mlx->mlx_ptr)
		return (1);
	game->frame_tex.img_ptr = mlx_new_image(game->mlx->mlx_ptr, WIN_W, WIN_H);
	if (!game->frame_tex.img_ptr)
		return (1);
	game->frame_tex.width = WIN_W;
	game->frame_tex.height = WIN_H;
	game->frame_tex.addr = mlx_get_data_addr(game->frame_tex.img_ptr,
			&game->frame_tex.bpp, &game->frame_tex.line_len,
			&game->frame_tex.endian);
	if (!game->frame_tex.addr)
	{
		mlx_destroy_image(game->mlx->mlx_ptr, game->frame_tex.img_ptr);
		game->frame_tex.img_ptr = NULL;
		return (1);
	}
	return (0);
}
