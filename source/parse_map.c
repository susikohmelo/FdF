/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljylhank <ljylhank@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:00:05 by ljylhank          #+#    #+#             */
/*   Updated: 2024/12/09 17:10:44 by ljylhank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

static inline int	add_space_to_map(int **map, int len, int amount)
{
	int	*new;
	int	i;

	new = malloc((len + amount) * sizeof(int));
	if (!new)
	{
		if (*map)
			free(*map);
		return (0);
	}
	i = 0;
	while (i < len)
	{
		new[i] = (*map)[i];
		i++;
	}
	if (*map)
		free(*map);
	*map = new;
	return (1);
}

static inline int	append_values(int **map, char *new, int *len, int width)
{
	int	i;

	i = 0;
	if (!add_space_to_map(map, *len, width))
		return (0);
	while (new[i])
	{
		while (new[i] && (!ft_isdigit(new[i]) && new[i] != '-'))
			i++;
		if (ft_isdigit(new[i]) || new[i] == '-')
		{
			(*map)[*len] = ft_atoi(new + i);
			(*len)++;
		}
		while (ft_isdigit(new[i]) || new[i] == '-')
			i++;
	}
	return (1);
}

static inline int	get_line_width(char *line)
{
	int	width;

	width = 0;
	while (*line)
	{
		if (ft_isdigit(*line) || *line == '-')
		{
			width++;
			while (ft_isdigit(*line) || *line == '-')
				line++;
		}
		else
			line++;
	}
	return (width);
}

// [ Parse input map and convert from char* to int* ]
void	parse_map(char *filename, int *width, int *len, int **map)
{
	int		fd;
	char	*gnl_return;
	int		first;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ;
	first = 1;
	while (first || gnl_return != 0)
	{
		gnl_return = get_next_line(fd);
		if (!gnl_return)
			break ;
		if (first)
		{
			first = 0;
			*width = get_line_width(gnl_return);
		}
		append_values(map, gnl_return, len, *width);
		free(gnl_return);
	}
	close(fd);
}
