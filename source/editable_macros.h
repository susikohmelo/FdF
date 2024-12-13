/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editable_macros.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljylhank <ljylhank@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:39:31 by ljylhank          #+#    #+#             */
/*   Updated: 2024/12/09 18:35:06 by ljylhank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef EDITABLE_MACROS_H
# define EDITABLE_MACROS_H

// Launch window size x/y
# ifndef WIND_X
#  define WIND_X 1920
# endif
# ifndef WIND_Y
#  define WIND_Y 1920
# endif

// Color of vertices with height 0
# ifndef BASE_COLOR 
#  define BASE_COLOR 0x00FF0095
# endif
// Color of vertices above 0
# ifndef H_COLOR 
#  define H_COLOR 0x0000FFFF
# endif
// Color of vertices below 0
# ifndef L_COLOR 
#  define L_COLOR 0x00FA9F42
# endif

// Default size of the object.
// Scale = 1 is 1 pixel gaps between vertices.
# ifndef OBJ_SCALE 
#  define OBJ_SCALE 20
# endif
// How much 1 unit of height on the map is
// relative to the horizontal difference between vertices.
# ifndef RELATIVE_H_SCALE
#  define RELATIVE_H_SCALE 0.1
# endif

// Speed of the autospin key
# ifndef AUTOSPIN_SPEED
#  define AUTOSPIN_SPEED 0.7
# endif
// Speed of the rotation key
# ifndef ROTATE_SPEED
#  define ROTATE_SPEED 0.3
# endif
// Speed of the mvement key
# ifndef MOVE_SPEED
#  define MOVE_SPEED 1
# endif

#endif
