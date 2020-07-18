/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 02:28:49 by badam             #+#    #+#             */
/*   Updated: 2020/07/14 22:59:50 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	num2buff(size_t n, t_byte *buff, size_t len)
{
	register size_t	i;

	i = 0;
	while (i < len)
	{
		buff[i] = n % 256;
		n /= 256;
		++i;
	}
}

static void	set_header(t_bmpheader *header, size_t w, size_t h, size_t len)
{
	ft_memset(header, 0, sizeof(header) * 8);
	header->type[0] = 'B';
	header->type[1] = 'M';
	num2buff(54 + len, header->total_size, sizeof(header->total_size));
	num2buff(54, header->offset, sizeof(header->offset));
	num2buff(40, header->dib_size, sizeof(header->dib_size));
	num2buff(w, header->width, sizeof(header->width));
	num2buff(h, header->height, sizeof(header->height));
	num2buff(1, header->planes, sizeof(header->planes));
	num2buff(24, header->bpp, sizeof(header->bpp));
	num2buff(len, header->bitmap_size, sizeof(header->bitmap_size));
	num2buff(2835, header->h_print_res, sizeof(header->h_print_res));
	num2buff(2835, header->v_print_res, sizeof(header->v_print_res));
}

static void	*generate_image(int *colors, size_t len, size_t pixels_c, size_t w)
{
	register size_t	i;
	register size_t	in;
	register size_t	out;
	void			*data;

	if (!(data = malloc(len * sizeof(t_byte))))
		return (NULL);
	ft_memset(data, 0, len);
	i = pixels_c;
	out = 0;
	while (i > 1)
	{
		in = i / w * w + (w - (i % w));
		num2buff(colors[in], data + out, 3);
		out += 3;
		i--;
	}
	return (data);
}

bool		write_image(char *file, int *colors, size_t width, size_t height)
{
	int			fd;
	t_bmpheader	header;
	size_t		data_len;
	void		*data;

	data_len = width * height * 3;
	set_header(&header, width, height, data_len);
	if (!(data = generate_image(colors, data_len, width * height, width))
			|| (fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1
			|| write(fd, &header, sizeof(header)) != sizeof(header)
			|| write(fd, data, data_len) != (ssize_t)data_len
			|| close(fd) == -1)
		return (false);
	free(data);
	return (true);
}
