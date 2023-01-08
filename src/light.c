
#include "../inc/minirt.h"

//add triangle
t_p3    calculate_base_reflection(t_p3 inter_p, t_figures *fig){
    t_p3 refl;
    
    if(fig->flag == SP)
        refl = _substruct(inter_p, fig->figures.sp.centr);
    if(fig->flag == PL)
        refl = fig->figures.pl.orient;
	if(fig->flag == CY)
		refl = fig->figures.cy.normal;
    return refl;
}

bool	is_blocked(t_p3 dir_to_light, t_p3 inter_p, t_figures *fig)
{
	float	inter;

	while (fig)
	{
		if(fig->flag == SP)
			inter = sphere_intersection(dir_to_light, inter_p, fig->figures.sp.centr, fig->figures.sp.radius);
		else if(fig->flag == PL)
			inter = plane_intersection(dir_to_light, inter_p, fig->figures.pl.orient, fig->figures.pl.centr);
		if(inter > 1e-4 && inter < 1)
			return true;
		fig = fig->next;
	}
	return false;
}

// t_p3	calculate_light(t_p3 norm, t_p3 inter_p, t_scene *scene)
// {
// 	t_p3 ret_light;
// 	t_lights *light;
// 	t_p3 dir_to_light;
//     float intensity;

// 	light = scene->lights;
// 	ret_light = new_vec(0, 0, 0);
// 	ret_light = color_x_light(ret_light, _multy(scene->a_color,
// 				scene->a_scale));
// 	while (light)
// 	{
// 		dir_to_light = _substruct(light->light.pos, inter_p);
//         if(!is_blocked(dir_to_light, inter_p, scene->figures) && _dot(dir_to_light, norm) > 0/*insurse that we dont lower our light because of light souces that cosinus lower than 0*/)
//         {
//             // printf("im trying to calculate light\n");
//             intensity = (light->light.scale * _dot(norm, dir_to_light)) / (_lenth(norm) * _lenth(dir_to_light));//dot(a, b)/len(a)*len(b) == cosinus between a
//             ret_light = color_x_light(ret_light, _multy(light->light.rgb, light->light.scale));
//         }
//         light = light->next;
// 	}
//     if(ret_light.x > 253)
//         ret_light.x = 255;
//     if(ret_light.y > 253)
//         ret_light.y = 255;
//     if(ret_light.z > 253)
//         ret_light.z = 255;
// 	return (ret_light);
// }

// void add_light(t_p3 *rgb, float cof, )

float	calculate_light(t_p3 norm, t_p3 inter_p, t_scene *scene, t_p3 view_vec, t_figures figure)
{
	float ret_light;
	t_lights *light;
	t_p3 dir_to_light;
	t_p3	R_vec;
	
	// t_p3	rgb;

	// add_light();
	light = scene->lights;
	ret_light = 0;
	ret_light += scene->a_scale; 
	while (light)
	{
		dir_to_light = _substruct(light->light.pos, inter_p);
		R_vec = _substruct(_multy(_multy(norm, 2), _dot(norm, dir_to_light)), dir_to_light);
		if (!is_blocked(dir_to_light, inter_p, scene->figures))
		{
			if (_dot(norm, dir_to_light) > 0/*insurse that we dont lower our light because of light souces that cosinus lower than 0*/)
			{
				ret_light += (light->light.scale * _dot(norm, dir_to_light)) / (_lenth(norm) * _lenth(dir_to_light));//dot(a, b)/len(a)*len(b) == cosinus between vectors
			}
			if (figure.material.gloss != -1 && figure.material.gloss != 0)
			{
				if (_dot(R_vec, view_vec) > 0)
				{
					ret_light += light->light.scale * powf(_dot(R_vec, view_vec) / (_lenth(R_vec) * _lenth(view_vec)), figure.material.gloss);
				}
				
			}
		}
		light = light->next;
	}
	return (ret_light);
}
