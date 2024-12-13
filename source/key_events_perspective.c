/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events_perspective.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljylhank <ljylhank@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:46:26 by ljylhank          #+#    #+#             */
/*   Updated: 2024/12/09 17:33:15 by ljylhank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// [ Switch between isometric and parallel perspective ]
int	check_perspective(int keycode, t_frameinfo *f)
{
	if (keycode == KEY_I)
	{
		f->angles[0] = 225;
		f->angles[1] = 35;
		f->angles[2] = 30;
	}
	else if (keycode == KEY_P)
	{
		f->angles[0] = -90;
		f->angles[1] = 0;
		f->angles[2] = 0;
	}
	else
		return (0);
	return (1);
}
