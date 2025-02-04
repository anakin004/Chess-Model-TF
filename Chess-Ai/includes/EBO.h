#pragma once

#include <glad/glad.h>
#include "util.h"

class EBO
{

public:


	void LoadBuffer(uint32_t* indices, uint32_t numIndices);

	EBO();

	// Deletes the EBO
	~EBO();

	// Binds the EBO
	void Bind() const;
	// Unbinds the EBO
	void Unbind() const;

	inline uint32_t GetID() { return m_ID; };
	
private:
	
	uint32_t m_ID;
};
