#pragma once

#include <glad/glad.h>
#include "util.h"
#include <vector>

class VBO
{
public:	


	VBO();
	~VBO();

	void load_buffer(std::vector<Vertex>& vertices);

	void bind() const;
	void unbind() const;

	inline uint32_t get_ID() { return m_ID; };

private:
	uint32_t m_ID;

};

