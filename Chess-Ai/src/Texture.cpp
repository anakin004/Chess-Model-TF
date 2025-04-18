#include "Texture.h"


#include <glad/glad.h>

std::array<Texture, 4> Texture::m_Textures;


// @param numSpritesVert the number of sprites on a vertical column so when we do height/numSpritesVert it will give sprite size
Texture::Texture(const std::string& path)
	: m_ID(0), m_FilePath(path), m_ImgBytes(nullptr), m_Width(0), m_BPP(0), m_Height(0)
{

	stbi_set_flip_vertically_on_load(true);
	m_ImgBytes = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 0);

	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_ImgBytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	if (m_ImgBytes)
		stbi_image_free(m_ImgBytes);


}


Texture& Texture::get_texture(int index) {
	return m_Textures[index];
}

void Texture::init_textures()
{
	m_Textures[0] = Texture("resources/textures/chess_board.png");
}


void Texture::bind(int slot /*= 0*/) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::delete_textures()
{
	for (auto& tex : m_Textures)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteTextures(1, &tex.get_texture_ID());
	}
}
