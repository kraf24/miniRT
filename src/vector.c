/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 18:12:38 by admin             #+#    #+#             */
/*   Updated: 2023/01/07 14:54:40 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_p3 new_vec(float x, float y, float z)
{
	t_p3 vec;
	// vec = (t_p3)malloc(sizeof(t_p3));
	// if (!vec)
	// 	fatal_error("Vector was not allocated");
	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

float _lenth(t_p3 vec)
{
	float ret;

	ret = sqrt((pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2)));
	return (ret);
}

// double		mod(t_p3 v)
// {
// 	return (sqrt(dot(v, v)));
// }

// t_p3		normalize(t_p3 p)
// {
// 	t_p3	nv;
// 	double	mod;

// 	mod = sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
// 	nv.x = p.x / mod;
// 	nv.y = p.y / mod;
// 	nv.z = p.z / mod;
// 	return (nv);
// }

float _lenth_sq(t_p3 vec)
{
	float ret;

	ret = (pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
	return (ret);
}

t_p3 _norm(t_p3 vec)
{
	t_p3	nv;
	float	mod;

	// print_p3(vec);
	mod = sqrt((double)vec.x * (double)vec.x + (double)vec.y * (double)vec.y + (double)vec.z * (double)vec.z);
	if(mod == 0)
		return vec;
	// printf("mod is %f\n", mod);
	nv.x = vec.x / mod;
	nv.y = vec.y / mod;
	nv.z = vec.z / mod;
	return (nv);
}

t_p3 _substruct(t_p3 vec1, t_p3 vec2)
{
	t_p3 new;

	new.x = vec1.x - vec2.x;
	new.y = vec1.y - vec2.y;
	new.z = vec1.z - vec2.z;

	return (new);
}

t_p3 _add(t_p3 vec1, t_p3 vec2)
{
	t_p3 new;

	new.x = vec1.x + vec2.x;
	new.y = vec1.y + vec2.y;
	new.z = vec1.z + vec2.z;

	return (new);
}

t_p3 _cross(t_p3 a, t_p3 b)
{
	t_p3	cp;
	// printf("a is ");
	// print_p3(a);
	// printf("b is ");
	// print_p3(a);
	cp.x = a.y * b.z - a.z * b.y;
	cp.y = a.z * b.x - a.x * b.z;
	cp.z = a.x * b.y - a.y * b.x;

	return (cp);
}

t_p3 _multy(t_p3 vec1, float i)
{
	t_p3 new;

	new.x = vec1.x * i;
	new.y = vec1.y * i;
	new.z = vec1.z * i;
	return (new);
}

float _dot(t_p3 vec1, t_p3 vec2)
{
	float ret;

	ret = ((vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z));
	return ret; 
}

float		distance(t_p3 p1, t_p3 p2)
{
	float d;

	d = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2));
	return (d);
}