#define _CRT_SECURE_NO_WARNINGS

#include "LoadTexture.h"  

//load image & set it as a texture with dimension as 256*256  

GLuint LoadTexture::LoadTextureImageFile(const char* file_name, int width, int height)
{
	GLuint texture;
	FILE* file;
	unsigned char* data;

	fopen_s(&file, file_name, "rb");
	if (file == NULL)
	{
		return 0;
	}
	data = new unsigned char[width * height * 3];
	fread(data, 54, 1, file);
	fread(data, width * height * 3, 1, file);
	fclose(file);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	for (int i = 0; i < width * height * 3; i += 3)
	{
		unsigned char s = data[i + 2];
		data[i + 2] = data[i];
		data[i] = s;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glBindTexture(GL_TEXTURE_2D, 0);
	delete[] data;
	return texture;
}

