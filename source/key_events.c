/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljylhank <ljylhank@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:31:08 by ljylhank          #+#    #+#             */
/*   Updated: 2024/12/09 17:35:41 by ljylhank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// [ Update object size if corresponding key is pressed ]
static inline char	check_size_keys(int keycode, t_frameinfo *f)
{
	int	size_amount;

	size_amount = 1;
	if (keycode == KEY_PLUS)
	{
		f->obj->scale += size_amount;
		free(f->obj->og_verts);
		f->obj->og_verts = ints_to_vectors(f->obj);
		if (!(f->obj->og_verts))
			return (-1);
		return (0);
	}
	else if (keycode == KEY_MINUS)
	{
		f->obj->scale -= size_amount;
		free(f->obj->og_verts);
		f->obj->og_verts = ints_to_vectors(f->obj);
		if (!(f->obj->og_verts))
			return (-1);
		return (0);
	}
	else
		return (0);
	return (1);
}

// [ Update object position if corresponding key is pressed ]
static inline char	check_move_keys(int keycode, t_frameinfo *f)
{
	int	move_amount;

	move_amount = 7;
	if (keycode == KEY_ARROW_R)
		f->obj->worldpos[0] += move_amount;
	else if (keycode == KEY_ARROW_L)
		f->obj->worldpos[0] -= move_amount;
	else if (keycode == KEY_ARROW_U)
		f->obj->worldpos[1] -= move_amount;
	else if (keycode == KEY_ARROW_D)
		f->obj->worldpos[1] += move_amount;
	else
		return (0);
	return (1);
}

// [ Update object rotation if corresponding key is pressed ]
static inline char	check_rotation_keys(int keycode, t_frameinfo *f)
{
	float	angle_amount;

	angle_amount = 1;
	if (keycode == KEY_Q)
		f->angles[0] += angle_amount;
	else if (keycode == KEY_A)
		f->angles[0] -= angle_amount;
	else if (keycode == KEY_W)
		f->angles[1] += angle_amount;
	else if (keycode == KEY_S)
		f->angles[1] -= angle_amount;
	else if (keycode == KEY_E)
		f->angles[2] += angle_amount;
	else if (keycode == KEY_D)
		f->angles[2] -= angle_amount;
	else
		return (0);
	return (1);
}

// [ Turn autospin on/off if corresponding key is pressed ]
static inline int	check_autospin(int keycode, t_frameinfo *f)
{
	if (keycode == KEY_1)
	{
		if (f->autospin[0])
			f->autospin[0] = 0;
		else
			f->autospin[0] = 1;
	}
	else if (keycode == KEY_2)
	{
		if (f->autospin[1])
			f->autospin[1] = 0;
		else
			f->autospin[1] = 1;
	}
	else if (keycode == KEY_3)
	{
		if (f->autospin[2])
			f->autospin[2] = 0;
		else
			f->autospin[2] = 1;
	}
	else
		return (0);
	return (1);
}

// [ Check if the pressed key is any of the ones we're looking out for ]
int	key_down(int keycode, t_frameinfo *f)
{
	char	size_return;

	size_return = check_size_keys(keycode, f);
	if (size_return > 0)
		return (0);
	if (size_return < 0)
		return (1);
	if (check_rotation_keys(keycode, f))
		return (0);
	if (check_move_keys(keycode, f))
		return (0);
	if (check_autospin(keycode, f))
		return (0);
	if (check_perspective(keycode, f))
		return (0);
	else if (keycode == KEY_ESC)
	{
		exit_fdf(f);
		return (0);
	}
	return (0);
}
