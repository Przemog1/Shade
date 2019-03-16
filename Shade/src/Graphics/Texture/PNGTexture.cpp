#pragma once
#include "PNGTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <glad/glad.h>
#include <iostream>

PNGTexture::PNGTexture(const std::string& imagePath)
{
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(imagePath.c_str(), &width, &height, &channels, 4);

	if (!data)
	{
		std::cout << "Failed to load image: " << imagePath << std::endl;
		return;
	}

	glGenTextures(1, &id);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

void PNGTexture::setTexture(const std::string& imagePath)
{
	glDeleteTextures(1, &id);

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(imagePath.c_str(), &width, &height, &channels, 4);

	if (!data)
	{
		std::cout << "Failed to load image: " << imagePath << std::endl;
		return;
	}

	glGenTextures(1, &id);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

PNGTexture::PNGTexture(PNGTexture&& other) noexcept
{
	id = other.id;
	width = other.width;
	height = other.height;
	channels = other.channels;

	other.id = 0;
	other.width = 0;
	other.height = 0;
	other.channels = 0;
}

PNGTexture& PNGTexture::operator=(PNGTexture&& other) noexcept
{
	id = other.id;
	width = other.width;
	height = other.height;
	channels = other.channels;

	other.id = 0;
	other.width = 0;
	other.height = 0;
	other.channels = 0;

	return *this;
}

PNGTexture::~PNGTexture() noexcept
{
	glDeleteTextures(1, &id);
}

void PNGTexture::bind(unsigned int activeTexture) const
{
	glActiveTexture(GL_TEXTURE0 + activeTexture);
	glBindTexture(GL_TEXTURE_2D,id);
}

