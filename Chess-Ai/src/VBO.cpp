#include"VBO.h"
#include <vector>


VBO::VBO(std::vector<Vertex>& vertices))
{
	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);

	// will be static since only chess board + pieces need to be rendered
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), (void*)&vertices[0], GL_STATIC_DRAW);
}

VBO::~VBO()
{
	glDeleteBuffers(1, &m_ID);
}

void VBO::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VBO::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
