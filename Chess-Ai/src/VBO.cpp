#include"VBO.h"
#include <vector>


VBO::VBO()
{
	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}


void VBO::load_buffer(std::vector<Vertex>& vertices)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
}


VBO::~VBO()
{
	glDeleteBuffers(1, &m_ID);
}

void VBO::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VBO::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
