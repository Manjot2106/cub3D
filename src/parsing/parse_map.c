/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msingh <msingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 14:35:03 by akaddo            #+#    #+#             */
/*   Updated: 2026/06/18 13:32:19 by msingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_line_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

static int	is_local_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == 'D' || c == 'B' || c == 'O');
}

static int	is_map_line(char *line)
{
	int	i;
	int	has_content;

	if (is_line_empty(line))
		return (0);
	i = 0;
	has_content = 0;
	while (line[i] && line[i] != '\n' && line[i] != '\r')
	{
		if (!is_local_map_char(line[i]))
			return (0);
		if (line[i] != ' ')
			has_content = 1;
		i++;
	}
	return (has_content);
}

int	find_map_start(char **file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (is_map_line(file[i]))
			return (i);
		i++;
	}
	return (-1);
}

int	check_map_is_last(char **file, int start)
{
	int	i;

	if (start < 0)
		return (1);
	i = start;
	while (file[i])
	{
		if (is_line_empty(file[i]) || !is_map_line(file[i]))
			return (1);
		i++;
	}
	return (0);
}
