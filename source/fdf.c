/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljylhank <ljylhank@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:53:59 by ljylhank          #+#    #+#             */
/*   Updated: 2024/12/09 17:33:24 by ljylhank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// [ Free allocated memory and exit program ]
// Returning 0 lets us do a clean single line exit "return (exit_fdf(f));"
int	exit_fdf(t_frameinfo *f)
{
	if (f->obj->int_arr)
		free(f->obj->int_arr);
	if (f->obj->og_verts)
		free(f->obj->og_verts);
	if (f->obj->verts)
		free(f->obj->verts);
	if (f->img)
		mlx_destroy_image(f->mlx, f->img);
	mlx_destroy_window(f->mlx, f->wind);
	exit (0);
}

// [ Convert int array into 3D vectors ]
t_vector3	*ints_to_vectors(t_object *obj)
{
	t_vector3	*vector_arr;
	int			i;
	int			len;
	int			width;
	int			offset[2];

	len = obj->arr_len;
	width = obj->arr_width;
	offset[0] = width / 2 * -1;
	offset[1] = len / width / 2 * -1;
	vector_arr = malloc(len * sizeof(t_vector3));
	if (!vector_arr)
		return (0);
	i = 0;
	while (i < len)
	{
		vector_arr[i].x = i % width * obj->scale + offset[0] * obj->scale;
		vector_arr[i].y = obj->int_arr[i] * obj->scale * obj->height_scale;
		vector_arr[i].z = i / width * obj->scale + offset[1] * obj->scale;
		vector_arr[i].y_color = obj->int_arr[i];
		i++;
	}
	return (vector_arr);
}

// [ Initialize default values for object struct ]
static inline void	initialize_obj_and_frame(t_object *obj, t_frameinfo *frame)
{
	obj->int_arr = 0;
	obj->arr_len = 0;
	obj->int_arr = 0;
	obj->scale = OBJ_SCALE;
	obj->height_scale = RELATIVE_H_SCALE;
	obj->worldpos[0] = WIND_X / 2;
	obj->worldpos[1] = WIND_Y / 2;
	frame->mlx = mlx_init();
	frame->wind = mlx_new_window(frame->mlx, WIND_X, WIND_Y, "FdF");
	frame->angles[0] = 225;
	frame->angles[1] = 35;
	frame->angles[2] = 30;
	frame->autospin[0] = 0;
	frame->autospin[1] = 0;
	frame->autospin[2] = 0;
	frame->img = 0;
	frame->obj = obj;
}

int	main(int argc, char **argv)
{
	t_frameinfo	frame;
	t_object	obj;

	if (argc != 2)
		return (0);
	initialize_obj_and_frame(&obj, &frame);
	parse_map(argv[1], &(obj.arr_width), &(obj.arr_len), &(obj.int_arr));
	if (!obj.int_arr)
		return (1);
	obj.og_verts = ints_to_vectors(&obj);
	if (!obj.og_verts)
		return (0);
	obj.verts = ints_to_vectors(&obj);
	if (!obj.verts)
		return (0);
	mlx_hook(frame.wind, 2, 1L << 0, key_down, &frame);
	mlx_hook(frame.wind, 17, 0L, exit_fdf, &frame);
	mlx_loop_hook(frame.mlx, render_frame, &frame);
	mlx_loop(frame.mlx);
	return (0);
}
