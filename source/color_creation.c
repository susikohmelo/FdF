/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljylhank <ljylhank@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:01:19 by ljylhank          #+#    #+#             */
/*   Updated: 2024/12/04 14:25:06 by ljylhank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// 4 bytes - transparency, red, green and blue - are what form colors in libx.
//
// Since RGB values range from 0 to 255 this data fits perfectly into an int.
// Usually bitshift is used to do this, but you can also convert a 4 byte array
// into an integer, which I think makes assigning more intuitive.
//
// [ Create a new color from TRGB values ]
int	new_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	unsigned char	trgb[4];

	trgb[3] = t;
	trgb[2] = r;
	trgb[1] = g;
	trgb[0] = b;
	return (*(int *)(trgb));
}

// The same trick is used in reverse,
// we can traverse through the integer as if it were a character array. 
unsigned char	get_val_t(int trgb)
{
	return (((unsigned char *)&trgb)[3]);
}

unsigned char	get_val_r(int trgb)
{
	return (((unsigned char *)&trgb)[2]);
}

unsigned char	get_val_g(int trgb)
{
	return (((unsigned char *)&trgb)[1]);
}

unsigned char	get_val_b(int trgb)
{
	return (((unsigned char *)&trgb)[0]);
}
