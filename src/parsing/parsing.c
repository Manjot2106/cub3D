/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddo <akaddo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 12:11:42 by msingh            #+#    #+#             */
/*   Updated: 2026/06/11 16:15:32 by akaddo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_cub_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5)
		return (1);
	if (ft_strncmp(path + len - 4, ".cub", 4) != 0)
		return (1);
	return (0);
}

static t_game	*init_parsing_game(char *map_path)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	ft_bzero(game, sizeof(t_game));
	game->file_lines = read_file(map_path);
	if (!game->file_lines)
	{
		free(game);
		err_msg(map_path, BAD_MAP_FILE_ERROR);
		return (NULL);
	}
	return (game);
}

static int	parse_game_data(t_game *game)
{
	if (parse_elements(game))
		return (1);
	if (extract_map(game))
		return (1);
	game->map_row = game->map_height;
	game->map_cols = game->map_width;
	if (validate_map(game))
		return (1);
	return (0);
}

t_game	*ft_parsing(char *map_path)
{
	t_game	*game;

	if (check_cub_extension(map_path))
		return (err_msg(map_path, "Invalid file extension"), NULL);
	game = init_parsing_game(map_path);
	if (!game)
		return (NULL);
	if (parse_game_data(game))
	{
		if (game->error_msg)
			err_msg(map_path, game->error_msg);
		free_game(game);
		return (NULL);
	}
	return (game);
}
