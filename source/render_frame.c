/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljylhank <ljylhank@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:09:10 by ljylhank          #+#    #+#             */
/*   Updated: 2024/12/09 17:02:38 by ljylhank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Copy unchanged original vertices into a temporary set
static inline void	copy_ogverts_to_tempverts(t_object *obj)
{
	int	i;

	i = 0;
	while (i < obj->arr_len)
	{
		obj->verts[i] = obj->og_verts[i];
		i++;
	}
}

// [ Figure out which vertices to connect with lines and draw them ]
void	display_object(t_img_data *data, t_object *obj)
{
	int			i;
	t_vector3	*verts;

	i = 0;
	verts = obj->verts;
	while (i < obj->arr_len - 1)
	{
		if (i % obj->arr_width != obj->arr_width - 1)
			img_drawline(data, verts[i], verts[i + 1]);
		if (i + obj->arr_width < obj->arr_len)
			img_drawline(data, verts[i], verts[i + obj->arr_width]);
		i++;
	}
}

// [ Increases X/Y/Z rotation every frame if autospin is enabled ]
static inline void	autospin(t_frameinfo *f)
{
	if (f->autospin[0])
		f->angles[0] += AUTOSPIN_SPEED;
	if (f->autospin[1])
		f->angles[1] += AUTOSPIN_SPEED;
	if (f->autospin[2])
		f->angles[2] += AUTOSPIN_SPEED;
}

// [ Render frame & put it up on the window ]
// This is called every frame and it updates the rotation of
// the object and draws new lines between the vertices.
int	render_frame(t_frameinfo *f)
{
	t_img_data	img;

	copy_ogverts_to_tempverts(f->obj);
	if (f->img)
		mlx_destroy_image(f->mlx, f->img);
	img.img = mlx_new_image(f->mlx, WIND_X, WIND_Y);
	f->img = img.img;
	img.addr = mlx_get_data_addr(img.img, &img.b_per_pxl,
			&img.line_len, &img.endian);
	autospin(f);
	rotate_verts(f->obj, f->angles[0], f->angles[1], f->angles[2]);
	move_verts_to_worldpos(f->obj);
	display_object(&img, f->obj);
	mlx_put_image_to_window(f->mlx, f->wind, img.img, 0, 0);
	return (0);
}
