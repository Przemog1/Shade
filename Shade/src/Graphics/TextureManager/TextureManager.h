#pragma once
#include <unordered_map>
#include <memory>
#include "../Texture/PNGTexture.h"


class TextureManager
{
public:
	void addTexture(const std::string& textureImagePath, const std::string& textureName);
	PNGTexture* getTexture(const std::string& name);
	static TextureManager& getTextureManager();
	
private:
	TextureManager() = default;
	~TextureManager();

	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;

	std::unordered_map<std::string, PNGTexture*> textures;
	PNGTexture emptyTexture;
};
