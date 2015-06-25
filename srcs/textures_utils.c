/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/23 14:32:14 by jflorimo          #+#    #+#             */
/*   Updated: 2015/06/23 14:32:17 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <libft.h>
#include <stdio.h>
#include "../includes/scop.h"

t_bmp			init_texture(t_bmp texture)
{
	if (texture.header[0] != 'B' || texture.header[1] != 'M')
	{
		printf("Not a correct BMP file\n");
		exit_error_file_format();
	}
	texture.data_pos = *(int*)&(texture.header[0x0A]);
	texture.image_size = *(int*)&(texture.header[0x22]);
	texture.width = *(int*)&(texture.header[0x12]);
	texture.height = *(int*)&(texture.header[0x16]);
	if (texture.image_size == 0)
		texture.image_size = texture.width * texture.height * 3;
	if (texture.data_pos == 0)
		texture.data_pos = 54;
	return (texture);
}

GLuint			load_bmp_custom(const char *imagepath)
{
	t_bmp_init	b;
	t_bmp		texture;

	b.fd = open(imagepath, O_RDONLY);
	b.rt = read(b.fd, texture.header, BMP_HEADER_SIZE);
	texture = init_texture(texture);
	texture.data = malloc(sizeof(unsigned char) * texture.image_size);
	b.rt = read(b.fd, texture.data, texture.image_size);
	glGenTextures(1, &(b.texture_id));
	glBindTexture(GL_TEXTURE_2D, b.texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0,
		GL_BGR, GL_UNSIGNED_BYTE, texture.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	return (b.texture_id);
}
