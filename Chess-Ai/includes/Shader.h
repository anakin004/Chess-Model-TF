#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <unordered_map>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>




struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};


ShaderProgramSource get_file_contents(const std::string& filename);

class Shader
{

	public:
		GLuint m_ID;
		Shader() {};
		Shader(const std::string& filename);
		static void delete_shaders();
		static void init_shaders();

		void bind_by_id(GLint ID);
		void set_uniform_1f(const std::string& uni_name, const float val);
		void set_uniform_1i(const std::string& uni_name, const GLint val);
		void set_uniform_mat4f(const std::string& uni_name, const glm::mat4& matrix);
		void set_uniform_vec3f(const std::string& uni_name, const glm::vec3& vector);
		void set_uniform_vec4f(const std::string& uni_name, const glm::vec4& vector);
		void set_uniform_3fs(const std::string& uni_name, const glm::vec3 vector[6]);

		GLint get_uniform(const std::string& uni_name);
		static Shader* get_shader(const std::string& shader_name);
			
		void bind() const;
		void unbind() const;

		inline GLint get_ID() { return m_ID; };

	private:

		void compile_errors(unsigned int shader, const char* type);


		std::unordered_map<std::string, GLint> m_UniformLocationCache;
		static std::unordered_map<std::string, Shader*> m_ShaderLocationCache;
};
