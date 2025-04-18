#include "EBO.h"
#include <glad/glad.h>


EBO::EBO()
{
	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void EBO::load_buffer(uint32_t* indices, uint32_t numIndices)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uint32_t) * numIndices, indices, GL_STATIC_DRAW);
}

EBO::~EBO()
{
	glDeleteBuffers(1, &m_ID);
}


void EBO::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void EBO::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

