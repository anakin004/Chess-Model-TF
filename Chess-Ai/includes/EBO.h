#pragma once
#include "util.h"

class EBO
{

public:
	

	EBO();
	~EBO();

	void load_buffer(uint32_t* indices, uint32_t numIndices);


	void bind() const;
	void unbind() const;

	inline uint32_t get_ID() { return m_ID; };
	
private:
	
	uint32_t m_ID;
};
