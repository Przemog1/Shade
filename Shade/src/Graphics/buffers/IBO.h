#pragma once
#include "Vertex.h"

class IBO
{
public:
	IBO(const unsigned int* indices, unsigned int count);
	IBO();
	~IBO();

	IBO(const IBO&) = delete;
	IBO& operator=(IBO&) = delete;

	IBO(IBO&& other) noexcept;
	IBO& operator=(IBO&& other) noexcept;

	void bind() const;
	void setData(const unsigned int* indices, unsigned int count);

	inline bool isValid() const { return iboID; }
	inline unsigned int getIndicesCount() const { return indicesCount; }
private:
	unsigned int iboID;
	unsigned int indicesCount;
};
