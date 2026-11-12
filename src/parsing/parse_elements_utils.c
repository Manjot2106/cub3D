/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assistant <assistant@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 12:00:00 by assistant         #+#    #+#             */
/*   Updated: 2026/06/15 12:00:00 by assistant        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_texture_identifier(char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0 && ft_isspace(line[2]))
		return (1);
	if (ft_strncmp(line, "SO", 2) == 0 && ft_isspace(line[2]))
		return (1);
	if (ft_strncmp(line, "WE", 2) == 0 && ft_isspace(line[2]))
		return (1);
	if (ft_strncmp(line, "EA", 2) == 0 && ft_isspace(line[2]))
		return (1);
	return (0);
}
