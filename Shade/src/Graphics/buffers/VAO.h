#pragma once
#include "Vertex.h"

class VAO
{
public:
	VAO();
	~VAO();

	void bind() const;
	void unbind() const;

	VAO(const VAO&) = delete;
	VAO& operator=(VAO&) = delete;

	VAO(VAO&& other) noexcept;
	VAO& operator=(VAO&& other) noexcept;

	inline bool isValid() const { return vaoID; }
private:
	unsigned int vaoID;
};

