/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljylhank <ljylhank@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:00:54 by ljylhank          #+#    #+#             */
/*   Updated: 2024/12/09 14:24:06 by ljylhank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// P = percentage, ranges from 0 to 1.
// Returns new color that is a mix between c1 and c2
static inline int	mix_colors(int c1, int c2, float p)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = get_val_r(c1) * (1 - p) + get_val_r(c2) * p;
	g = get_val_g(c1) * (1 - p) + get_val_g(c2) * p;
	b = get_val_b(c1) * (1 - p) + get_val_b(c2) * p;
	return (new_trgb(0, r, g, b));
}

// Calculates what color should be used for this pixel of the line draw.
// Returned color is a mix between the 2 vertices based on their heights
int	gradient(t_vector3 *v1, t_vector3 *v2, int delta, int progress)
{
	float	percent;
	int		v1_clr;
	int		v2_clr;

	progress++;
	percent = (float) progress / (float) delta;
	if (v1->y_color > 0)
		v1_clr = H_COLOR;
	else if (v1->y_color < 0)
		v1_clr = L_COLOR;
	else
		v1_clr = BASE_COLOR;
	if (v2->y_color > 0)
		v2_clr = H_COLOR;
	else if (v2->y_color < 0)
		v2_clr = L_COLOR;
	else
		v2_clr = BASE_COLOR;
	return (mix_colors(v1_clr, v2_clr, percent));
}
