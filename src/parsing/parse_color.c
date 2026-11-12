/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddo <akaddo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:20:24 by akaddo            #+#    #+#             */
/*   Updated: 2026/06/11 16:09:41 by akaddo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	color_to_hex(t_color *color)
{
	color->hex = (color->r << 16) | (color->g << 8) | color->b;
	return (0);
}

static int	fill_color(t_color *color, char **rgb)
{
	int		len;
	char	*r_str;
	char	*g_str;
	char	*b_str;

	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (1);
	len = ft_strlen(rgb[2]);
	if (len > 0 && rgb[2][len - 1] == '\n')
		rgb[2][len - 1] = '\0';
	r_str = skip_space(rgb[0]);
	g_str = skip_space(rgb[1]);
	b_str = skip_space(rgb[2]);
	if (!is_number(r_str) || !is_number(g_str) || !is_number(b_str))
		return (1);
	color->r = ft_atoi(r_str);
	color->g = ft_atoi(g_str);
	color->b = ft_atoi(b_str);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		return (1);
	return (color_to_hex(color));
}

static int	set_color(char *line, t_color *color)
{
	char	**rgb;
	int		err;

	line++;
	while (ft_isspace(*line))
		line++;
	rgb = ft_split(line, ',');
	if (!rgb)
		return (1);
	err = fill_color(color, rgb);
	free_map_lines(rgb);
	return (err);
}

int	is_color_identifier(char *line)
{
	return ((ft_strncmp(line, "F", 1) == 0 && ft_isspace(line[1]))
		|| (ft_strncmp(line, "C", 1) == 0 && ft_isspace(line[1])));
}

int	parse_color(char *line, t_game *game, t_check *check)
{
	if (ft_strncmp(line, "F", 1) == 0 && ft_isspace(line[1]))
	{
		if (check->f != 0)
			return (game->error_msg = "Floor color defined multiple times", 1);
		if (set_color(line, &game->config.floor))
			return (game->error_msg = RGB_ERROR, 1);
		check->f++;
		return (0);
	}
	if (ft_strncmp(line, "C", 1) == 0 && ft_isspace(line[1]))
	{
		if (check->c != 0)
			return (game->error_msg = "Ceiling color defined multiple times",
				1);
		if (set_color(line, &game->config.ceiling))
			return (game->error_msg = RGB_ERROR, 1);
		check->c++;
		return (0);
	}
	return (0);
}
