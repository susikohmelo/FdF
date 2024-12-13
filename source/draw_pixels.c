/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljylhank <ljylhank@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:59:08 by ljylhank          #+#    #+#             */
/*   Updated: 2024/12/09 14:22:13 by ljylhank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// [ Puts a single pixel onto an image ]
void	img_pxl_put(t_img_data *data, int x, int y, int color)
{
	char	*offset;

	if (x < 0 || y < 0 || x > WIND_X || y > WIND_Y)
		return ;
	offset = data->addr + (y * data->line_len + x *(data->b_per_pxl / 8));
	*(unsigned int *) offset = color;
}

void	swap_vectors(t_vector3 *v1, t_vector3 *v2)
{
	t_vector3	temp;

	temp = *v1;
	*v1 = *v2;
	*v2 = temp;
}

// [ Draw line that is more vertical than horizontal ]
// This is the same as drawline_h but iterates upwards instead of to the right.
static inline void	drawline_v(t_img_data *data, t_vector3 *v1, t_vector3 *v2)
{
	int		i;
	int		x;
	int		dy;
	int		dx;
	int		incr;

	incr = 1;
	if (v1->y > v2->y)
		swap_vectors(v1, v2);
	dx = v2->x - v1->x;
	dy = v2->y - v1->y;
	if (v1->x > v2->x)
		incr = -1;
	dx *= incr;
	x = 0;
	i = 0;
	while (i < dy)
	{
		img_pxl_put(data, v1->x + x * incr, v1->y + i, gradient(v1, v2, dy, i));
		if (2 * dx * i - 2 * dy * x + dy >= 0)
			x++;
		i++;
	}
}

// I'm using my own version of Bresanham's line algorithm.
//
// We move pixel by pixel to the right (X) and then check what our Y should be.
// The pixels Y is decided by if the slope (delta y / delta x * current x) is
// closer to the pixel we are currently on (Y) or the one below us (Y + 1).
//
// [ Draw line that is more horizontal than vertical ]
static inline void	drawline_h(t_img_data *data, t_vector3 *v1, t_vector3 *v2)
{
	int		i;
	int		y;
	int		dy;
	int		dx;
	int		incr;

	incr = 1;
	if (v1->x > v2->x)
		swap_vectors(v1, v2);
	dx = v2->x - v1->x;
	dy = v2->y - v1->y;
	if (v1->y > v2->y)
		incr = -1;
	dy *= incr;
	y = 0;
	i = 0;
	while (i < dx)
	{
		img_pxl_put(data, v1->x + i, v1->y + y * incr, gradient(v1, v2, dx, i));
		// This is whee we choose if we want to iterate a pixel downwards.
		// Basic algebra was used to simplify the equation to get rid of floats
		if (2 * dy * i - 2 * dx * y + dx >= 0)
			y++;
		i++;
	}
}

// [ Draws a line between two vectors ]
// Function used is based on which direction is longer (horizontal or vertical)
void	img_drawline(t_img_data *data, t_vector3 v1, t_vector3 v2)
{
	int	dx;
	int	dy;

	dx = v2.x - v1.x;
	dy = v2.y - v1.y;
	if (dx < 0)
		dx *= -1;
	if (dy < 0)
		dy *= -1;
	if (dx == 0 && dy == 0)
		return ;
	else if (dx > dy)
		drawline_h(data, &v1, &v2);
	else
		drawline_v(data, &v1, &v2);
}
