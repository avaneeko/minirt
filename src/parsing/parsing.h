#ifndef PARSING_H
# define PARSING_H

#include <stdbool.h>
#include <stddef.h>

typedef struct s_ptrim
{
	int   i;
	int   j;
	int   spaces;
	char *old_line;
	char *line;
} t_ptrim;

typedef struct s_pcolor
{
	float r;
	float g;
	float b;
}	t_pcolor;

typedef struct s_pvec3
{
	float x;
	float y;
	float z;
}	t_pvec3;

typedef struct s_plight
{
	bool   is_set;
	t_pvec3 lpoint;
	t_pcolor lcolor;
	float  brightness;
}	t_plight;

typedef struct s_pcamera
{
	bool    is_set;
	t_pvec3	vpoint;
	t_pvec3 	orien;
	float	fov;
}	t_pcamera;

typedef struct s_pambient
{
	bool  is_set;
	float ratio;
	t_pcolor a_color;
}	t_pambient;

typedef struct s_psphere
{
	t_pvec3 sp_center;
	float  sp_diamtr;
	t_pcolor sp_color;
}	t_psphere;

typedef struct s_pplane
{
	t_pvec3 point;
	t_pvec3 normal;
	t_pcolor pl_color;
}	t_pplane;

typedef struct s_pcylinder
{
	t_pvec3 cy_center;
	t_pvec3 cy_normal;
	float  cy_diamtr;
	float cy_height;
	t_pcolor cy_color;
}	t_pcylinder;

typedef struct  s_pobjs
{
	t_psphere *sp;
	uint32_t		sphere_len;
	uint32_t		sphere_cap;
	t_pplane  *pl;
	uint32_t		pl_len;
	uint32_t		pl_cap;
	t_pcylinder *cy;
	uint32_t		cy_len;
	uint32_t		cy_cap;
}	t_pobjs;

typedef struct s_pworld
{
	t_pambient A;
	t_pcamera  C;
	t_plight	  L;
	t_pobjs  objs;
}	t_pworld;


//parsing/parsing.c
void parsing(t_pworld *pworld, int ac, char const*filename);

//parsing/parse_ambient.c
void parse_ambient(t_pworld *pworld, char *line);

//parsing/parse_camera.c
void parse_camera(t_pworld *pworld, char *line);

//parsing/parse_light.c
void parse_light(t_pworld *pworld, char *line);

//parsing/parse_object.c
void parse_sphere(char *line);
void parse_plane(char *line);
void parse_cylinder(char *line);

//utils/parse_error.c
void parse_error(int code, char *s);

//utils/ft_split.c
char	**ft_split(char const *s, char c);

//utils/number_utils.c
double	parse_number(char const*str);

//parsing/parse_utils.c
void pworld_init(t_pworld *pworld);
void check_unit_vector(t_pvec3 v, char *err_msg);
t_pcolor parse_color(char *tok);
t_pvec3 parse_vec3(char *tok);
void	free_split(char **arr);

//utils/string_utils.c
int	ft_isspace(char c);
int ft_strlen(const char *s);
int	ft_strcmp(char const*s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(char const *s1);

#endif