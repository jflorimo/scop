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
	texture.dataPos = *(int*)&(texture.header[0x0A]);
	texture.imageSize = *(int*)&(texture.header[0x22]);
	texture.width = *(int*)&(texture.header[0x12]);
	texture.height = *(int*)&(texture.header[0x16]);
	if (texture.imageSize == 0)
		texture.imageSize = texture.width * texture.height * 3;
	if (texture.dataPos == 0)
		texture.dataPos = 54;
	return (texture);
}

GLuint			load_bmp_custom(const char *imagepath)
{
	t_bmp_init	b;
	t_bmp		texture;

	b.fd = open(imagepath, O_RDONLY);
	b.rt = read(b.fd, texture.header, BMP_HEADER_SIZE);
	texture = init_texture(texture);
	texture.data = malloc(sizeof(unsigned char) * texture.imageSize);
	b.rt = read(b.fd, texture.data, texture.imageSize);
	glGenTextures(1, &(b.textureID));
	glBindTexture(GL_TEXTURE_2D, b.textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0,
		GL_BGR, GL_UNSIGNED_BYTE, texture.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	return (b.textureID);
}
