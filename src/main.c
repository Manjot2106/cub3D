/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddo <akaddo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 11:10:49 by msingh            #+#    #+#             */
/*   Updated: 2026/06/11 14:19:15 by akaddo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		return (1);
	game = ft_parsing(av[1]);
	if (!game)
		return (1);
	init_game(game);
	init_mlx(game);
	if (create_image_buffer(game) != 0)
		return (free_game(game), 1);
	if (load_textures(game) != 0)
		return (free_game(game), 1);
	if (init_player_data(game) != 0)
		return (free_game(game), 1);
	if (setup_hooks(game) != 0)
		return (free_game(game), 1);
	if (render_first_frame(game) != 0)
		return (free_game(game), 1);
	mlx_loop(game->mlx->mlx_ptr);
	free_game(game);
	return (0);
}
