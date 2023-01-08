

#ifndef MINIRT_H
#define MINIRT_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <mlx.h>

# include "vector.h"
# include "figures.h"
# include "get_next_line.h"
# include "libft.h"
# include "scene.h"

#define EPSILON 0.00001

//ERRORS
int		print_error(char *str);
void	fatal_error(char *str);
void	fatal_error_v2(t_scene *scene);
void	free_scene(t_scene *scene);
void	exit_error(int code);
void	check_stof(float num, t_scene *scene, int flag);

//PARSING
t_scene	*parse_scene(char *file_name);
void	parse_sphere(char **str, t_scene *scene);
void	parse_plane(char **str, t_scene *scene);
void	parse_triangle(char **str, t_scene *scene);
void	parse_cylinder(char **str, t_scene *scene);

//UTILS
void add_end_f(t_figures **figures);
t_figures *new_lst_f(void);
t_p3 read_vec(char **str, t_scene *scene, int flag);
float stof(char **str, t_scene *scene, int flag);
void next(char **str, t_scene *scene);

void	my_mlx_pixel_put(t_scene *scene, int x, int y, int color);


//MATERIAL
t_material fill_material(char **str, t_scene *scene);

//LIGHTS

t_p3    calculate_base_reflection(t_p3 inter_p, t_figures *fig);
// t_p3	calculate_light(t_p3 norm, t_p3 inter_p, t_scene *scene);
float	calculate_light(t_p3 norm, t_p3 inter_p, t_scene *scene, t_p3 view_vec, t_figures figure);

//COLORS
int rgb_int(t_p3 col);
int		_cadd(int color_a, int color_b);
int		_cproduct(int color, float coef);
t_p3	color_x_light(t_p3 base_color, t_p3 light_collor);


//intersections

float   sphere_intersection(t_p3 d, t_p3 cam_o, t_p3 sp_o, float r);
float	plane_intersection(t_p3 d, t_p3 cam_o, t_p3 pl_n, t_p3 pl_o);
float try_intersections(t_p3 d, t_p3 cam_o, t_figures *fig, t_figures *closest_fig);

//render
void render_scene(t_scene *scene);

void print_p3(t_p3 x);
void print_scene(t_scene *scene);

//cylinder

float	cylinder_intersection(t_p3 d, t_p3 cam_o, t_figures* cy);


//keyhook
int	key(int key, t_scene *scene);
int escape(t_scene *scene);
#endif