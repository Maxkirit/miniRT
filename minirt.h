/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:05:05 by mkeerewe          #+#    #+#             */
/*   Updated: 2026/01/09 10:24:42 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft/src/libft.h"
# include "mlx/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>


# define EPSILON 0.000001

typedef enum	e_type
{
	SPHERE, PLANE, CYLINDER
}	t_type;

typedef struct	s_mat
{
	int		rows;
	int		cols;
	double	*data;
}	t_mat;

// pt is boolean for point or vector
typedef struct	s_tuple
{
	double	x;
	double	y;
	double	z;
	double	pt;
}	t_tuple;

typedef struct	s_ray
{
	t_tuple	origin;
	t_tuple	dir;
}	t_ray;

typedef struct	s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct	s_material
{
	t_color	color;
	double	diffuse; // hard code
	double	specular; // hard code
	double	shine; // hard code
}	t_material;

typedef struct	s_sphere
{
	t_tuple		centre;
	double		radius;
}	t_sphere;

typedef struct	s_plane
{
	t_tuple		point;
	t_tuple		normal_n;
}	t_plane;

typedef struct	s_cylinder
{
	t_tuple		centre;
	t_tuple		axis_n;
	double		radius;
	double		height;
}	t_cylinder;

typedef union	u_obj
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cyl;
}	t_obj;

typedef struct	s_light
{
	t_tuple	point;
	double	bright;
	t_color	color;
}	t_light;

typedef struct	s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;

typedef struct	s_cam
{
	t_tuple	viewpoint;
	t_tuple	normal_n;
	double	fov;
	double	pixel_step;
	t_mat	to_world;
	t_mat	from_world;
	double	half_width;
	double	half_height;
}	t_cam;

typedef struct	s_shape
{
	t_type		type;
	t_obj		obj;
	t_material	mat;
	t_mat		to_world;
	t_mat		from_world;
}	t_shape;

typedef struct	s_world
{
	t_shape		*shapes;
	int			num_shapes;
	t_cam		cam;
	t_light		*lights;
	int			num_lights;
	t_ambient	ambient;
}	t_world;

typedef struct s_image
{
	void	*pointer;
	char	*pixels;
	int		bpp;
	int		line_size;
	int		endian;
}	t_image;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win;
	t_image	img;
	int		x;
	int		y;
}	t_mlx;

typedef struct	s_intersection
{
	t_shape	*shape;
	double	t;
}	t_intersection;

typedef struct s_intersect
{
	t_intersection	*table;
	int				size;
}	t_intersect;

// tuple operations
t_tuple	point(double x, double y, double z);
t_tuple	vector(double x, double y, double z);
t_tuple	substr_tuples(t_tuple a, t_tuple b);
// vector operations
double	dot_product(t_tuple a, t_tuple b);
t_tuple	mult_vec_scalar(t_tuple vec, double scal);
double	vec_magnitude(t_tuple vec);
t_tuple	vec_normalise(t_tuple vec);
t_tuple	cross_product(t_tuple a, t_tuple b);
// matrix operations
t_mat	new_matrix(int rows, int cols);
void	destroy_matrix(t_mat mat);
double	get_data(t_mat mat, int i, int j);
void	set_data(t_mat mat, int i, int j, double input);
t_mat	mat_mult(t_mat a, t_mat b);
t_tuple	mat_tuple_mult(t_mat mat, t_tuple tup);
int		mat_equal(t_mat a, t_mat b);
t_tuple	mat_tuple_mult(t_mat mat, t_tuple tup);
t_mat	identity(void);
double	determinant(t_mat mat);
t_mat	submatrix(t_mat mat, int row, int col);
double	minor(t_mat mat, int row, int col);
double	cofactor(t_mat mat, int row, int col);
t_mat	inverse(t_mat mat);
//transformation matrices
t_mat	scale_mtx(double x, double y, double z);
t_mat	translate_mtx(t_tuple dest);
t_mat	rotation_mtx(t_tuple dest_axis);
t_mat	build_transfo(t_shape obj);
t_mat	build_transfo_cam(t_cam cam);
// parsing
int		parse_file(char *file, t_world *world);
// utils
void	free_world(t_world *w);
int		equal(double a, double b);
double	square(double x);
t_shape	*shape_realloc(t_shape *old, int new_size);
t_light	*light_realloc(t_light *old, int new_size);
int		check_int_conversion(char *str, int num);
void	free_args(char **args);
double	*res_realloc(double *res, int size, t_intersect sol);
t_intersection	*inter_realloc(t_intersection *old, int old_size, t_intersection *sol, int num_sol);
//mlx
void	init_mlx(t_mlx *data, int screen_x, int screen_y);
void	error(t_mlx *data);
void	end_program(t_mlx *data);
void	my_pixel_put(t_image *img, int x, int y, int color);
int		rgb_color(double r, double g, double b);
// raytracer
t_color	run_raytracer(t_world *w, int x, int y);
int		intersections(t_ray ray, t_world world, t_intersection *hit);

#endif
