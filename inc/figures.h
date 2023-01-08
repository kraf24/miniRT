

#ifndef FIGURES_H
# define FIGURES_H
# define SP 1
# define PL 2
# define TR 3
# define CY 4

# include "minirt.h"

typedef struct s_sphere
{
	t_p3		centr;
	float		radius;
}				t_sphere;

typedef struct s_plane
{
	t_p3		centr;
	t_p3		orient;
}				t_plane;

typedef struct s_triangle
{
	t_p3		p1;
	t_p3		p2;
	t_p3		p3;
}				t_triangle;

typedef struct s_cylinder
{
	t_p3		o;
	t_p3		nv;
	float		r;
	float		h;
	t_p3		normal;
	float		dist1;
	float		dist2;
}				t_cylinder;

typedef struct	s_material
{
	int			gloss;
	float		reflective;
}				t_material;

// typedef struct s_square
// {
// 	t_p3		centr;
// 	t_p3		orient;
// 	float		scale;
// }				t_square;

union u_figures
{
	t_sphere	sp;
	t_plane		pl;
	t_triangle	tr;
	t_cylinder	cy;
	// t_square	sq;
};

typedef struct s_figures
{
	int				flag;
	union u_figures	figures;
	t_p3			collor;
	t_material		material;
	// t_p3			*pos;
	struct s_figures *next;
}				t_figures;


#endif