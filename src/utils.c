/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:26:52 by llalba            #+#    #+#             */
/*   Updated: 2022/02/21 17:54:40 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_error(t_data *data, char *str)
{
	(void)write(2, "Error:\n", 7);
	(void)write(2, str, ft_strlen(str));
	if (data)
		free_data(data);
	exit (EXIT_FAILURE);
}

int	map_is_valid(char *cub)
{
	int	len;

	len = ft_strlen(cub);
	if (cub == 0)
		return (FAIL);
	if (len < 5)
		return (FAIL);
	if (ft_strcmp(cub + len - 4, ".cub"))
		return (FAIL);
	return (SUCCESS);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

int	ft_atoi(const char *str)
{
	unsigned long long	value;
	size_t				i;
	t_bool				empty;

	value = 0;
	empty = TRUE;
	i = 0;
	while (str[i] == 32)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		empty = FALSE;
		value = value * 10 + str[i++] - 48;
	}
	while (str[i] == ' ')
		i++;
	if (str[i])
		return (-1);
	if (empty || value > 2147483647)
		return (-1);
	return (value);
}

void	skip_spaces(char **line)
{
	while (**line == ' ')
		(*line)++;
}

int	count_comma(char *color_str)
{
	int	i;

	i = 0;
	while (*color_str && i < 4)
	{
		if (*color_str == ',')
			i++;
		color_str++;
	}
	return (i);
}

t_bool	is_not_in_set(t_data *data)
{
	if (data->line[0] != 'F' && data->line[0] != 'C' \
		&& ft_cmp(data->line, "NO") && ft_cmp(data->line, "SO") \
		&& ft_cmp(data->line, "WE") && ft_cmp(data->line, "EA") \
		&& data->line[0] != 0)
		return (TRUE);
	return (FALSE);
}

int	open_file(t_data *data, char *map)
{
	int		fd;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		ft_error(data, "invalid map\n");
	return (fd);
}

void	close_file(t_data *data, int fd)
{
	int		ret;

	ret = close(fd);
	if (ret)
		ft_error(data, "close failed\n");
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}
