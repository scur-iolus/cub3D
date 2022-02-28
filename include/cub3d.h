/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:27:16 by llalba            #+#    #+#             */
/*   Updated: 2022/02/28 17:37:09 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include "mlx.h" // "../mlx_linux/mlx.h"

# define ERROR				"Error\n"
# define TRUE				1
# define FALSE				0
# define FAIL				1
# define SUCCESS			0
# define WIN_W				1920
# define WIN_H				1080
# define MM_W_MIN			30
# define MM_W_MAX			380
# define MM_H_MIN			812
# define MM_H_MAX			1050

# define W					119
# define S					115
# define A					97
# define D					100
# define ESC				65307
# define LEFT				65361
# define RIGHT				65363
# define MOUSE_LEFT			1
# define MOUSE_RIGHT		3
# define MOUSE_CENTRAL		2
# define SCROLL_OUT			4
# define SCROLL_IN			5
# define PI					3.1415926535
# define VIEW				1.15191730632

typedef char	t_bool;

typedef struct s_map
{
	char			*content;
	int				width;
	int				height;
	int				pos;
	int				block_w;
	int				block_h;
	char			compass;
}					t_map;

typedef struct s_color
{
	t_bool			not_yet;
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct s_img
{
	void	*mlx_img;
	char	*ad;
	int		bpp;
	int		len;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void			*mlx;
	void			*mlx_win;
	int				img_w;
	int				img_h;
	struct s_img	img;
}					t_mlx;

/*
** no = path de la texture NO
** so = path de la texture SO
** we = path de la texture WE
** ea = path de la texture EA
** color_str = contient successivement F et C sous forme de string
** f = couleur au format RGB
** c = couleur au format RGB
** line = issu de GNL, attention on modifie le pointeur
** line_start = début de line
** state = va de 0 à 6, à 6 toute la config (hors map) est déjà chargé
** map_start = numéro de la ligne où la map en elle-même commence
** pos_x = x de la position du joueur avec x = 0 en bas à gauche
** pos_y = y de la position du joueur avec y = 0 en bas à gauche
** dir_x = x de la direction vers laquelle est tourné le joueur
** dir_y = y de la direction vers laquelle est tourné le joueur
** plane_x = x du plan de la caméra
** plane_y = y du plan de la caméra
** camera_x = de -1 à 1, représente le n-ième rayon, 0 le rayon "tout droit"
** ray_dir_x = coordonnée x de camera_x
** ray_dir_y = coordonnée x de camera_y
** side_dist_x = distance jusqu'à une ligne verticale donnée du quadrillage
** side_dist_y = distance jusqu'à une ligne horizontale donnée du quadrillage
** delta_dist_x = longueur du segment entre 2 lignes verticales du quadrillage 
** delta_dist_y = longueur du segment entre 2 lignes horizontales du quadrillage
** step_x = vaut -1 ou 1, projection du rayon actuel sur l'axe x
** step_y = vaut -1 ou 1, projection du rayon actuel sur l'axe y
** map_x = int de pos_x (arrondi vers zéro)
** map_y = int de pos_y (arrondi vers zéro)
** hit = vaut 0 (pas de mur touché), N, S, E ou W (mur touché)
** line_height = hauteur de la ligne de pixels à colorier pour rendre le mur
*/

typedef struct s_text
{
	double			ray_pos;
	int				h;
	int				w;
	double			step;
	double			start;
	struct s_img	img;
}	t_text;

typedef struct s_data
{
	t_map			map;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*color_str;
	t_color			f;
	t_color			c;
	char			*line;
	char			*line_start;
	int				state;
	int				map_start;
	struct s_mlx	mlx;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				step_x;
	int				step_y;
	int				map_x;
	int				map_y;
	char			hit;
	double			line_height;
	struct s_text	n;
	struct s_text	s;
	struct s_text	e;
	struct s_text	w;
}					t_data;

// INIT
void		init_data(t_data *data);
void		init_color(t_data *data);

// UTILS
int			ft_strlen(const char *s);
void		ft_error(t_data *data, char *str);
int			ft_strcmp(char *s1, char *s2);
int			map_is_valid(char *ber);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
void		ft_strncpy(char *s, char **d, int n);
int			ft_cmp(char *s1, char *s2);
int			ft_atoi(const char *str);
void		free_data(t_data *data);
void		ft_free_split(char **ptr);
void		skip_spaces(char **line);
t_bool		is_not_in_set(t_data *data);
char		*ft_cpy(void *dst, const void *src, int n);
int			count_comma(char *color_str);
int			open_file(t_data *data, char *map);
void		close_file(t_data *data, int fd);
int			free_n_exit(void *data);
void		img_pix_put(t_img *img, int x, int y, int color);
char		pixel_to_char(t_data *data, int x, int y);


// GET_CONFIG
size_t		get_coord_len(t_data *data, char *str);
size_t		get_color_len(char *str);
int			get_coord(t_data *data, char *coord, char **s);
int			get_colors(t_data *data, char c, t_color *color);
void		format_color(t_data *data, t_color *color);

// CHECK_MAP
void		check_frame(t_data *data);

// GET_MAP
void		get_map_size(t_data *data);
void		get_map_content(t_data *data);
void		set_map(t_data *data);

// GET_NEXT_LINE
int			get_next_line(int fd, char **line);

// SPLIT
char		**ft_split(char const *str, char c);

//MOVE
int			key_press(int key, void *param);
void		step_backwards(t_data *data);
void		move_right(t_data *data);
void		move_left(t_data *data);
void		step_forward(t_data *data);

//LOOK
void		look_right(t_data *data);
void		look_left(t_data *data);

//MINI_MAP
void		draw_player(t_data *data);
void		outline_mm(t_data *data);
void		color_block(t_data *data, int x, int y, int color);
void		design_mm(t_data *data);
void		mini_map(t_data *data);

//SETTINGS
void		set_dir(t_data *data);
void		set_plane(t_data *data);
void		set_delta(t_data *data);
void		set_side_dist(t_data *data);
void		set_pos_xy(t_data *data);

//RAY_CASTING
void		ray_casting(t_data *data);

#endif
