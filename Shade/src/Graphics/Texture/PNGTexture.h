#pragma once
#include <string>

enum class TextureType {
	diffuse, specular
};


class PNGTexture
{
public:
	explicit PNGTexture(const std::string& imagePath);

	void bind(unsigned int activeTexture = 0) const;

	PNGTexture()
		: id(0), width(0), height(0), channels(0) {};

	void setTexture(const std::string& imagePath);

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }

	PNGTexture(PNGTexture&&) noexcept;
	PNGTexture& operator=(PNGTexture&&) noexcept;
	~PNGTexture() noexcept;


	PNGTexture(const PNGTexture&) = delete;
	PNGTexture& operator=(const PNGTexture&) = delete;
private:
	unsigned int id;
	int width;
	int height;
	int channels;
};
