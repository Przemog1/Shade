#pragma once
#include "Vertex.h"

class SSBO
{
public:
	SSBO(unsigned int binding);
	~SSBO() noexcept;

	SSBO(const SSBO&) = delete;
	SSBO& operator=(SSBO&) = delete;

	SSBO(SSBO&& other) noexcept;
	SSBO& operator=(SSBO&& other) noexcept;
	
	void bind() const;
	void bind(unsigned int binding) const;
	void setData(const void* data, unsigned int dataSize);

	inline bool isValid() const { return SSBOID; }
private:
	unsigned int SSBOID;
};
