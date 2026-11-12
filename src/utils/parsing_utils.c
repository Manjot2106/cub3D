/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddo <akaddo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:54:17 by akaddo            #+#    #+#             */
/*   Updated: 2026/06/11 16:01:56 by akaddo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*skip_space(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

void	trim_end(char *str)
{
	int	len;

	len = ft_strlen(str);
	while (len > 0 && ft_isspace(str[len - 1]))
	{
		str[len - 1] = '\0';
		len--;
	}
}

int	is_number(char *str)
{
	int	i;

	while (ft_isspace(*str))
		str++;
	if (*str == '\0')
		return (0);
	i = 0;
	while (str[i] && !ft_isspace(str[i]))
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	while (ft_isspace(str[i]))
		i++;
	return (str[i] == '\0');
}

char	*get_value(char *line, int n)
{
	line += n;
	return (ft_strdup(skip_space(line)));
}

int	err_msg(char *path, char *message)
{
	ft_putstr_fd("Error", 2);
	if (path)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(path, 2);
	}
	if (message)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(message, 2);
	}
	ft_putstr_fd("\n", 2);
	return (1);
}
