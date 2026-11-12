/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddo <akaddo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 12:14:17 by akaddo            #+#    #+#             */
/*   Updated: 2026/06/11 15:08:36 by akaddo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	has_xpm_extension(char *path)
{
	int	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 5)
		return (0);
	return (ft_strncmp(path + len - 4, ".xpm", 4) == 0);
}

static int	set_texture(char **dst, int *count, char *line, int n)
{
	char	*value;

	if (*count != 0)
		return (1);
	value = get_value(line, n);
	if (!value || value[0] == '\0')
		return (free(value), 1);
	trim_end(value);
	if (!has_xpm_extension(value))
	{
		free(value);
		return (1);
	}
	*dst = value;
	(*count)++;
	return (0);
}

int	check_texture_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}

int	validate_textures(t_game *game)
{
	if (check_texture_file(game->config.north))
		return (1);
	if (check_texture_file(game->config.south))
		return (1);
	if (check_texture_file(game->config.east))
		return (1);
	if (check_texture_file(game->config.west))
		return (1);
	return (0);
}

int	parse_texture(char *line, t_game *game, t_check *check)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(line, "NO", 2) == 0 && ft_isspace(line[2]))
		ret = set_texture(&game->config.north, &check->no, line, 2);
	else if (ft_strncmp(line, "SO", 2) == 0 && ft_isspace(line[2]))
		ret = set_texture(&game->config.south, &check->so, line, 2);
	else if (ft_strncmp(line, "WE", 2) == 0 && ft_isspace(line[2]))
		ret = set_texture(&game->config.west, &check->we, line, 2);
	else if (ft_strncmp(line, "EA", 2) == 0 && ft_isspace(line[2]))
		ret = set_texture(&game->config.east, &check->ea, line, 2);
	if (ret)
		game->error_msg = "Invalid texture definition";
	return (ret);
}
