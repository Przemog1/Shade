#pragma once
#include "Vertex.h"

class VBO
{
public:
	VBO(const Vertex* vertexArray, unsigned int count);
	VBO();
	~VBO();

	VBO(const VBO&) = delete;
	VBO& operator=(VBO&) = delete;

	VBO(VBO&& other) noexcept;
	VBO& operator=(VBO&& other) noexcept;

	void bind() const;
	void setData(const Vertex* vertexArray, unsigned int count);

	inline bool isValid() const { return vboID; }
private:
	unsigned int vboID;
};
