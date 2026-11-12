/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddo <akaddo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 20:36:48 by akaddo            #+#    #+#             */
/*   Updated: 2026/06/11 14:53:57 by akaddo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_required(t_check *check)
{
	if (check->no != 1 || check->so != 1 || check->we != 1 || check->ea != 1
		|| check->f != 1 || check->c != 1)
		return (1);
	return (0);
}

static int	is_map_start(char *line)
{
	if (*line == '1' || *line == '0' || bonus_is_map_start(line))
		return (1);
	if (*line == 'N' && line[1] != 'O')
		return (1);
	if (*line == 'S' && line[1] != 'O')
		return (1);
	if (*line == 'W' && line[1] != 'E' && line[1] != 'A')
		return (1);
	if (*line == 'E' && line[1] != 'A')
		return (1);
	return (0);
}

static int	parse_line(char *line, t_game *game, t_check *check)
{
	if (is_texture_identifier(line))
		return (parse_texture(line, game, check));
	if (is_color_identifier(line))
		return (parse_color(line, game, check));
	game->error_msg = "Unknown configuration identifier";
	return (1);
}

static int	parse_config_lines(t_game *game, t_check *check)
{
	char	*line;
	int		i;

	i = 0;
	while (game->file_lines[i])
	{
		line = skip_space(game->file_lines[i]);
		if (*line == '\0' || *line == '\n')
		{
			i++;
			continue ;
		}
		if (is_map_start(line))
			break ;
		if (parse_line(line, game, check))
			return (1);
		i++;
	}
	return (0);
}

int	parse_elements(t_game *game)
{
	t_check	check;

	ft_bzero(&check, sizeof(t_check));
	if (parse_config_lines(game, &check))
		return (1);
	if (check_required(&check))
		return (game->error_msg = "Missing configuration element", 1);
	if (validate_textures(game))
		return (game->error_msg = "Texture file not found", 1);
	return (0);
}
