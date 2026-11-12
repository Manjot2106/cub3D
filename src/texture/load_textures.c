/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddo <akaddo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 15:47:10 by akaddo            #+#    #+#             */
/*   Updated: 2026/06/15 12:00:00 by assistant        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_game_texture(t_game *game, t_texture *tex, char *path)
{
	int	w;
	int	h;

	w = 0;
	h = 0;
	if (!path)
		return (1);
	tex->img_ptr = mlx_xpm_file_to_image(game->mlx->mlx_ptr, path, &w, &h);
	if (!tex->img_ptr)
		return (1);
	tex->width = w;
	tex->height = h;
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->addr)
	{
		mlx_destroy_image(game->mlx->mlx_ptr, tex->img_ptr);
		tex->img_ptr = NULL;
		return (1);
	}
	return (0);
}

int	load_textures(t_game *game)
{
	if (!game || !game->mlx || !game->mlx->mlx_ptr)
		return (1);
	if (load_game_texture(game, &game->wall_no_tex, game->config.north) != 0)
		return (1);
	if (load_game_texture(game, &game->wall_so_tex, game->config.south) != 0)
		return (1);
	if (load_game_texture(game, &game->wall_we_tex, game->config.west) != 0)
		return (1);
	if (load_game_texture(game, &game->wall_ea_tex, game->config.east) != 0)
		return (1);
	if (load_bonus_textures(game) != 0)
		return (1);
	return (0);
}
