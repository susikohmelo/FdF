/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljylhank <ljylhank@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:41:59 by ljylhank          #+#    #+#             */
/*   Updated: 2024/12/09 16:04:11 by ljylhank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include "key_codes.h"
# include "editable_macros.h"
# include "../minilibx-linux/mlx.h"
# include "libft/libft.h"

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		b_per_pxl;
	int		line_len;
	int		endian;
}		t_img_data;

// [ 3D vertice/vector ]
// Y_color is used as a duplicate of Y that isn't changed by rotation.
// This is used to assign the height based color during the line draw.
typedef struct s_vector3
{
	int	x;
	int	y;
	int	z;
	int	y_color;
}		t_vector3;

// [ Data related to the 3D map object ]
// og_verts is the original unedited coordinates of the object.
// verts is a temporary set copied and transformed every frame.
typedef struct s_object
{
	t_vector3	*og_verts;
	t_vector3	*verts;
	int			*int_arr;
	int			arr_width;
	int			arr_len;
	int			scale;
	float		height_scale;
	int			worldpos[2];
}		t_object;

// [ All the data required to update the model & frame ]
typedef struct s_frameinfo
{
	void		*mlx;
	void		*wind;
	void		*img;
	double		angles[3];
	char		autospin[3];
	t_object	*obj;
}		t_frameinfo;

int				gradient(t_vector3 *v1, t_vector3 *v2, int delta, int progress);
unsigned char	get_val_t(int trgb);
unsigned char	get_val_r(int trgb);
unsigned char	get_val_g(int trgb);
unsigned char	get_val_b(int trgb);
int				new_trgb(unsigned char t, unsigned char r,
					unsigned char g, unsigned char b);

void			img_pxl_put(t_img_data *data, int x, int y, int color);
void			img_drawline(t_img_data *data, t_vector3 v1, t_vector3 v2);

void			display_object(t_img_data *data, t_object *obj);
int				render_frame(t_frameinfo *f);

void			move_verts_to_worldpos(t_object *obj);
void			rotate_verts(t_object *obj, double ang_x, double ang_y,
					double ang_z);

t_vector3		*ints_to_vectors(t_object *obj);
void			parse_map(char *filename, int *width, int *len, int **map);

int				key_down(int keycode, t_frameinfo *f);
int				check_perspective(int keycode, t_frameinfo *f);
int				exit_fdf(t_frameinfo *f);
#endif
