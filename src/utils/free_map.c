/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddo <akaddo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 12:12:50 by msingh            #+#    #+#             */
/*   Updated: 2026/06/15 12:00:00 by assistant        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map_lines(char **lines)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

static void	free_config(t_game *game)
{
	if (game->config.north)
		free(game->config.north);
	if (game->config.south)
		free(game->config.south);
	if (game->config.east)
		free(game->config.east);
	if (game->config.west)
		free(game->config.west);
}

static void	free_game_data(t_game *game)
{
	destroy_game_texture(game, &game->frame_tex);
	destroy_game_texture(game, &game->wall_tex);
	destroy_game_texture(game, &game->wall_no_tex);
	destroy_game_texture(game, &game->wall_so_tex);
	destroy_game_texture(game, &game->wall_we_tex);
	destroy_game_texture(game, &game->wall_ea_tex);
	destroy_game_texture(game, &game->ground_tex);
	free_bonus_data(game);
	if (game->map)
		free_map_lines(game->map);
	if (game->file_lines)
		free_map_lines(game->file_lines);
	if (game->player)
		free(game->player);
	free_config(game);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_game_data(game);
	if (game->mlx)
	{
		if (game->mlx->win_ptr)
			mlx_destroy_window(game->mlx->mlx_ptr, game->mlx->win_ptr);
		if (game->mlx->mlx_ptr)
		{
			mlx_destroy_display(game->mlx->mlx_ptr);
			free(game->mlx->mlx_ptr);
		}
		free(game->mlx);
	}
	free(game);
}

void	free_exit(t_game *game, int exit_code)
{
	free_game(game);
	exit(exit_code);
}
