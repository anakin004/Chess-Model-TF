#pragma once

#include <glad/glad.h>
#include "VBO.h"
#include "util.h"

class VAO
{
public:

	VAO();
	~VAO();

	void link_attrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset );
	void bind() const;
	void unbind() const;

	inline uint32_t get_ID() const { return m_ID; };
private:
	uint32_t m_ID;

};
