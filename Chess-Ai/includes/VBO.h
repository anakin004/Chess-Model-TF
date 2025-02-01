#pragma once

#include <glad/glad.h>
#include "util.h"
#include <vector>

class VBO
{
public:	

	VBO(std::vector<Vertex>& vertices);

	~VBO();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetID() { return m_ID; };
private:
	unsigned int m_ID

};

