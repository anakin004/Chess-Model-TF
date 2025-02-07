#pragma once

#include <glad/glad.h>
#include "VBO.h"
#include "util.h"

class VAO
{
	GLuint m_ID;
public:

	// Constructor that generates a VAO ID
	VAO();
	~VAO();

	// Links a VBO to the VAO using a certain layout
	void link_attrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset );
	// Binds the VAO
	void bind() const;
	// Unbinds the VAO
	void unbind() const;

	inline GLuint get_ID() const { return m_ID; };

};
