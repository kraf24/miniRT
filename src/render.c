
#include "../inc/minirt.h"

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

t_p3    get_screen_coord(int x, int y, t_scene *scene)
{
	t_p3 ret;

	// printf("defining vector for %d %d\n", x, y);
	ret.x = ((2 * (x + 0.5)/scene->width) - 1) * scene->aspect_ratio * scene->camera->fov_l;
	ret.y = (1 - (2 * (y + 0.5)/scene->height)) * scene->camera->fov_l;
	ret.z = -1;
	// printf("result is "z
	ret = look_at_pixel(ret, scene->camera->direct);
	return ret;
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
	if(inter == 0)
		return INFINITY;
	else
		return inter;
}

bool	check_p_in_borders(t_p3 p1, t_p3 p2, t_p3 p3, t_p3 inter_p)
{
	t_p3	v1;
	t_p3	v2;
	t_p3	v3;
	t_p3	cross1;
	t_p3	cross2;
	
	v1 = _substruct(p2, p1);
	v2 = _substruct(p3, p1);
	v3 = _substruct(inter_p, p1);	
	cross1 = _cross(v1, v2);
	cross2 = _cross(v1, v3);
	if(_dot(cross1, cross2) / _lenth(cross1) * _lenth(cross2) < 0)
		return false;
	return true;
}

float	trinagle_intersection(t_p3 d, t_p3 cam_o, t_triangle tri){
	t_p3 tri_norm;
	float	plane_inter;
	t_p3	inter_p;
	tri_norm = _cross(_substruct(tri.p1, tri.p2), _substruct(tri.p1, tri.p3));
	plane_inter = plane_intersection(d, cam_o, tri_norm, tri.p1);
	inter_p = _add(cam_o, _multy(d, plane_inter));
	if (!check_p_in_borders(tri.p1, tri.p2, tri.p3, inter_p))
		return INFINITY;
	if (!check_p_in_borders(tri.p3, tri.p1, tri.p2, inter_p))
		return INFINITY;
	if (!check_p_in_borders(tri.p2, tri.p3, tri.p1, inter_p))
		return INFINITY;
	return plane_inter;
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
		else if(fig->flag == TR)
			inter_dist = trinagle_intersection(d, cam_o, fig->figures.tr);
		else if(fig->flag == CY)
			inter_dist = cylinder_intersection(d, cam_o, fig);
        if(inter_dist < closest_inter && inter_dist > 0){
            closest_inter = inter_dist;
            *closest_fig = *fig;
        }
        fig = fig->next;
    }
	return closest_inter;
}

t_p3 ray_reflect(t_p3 dir, t_p3 normal)
{
	return _substruct(_multy(normal, 2 * _dot(normal, dir)) , dir);
}

// t_p3	get_reflect_ray(t_p3 d, t_p3 normal)
// {
// 	t_p3		reflect_ray;

// 	reflect_ray.direction = ray_reflect(d, normal);
// 	if (vec3_dot_product(reflect_ray.direction, hit_info->hit_normal) < 0)
// 		reflect_ray.origin = (vec3_substract(hit_info->hit,
// 					vec3_multiply(hit_info->hit_normal, 1e-3)));
// 	else
// 		reflect_ray.origin = (vec3_add(hit_info->hit,
// 					vec3_multiply(hit_info->hit_normal, 1e-3)));
// 	return (reflect_ray);
// }

int trace_ray(t_p3 d, t_p3 O, t_scene *scene, int depth)
{
	float		closest_inter;
	t_figures	closest_figure;
	t_p3		reflect_norm;
	t_p3		inter_p;
	t_p3		temp_color;
	int			reflect_color;
	
	closest_figure.flag = 0;
	closest_inter = try_intersections(d, O, scene->figures, &closest_figure);
	if(closest_inter == INFINITY)
		return scene->background;
	inter_p = _add(O, _multy(_norm(d), closest_inter));
	reflect_norm = _norm(calculate_base_reflection(inter_p, &closest_figure));
	temp_color = _multy(closest_figure.collor, calculate_light(reflect_norm, inter_p, scene, _multy(d, -1), closest_figure));
	if (depth <= -10 || closest_figure.material.reflective <= 0)
		return rgb_int(temp_color);
	reflect_color = trace_ray(ray_reflect(_multy(d, -1), reflect_norm), inter_p, scene, depth - 1);
	return _cadd(_cproduct(rgb_int(temp_color), (1 - closest_figure.material.reflective)), _cproduct(reflect_color, closest_figure.material.reflective));
	// return rgb_int(temp_color);
	// return reflect_color;
}

void render_scene(t_scene *scene)
{
	int y;
	int x;
	t_p3 dir_vec;
	int color;

	y = 0;
	if (scene->mlx->img)
	{
		fprintf(stderr, "%f", scene->camera->pos.x);
		mlx_destroy_image(scene->mlx->mlx, scene->mlx->img);
		scene->mlx->img = mlx_new_image(scene->mlx->mlx, scene->width, scene->height);
	}
	while (y < scene->height)
	{
		x = 0;
		while (x < scene->width)
		{
			dir_vec = get_screen_coord(x, y, scene);                 
			color = trace_ray(dir_vec, scene->camera->pos, scene, 2);
            my_mlx_pixel_put(scene, x, y, color); 
			// exit(0);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene->mlx->mlx, scene->mlx->window, scene->mlx->img, 0, 0);
}