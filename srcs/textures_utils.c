#include <fcntl.h>
#include <libft.h>
#include <stdio.h>
#include "../includes/scop.h"


GLuint loadBMP_custom(const char *imagepath)
{
	t_bmp texture;
	int fd;
	int rt;

	fd = open(imagepath, O_RDONLY);
	rt = read(fd, texture.header, BMP_HEADER_SIZE);
	if ( texture.header[0]!='B' || texture.header[1]!='M' ){
		printf("Not a correct BMP file\n");
		return 0;
	}
	texture.dataPos    = *(int*)&(texture.header[0x0A]);
	texture.imageSize  = *(int*)&(texture.header[0x22]);
	texture.width      = *(int*)&(texture.header[0x12]);
	texture.height     = *(int*)&(texture.header[0x16]);
	if (texture.imageSize == 0)
		texture.imageSize = texture.width * texture.height * 3;
	if (texture.dataPos == 0)
		texture.dataPos = 54;

	printf("##:%d - %s, %d %d %d %d", rt, texture.header, texture.dataPos, texture.imageSize, texture.width, texture.height);
	texture.data = malloc(sizeof(unsigned char) * texture.imageSize);
	rt = read(fd, texture.data, texture.imageSize);
	// write(1, texture.data, texture.imageSize);

	GLuint textureID;
	glGenTextures(1, &textureID);
	 
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	 
	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, texture.width, texture.height, 0, GL_BGR, GL_UNSIGNED_BYTE, texture.data);

	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	return (textureID);
}