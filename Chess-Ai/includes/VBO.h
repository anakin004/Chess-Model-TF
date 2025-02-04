#pragma once

#include <glad/glad.h>
#include "util.h"
#include <vector>

class VBO
{
public:	

	void LoadBuffer(std::vector<Vertex>& vertices, uint32_t numVerts);

	VBO();

	~VBO();

	void Bind() const;
	void Unbind() const;

	inline uint32_t GetID() { return m_ID; };

private:
	uint32_t m_ID;

};

