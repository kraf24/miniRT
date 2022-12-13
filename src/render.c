/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstaryk <fstaryk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 16:47:30 by fstaryk           #+#    #+#             */
/*   Updated: 2022/12/13 21:36:42 by fstaryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_p3    get_screen_coord(int x, int y, t_scene *scene)
{
	t_p3 ret;

	// printf("defining vector for %d %d\n", x, y);
	ret.x = ((2 * (x + 0.5)/scene->width) - 1) * scene->aspect_ratio * scene->camera->fov_l;
	ret.y = (1 - (2 * (y + 0.5)/scene->height)) * scene->aspect_ratio;
	ret.z = -1;
	// printf("result is "z
	return ret;
}

t_p3    look_at_pixel(t_p3 d, t_p3 cam_nv)
{
	t_p3    ref_up;
	t_p3    x_axis;
	t_p3    y_axis;
	t_p3    rotated;

	// printf("d axis is ");
	// print_p3(d);
	// printf("cam_nv axis is ");
	// print_p3(cam_nv);
	ref_up = new_vec(0, 1, 0);
	// print_p3(ref_up);
	// print_p3(_norm(cam_nv));
	x_axis = _cross(ref_up, _norm(cam_nv));
	// printf("x axis is ");
	// print_p3(x_axis);
	y_axis = _cross(_norm(cam_nv), x_axis);
	// printf("y axis is ");
	// print_p3(y_axis);

	rotated = _add(_multy(x_axis, d.x), cam_nv);
	rotated = _add(_multy(y_axis, d.y), rotated);

	// printf("rotated is ");
	// print_p3(rotated);
	return rotated;
}

float   sphere_intersection(t_p3 d, t_p3 cam_o, t_p3 sp_o, float r){
    t_p3 p;//makes vector p that goes from sphere origin to intersection
    float disc;
    float x1;
    float x2;
    float quad_kof[3];
    
	// print_p3(d);
    p = _substruct(cam_o, sp_o);
    quad_kof[0] = _dot(d, d);
    quad_kof[1] = 2 * _dot(p, d);
    quad_kof[2] = _dot(p, p) - r * r;
    disc = quad_kof[1] * quad_kof[1] - 4 * quad_kof[0] * quad_kof[2];
    x1 = (-quad_kof[1] + sqrt(disc)) / (2 * quad_kof[0]);
    x2 = (-quad_kof[1] - sqrt(disc)) / (2 * quad_kof[0]);
    // printf("disc is %f, x1 %f, x2 %f\n", disc, x1, x2);
	
    if (disc < 0)
		return (INFINITY);
	else if (disc == 0)
		return (x1);
	else
		return (x1 < x2 ? x1 : x2);
}

float	plane_intersection(t_p3 d, t_p3 cam_o, t_p3 pl_n, t_p3 pl_o){
	float inter_proj;//projection of intersecting normal and direction of camera
	float inter;
	
	inter_proj = _dot(d, pl_n);
	if(inter_proj == 0)//this means that plane doesnt intersect with the ray
		return INFINITY;
	inter = _dot(_substruct(pl_o, cam_o)/*vector to posible inter*/, pl_n) / inter_proj;
	//if inter == 0 vector is || to plane
	//if < 0 its on the oposite side of the cam
	//if > 0 it intersects
	if(inter > 0)
		return inter;
	else
		return INFINITY;
}

float try_intersections(t_p3 d, t_p3 cam_o, t_figures *fig, t_figures *closest_fig)
{
	float inter_dist;
    float closest_inter;
	
    closest_inter = INFINITY;
    while (fig)
	{
		if(fig->flag == SP)
            inter_dist = sphere_intersection(d, cam_o, fig->figures.sp.centr, fig->figures.sp.radius);
		else if(fig->flag == PL)
			inter_dist = plane_intersection(d, cam_o, fig->figures.pl.orient, fig->figures.pl.centr);
        if(inter_dist < closest_inter && inter_dist > 0){
            closest_inter = inter_dist;
            *closest_fig = *fig;
        }
        fig = fig->next;
    }
	return closest_inter;
}


int trace_ray(t_p3 d, t_scene *scene)
{
    float   closest_inter;
    t_figures closest_figure;
	t_p3		reflect_norm;
	t_p3	inter_p;
	
	// closest_figure = NULL;
    closest_figure.flag = 0;
    closest_inter = try_intersections(d, scene->camera->pos, scene->figures, &closest_figure);
    if(closest_inter == INFINITY)
        return scene->background;
	inter_p = _add(scene->camera->pos, _multy(_norm(d), closest_inter));
    reflect_norm = _norm(calculate_base_reflection(inter_p, &closest_figure));
	return rgb_int(_multy(closest_figure.collor, calculate_light(reflect_norm, inter_p, scene)));
}

void render_scene(t_scene *scene)
{
	int y;
	int x;
	t_p3 dir_vec;
	int color;

	y = 0;
	while (y < scene->height)
	{
		x = 0;
		while (x < scene->width)
		{
			dir_vec = get_screen_coord(x, y, scene);
			// printf("dir vec is ");
			// print_p3(dir_vec);
			dir_vec = look_at_pixel(dir_vec, scene->camera->direct);                     
			color = trace_ray(dir_vec, scene);
            my_mlx_pixel_put(scene, x, y, color); 
			x++;
		}
		y++;
	}
}