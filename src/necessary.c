/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   necessary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:49:18 by llalba            #+#    #+#             */
/*   Updated: 2022/03/02 17:50:02 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	pixel = img->addr + (y * img->len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}
