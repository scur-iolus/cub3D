/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:27:16 by llalba            #+#    #+#             */
/*   Updated: 2022/01/25 18:21:14 by llalba           ###   ########.fr       */
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

# define ERROR				"Error\n"
# define TRUE				1
# define FALSE				0
# define FAIL				1
# define SUCCESS			0

typedef char t_bool;


typedef struct s_data
{
	char		*map;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*f;
	char		*c;
	char		*line;

}				t_data;

int			ft_strlen(const char *s);
void		ft_error(t_data *data, char *str);
int			ft_strcmp(char *s1, char *s2);
int			map_is_valid(char *ber);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
void		ft_strncpy(char *s, char **d, int n);
int			ft_cmp(char *s1, char *s2);


void		free_data(t_data *data);
int			get_next_line(int fd, char **line);


#endif
