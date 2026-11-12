/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msingh <msingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 12:33:09 by akaddo            #+#    #+#             */
/*   Updated: 2026/06/11 16:42:00 by msingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*copy_map_line(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	return (ft_substr(line, 0, len));
}

static int	map_width(char **file, int start)
{
	int	i;
	int	len;
	int	max;

	i = start;
	max = 0;
	while (file[i])
	{
		len = ft_strlen(file[i]);
		if (len > 0 && file[i][len - 1] == '\n')
			len--;
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

static int	map_height(char **file, int start)
{
	int	i;

	i = start;
	while (file[i])
		i++;
	return (i - start);
}

static int	copy_map_lines(t_game *game, int start)
{
	int	i;

	i = 0;
	while (i < game->map_height)
	{
		game->map[i] = copy_map_line(game->file_lines[start + i]);
		if (!game->map[i])
		{
			free_map_lines(game->map);
			game->map = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

int	extract_map(t_game *game)
{
	int	start;

	start = find_map_start(game->file_lines);
	if (start == -1)
		return (game->error_msg = "Map section not found", 1);
	if (check_map_is_last(game->file_lines, start))
		return (game->error_msg = "Map must be the last element in file", 1);
	game->map_height = map_height(game->file_lines, start);
	game->map_width = map_width(game->file_lines, start);
	game->map = ft_calloc(game->map_height + 1, sizeof(char *));
	if (!game->map || copy_map_lines(game, start))
		return (game->error_msg = MAP_ERROR_MEMOIRE, 1);
	return (0);
}
