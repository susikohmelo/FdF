/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertice_rotations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljylhank <ljylhank@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:36:27 by ljylhank          #+#    #+#             */
/*   Updated: 2024/12/06 16:06:38 by ljylhank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static inline void	vert_rotate_x(int *y, int *z, double angle)
{
	double	y_dbl;
	double	z_dbl;

	y_dbl = (double) *y;
	z_dbl = (double) *z;
	*y = round(y_dbl * cos(angle) - z_dbl * sin(angle));
	*z = round(y_dbl * sin(angle) + z_dbl * cos(angle));
}

static inline void	vert_rotate_y(int *x, int *z, double angle)
{
	double	x_dbl;
	double	z_dbl;

	x_dbl = (double) *x;
	z_dbl = (double) *z;
	*x = round(x_dbl * cos(angle) + z_dbl * sin(angle));
	*z = round(x_dbl * -sin(angle) + z_dbl * cos(angle));
}

static inline void	vert_rotate_z(int *x, int *y, double angle)
{
	double	x_dbl;
	double	y_dbl;

	x_dbl = (double) *x;
	y_dbl = (double) *y;
	*x = round(x_dbl * cos(angle) - y_dbl * sin(angle));
	*y = round(x_dbl * sin(angle) + y_dbl * cos(angle));
}

// [ Move position of vertices on the screen ]
void	move_verts_to_worldpos(t_object *obj)
{
	int	i;

	i = 0;
	while (i < obj->arr_len)
	{
		obj->verts[i].x += obj->worldpos[0];
		obj->verts[i].y += obj->worldpos[1];
		i++;
	}
}

// [ Rotate all vertices to given new angle ]
void	rotate_verts(t_object *obj, double ang_x, double ang_y, double ang_z)
{
	int	i;

	i = 0;
	// Angles to radians conversion
	ang_x *= 0.01745;
	ang_y *= 0.01745;
	ang_z *= 0.01745;
	while (i < obj->arr_len)
	{
		vert_rotate_x(&(obj->verts[i].y), &(obj->verts[i].z), ang_x);
		vert_rotate_y(&(obj->verts[i].x), &(obj->verts[i].z), ang_y);
		vert_rotate_z(&(obj->verts[i].x), &(obj->verts[i].y), ang_z);
		i++;
	}
}
