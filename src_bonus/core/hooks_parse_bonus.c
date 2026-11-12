/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_parse_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msingh <msingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 12:00:00 by assistant         #+#    #+#             */
/*   Updated: 2026/06/15 16:46:16 by msingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	bonus_is_map_start(char *line)
{
	return (*line == 'D' || *line == 'O');
}

int	bonus_is_map_char(char c)
{
	return (c == 'D' || c == 'O' || c == 'B');
}

int	bonus_is_walkable(char c)
{
	return (c == 'D' || c == 'O' || c == 'B');
}

int	is_transparent(int color)
{
	if (color == 0 || color == (int)0xFF000000)
		return (1);
	return (0);
}
