#include "TextureManager.h"
#include <iostream>

void TextureManager::addTexture(const std::string& textureImagePath, const std::string& textureName)
{
	textures.emplace(std::make_pair<std::string,PNGTexture*>(std::string(textureName), new PNGTexture(textureImagePath)));
}

const PNGTexture* TextureManager::getTexture(const std::string& name) const
{
	auto tex = textures.find(name);

	if (tex == textures.end())
	{
		std::cout << "Texture: " << name << " not found.\n\n";
		__debugbreak();
		return &emptyTexture;
	}
	else
	{
		return tex->second;
	}
		
		
}

TextureManager::~TextureManager()
{
	for (auto tex : textures)
	{
		delete tex.second;
	}

	textures.clear();
}

TextureManager& TextureManager::get()
{
	static TextureManager textureManager;
	return textureManager;
}