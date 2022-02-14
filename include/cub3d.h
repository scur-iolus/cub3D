/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:27:16 by llalba            #+#    #+#             */
/*   Updated: 2022/02/14 14:49:38 by llalba           ###   ########.fr       */
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
# include "../mlx_linux/mlx.h"

# define ERROR				"Error\n"
# define TRUE				1
# define FALSE				0
# define FAIL				1
# define SUCCESS			0

typedef char	t_bool;

typedef struct s_map
{
	char	*content;
	int		width;
	int		height;
	int		pos;
	char	compass;
}				t_map;
typedef struct s_color
{
	t_bool		not_yet;
	int			r;
	int			g;
	int			b;
}				t_color;
typedef struct s_data
{
	t_map		map;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*color_str;
	t_color		f;
	t_color		c;
	char		*line;
	char		*line_start;
	int			state;
	int			map_start;
	int			ready;

}				t_data;

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

#endif
