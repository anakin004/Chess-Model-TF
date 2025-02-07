#pragma once


#include <glad/glad.h>



#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <array>


#include <stb/stb_image.h>


#include "Shader.h"
#include "util.h"
#include "Block.h"



class Texture
{

private:

	GLuint m_ID;
	std::string m_FilePath;
	unsigned char* m_ImgBytes;
	int m_Width, m_Height, m_BPP, m_SpriteSize;
	static std::array<Texture, 4> m_Textures;

	Texture(const std::string& path, int);
	
	

public:

	Texture() = default;


	static void init_textures();
	static void delete_textures();

	void bind(GLuint slot = 0) const;
	void unbind() const;

	inline int get_width() const { return m_Width; }
	inline int get_height() const { return m_Height; }
	inline int get_sprite_size() const { return m_SpriteSize; };
	static Texture& get_texture(int index);

	inline GLuint& get_texture_ID() { return m_ID; };

};



