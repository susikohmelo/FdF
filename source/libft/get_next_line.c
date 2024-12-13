/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljylhank <ljylhank@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:27:09 by ljylhank          #+#    #+#             */
/*   Updated: 2024/11/19 13:39:45 by ljylhank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline int	join_leftovers_to_buffer(char *leftovers, char **buffer)
{
	char	*temp;
	int		i;
	int		i2;

	if (!(*leftovers))
		return (1);
	i = 0;
	while (leftovers[i])
		if (leftovers[i++] == '\n')
			break ;
	i2 = 0;
	while ((*buffer)[i2])
		i2++;
	temp = malloc((i + i2 + 1) * sizeof(char));
	if (!temp)
		return (0);
	ft_setlength_cpy(temp, leftovers, i + 1);
	ft_setlength_cpy(temp + i, *buffer, i2 + 1);
	free(*buffer);
	*buffer = temp;
	return (1);
}

static inline int	getline_and_store_leftovers(char *leftovers, char **buffer)
{
	char	*temp;
	int		i;

	i = 0;
	while ((*buffer)[i])
		if ((*buffer)[i++] == '\n')
			break ;
	temp = malloc((i + 1) * sizeof(char));
	if (!temp)
		return (0);
	ft_setlength_cpy(temp, *buffer, i + 1);
	if (!join_leftovers_to_buffer(leftovers, &temp))
	{
		free(temp);
		return (0);
	}
	fill_with_zeroes(leftovers, BUFFER_SIZE + 1);
	while ((*buffer)[i])
		*leftovers++ = (*buffer)[i++];
	free(*buffer);
	*buffer = temp;
	return (1);
}

static inline int	leftovers_has_nl(char *leftovers, char **buffer)
{
	int	i;

	if (!leftovers)
		return (0);
	i = 0;
	while (leftovers[i])
	{
		if (leftovers[i] == '\n')
			break ;
		i++;
	}
	if (leftovers[i] == '\n')
	{
		*buffer = ft_strdup(leftovers);
		if (!(*buffer))
			return (1);
		fill_with_zeroes(leftovers, BUFFER_SIZE + 1);
		getline_and_store_leftovers(leftovers, buffer);
		return (1);
	}
	return (0);
}

static inline int	read_file_until_nl(int fd, char **buffer)
{
	int	r_return;
	int	b_read;
	int	nl_found;

	r_return = 1;
	b_read = 0;
	nl_found = -1;
	*buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!(*buffer))
		return (0);
	fill_with_zeroes(*buffer, BUFFER_SIZE + 1);
	while (nl_found == -1 && r_return > 0)
	{
		if (!allocate_more_buffer(buffer))
			return (0);
		r_return = read(fd, *buffer + b_read, BUFFER_SIZE);
		nl_found = ft_find_charpos(*buffer + b_read, '\n');
		b_read += r_return;
	}
	if (r_return == -1)
	{
		free(*buffer);
		return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	leftovers[BUFFER_SIZE + 1];
	char		*buffer;

	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (leftovers_has_nl(leftovers, &buffer))
		return (buffer);
	if (!read_file_until_nl(fd, &buffer))
	{
		fill_with_zeroes(leftovers, BUFFER_SIZE + 1);
		return (NULL);
	}
	if (!getline_and_store_leftovers(leftovers, &buffer))
	{
		free(buffer);
		return (NULL);
	}
	if (*buffer == '\0')
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}
