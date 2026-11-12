/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assistant <assistant@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 12:00:00 by assistant         #+#    #+#             */
/*   Updated: 2026/06/15 12:00:00 by assistant        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_game_texture(t_game *game, t_texture *tex)
{
	if (!tex)
		return ;
	if (tex->img_ptr && game->mlx && game->mlx->mlx_ptr)
		mlx_destroy_image(game->mlx->mlx_ptr, tex->img_ptr);
	tex->img_ptr = NULL;
	tex->addr = NULL;
	tex->width = 0;
	tex->height = 0;
}
