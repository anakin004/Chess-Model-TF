#include "EBO.h"



EBO::EBO()
{
	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void EBO::load_buffer(uint32_t* indices, uint32_t numIndices)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(uint32_t) * numIndices , indices));
}

EBO::~EBO()
{
	glDeleteBuffers(1, &m_ID);
}


void EBO::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void EBO::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

