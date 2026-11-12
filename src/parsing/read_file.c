/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddo <akaddo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 18:52:13 by akaddo            #+#    #+#             */
/*   Updated: 2026/06/10 19:02:34 by akaddo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	handle_append_error(char **file, char *line, int fd)
{
	free(line);
	free_map_lines(file);
	close(fd);
	return (1);
}

char	**append_line(char **lines, int count, char *line)
{
	char	**new_line;
	int		i;

	new_line = malloc(sizeof(char *) * (count + 2));
	if (!new_line)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_line[i] = lines[i];
		i++;
	}
	new_line[count] = ft_strdup(line);
	if (!new_line[count])
	{
		free(new_line);
		return (NULL);
	}
	new_line[count + 1] = NULL;
	free(lines);
	return (new_line);
}

char	**read_file(char *path)
{
	int			fd;
	char		**file;
	t_reader	r;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	file = NULL;
	r.count = 0;
	r.line = get_next_line(fd);
	while (r.line)
	{
		r.tmp = append_line(file, r.count, r.line);
		if (!r.tmp)
			return (handle_append_error(file, r.line, fd), NULL);
		file = r.tmp;
		r.count++;
		free(r.line);
		r.line = get_next_line(fd);
	}
	close(fd);
	return (file);
}
