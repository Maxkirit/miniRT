/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mturgeon <maxime.p.turgeon@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:05:05 by mkeerewe          #+#    #+#             */
/*   Updated: 2026/01/07 13:57:48 by mturgeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <math.h>

# define EPSILON 0.000001

typedef union	u_obj
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cyl;
}	t_obj;


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
	double	ambient;
	double	diffuse;
	double	specular;
	double	shine;
}	t_material;

typedef struct	s_sphere
{
	t_tuple		centre;
	double		radius;
	t_material	mat;
	t_mat		transform;
}	t_sphere;

typedef struct	s_plane
{
	t_tuple		point;
	t_tuple		normal_n;
	t_material	mat;
	t_mat		transform;
}	t_plane;

typedef struct	s_cylinder
{
	t_tuple		centre;
	t_tuple		axis_n;
	double		radius;
	double		height;
	t_material	mat;
	t_mat		transform;
}	t_cylinder;

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
	t_mat	transform;
}	t_cam;

typedef struct	s_world
{
	t_obj		*objs;
	int			num_objs;
	t_cam		cam;
	t_light		*lights;
	t_ambient	ambient;
}	t_world;

typedef struct s_image
{
	void	*pointer;
	char	*pixels;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
}	t_image;

typedef struct s_window
{
	void	*win;
	t_image	img;
	int		x;
	int		y;
}	t_window;

// tuple operations
t_tuple	vector(double x, double y, double z);
// vector operations
double	dot(t_tuple a, t_tuple b);
// matrix operations
t_mat	new_matrix(int rows, int cols);
t_mat	identity(void);
double	get_data(t_mat mat, int i, int j);
void	set_data(t_mat mat, int i, int j, double input);
// utils
int		equal(double a, double b);

#endif
