#pragma once
#include "util.h"

class EBO
{

public:


	void load_buffer(uint32_t* indices, uint32_t numIndices);


	EBO();

	// Deletes the EBO
	~EBO();

	// Binds the EBO
	void bind() const;
	// Unbinds the EBO
	void unbind() const;

	inline uint32_t get_ID() { return m_ID; };
	
private:
	
	uint32_t m_ID;
};
