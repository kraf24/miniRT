/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:41:40 by gpinchuk          #+#    #+#             */
/*   Updated: 2023/01/07 14:59:22 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
#define VECTOR_H

typedef struct  s_p3
{
	float	x;
	float	y;
	float	z;
}				t_p3;

t_p3	_norm(t_p3 vec);
float	_lenth(t_p3 vec);
float	_lenth_sq(t_p3 vec);
t_p3	_substruct(t_p3 vec1, t_p3 vec2);
t_p3	new_vec(float x, float y, float z);
t_p3	_multy(t_p3 vec1, float i);
float	_dot(t_p3 vec1, t_p3 vec2);
t_p3	_cross(t_p3 a, t_p3 b);
t_p3	_add(t_p3 vec1, t_p3 vec2);
float		distance(t_p3 p1, t_p3 p2);

#endif