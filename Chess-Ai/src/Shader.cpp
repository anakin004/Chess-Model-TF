#include "Shader.h"
#include <glm/gtc/type_ptr.hpp> // for value_ptr


#include <glad/glad.h>


std::unordered_map<std::string, Shader*> Shader::m_ShaderLocationCache = {};

// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const std::string& filepath) : m_UniformLocationCache()
{

	// Read vertexFile and fragmentFile 
	ShaderProgramSource shaderCode = get_file_contents(filepath);


	// Convert the shader source strings into character arrays
	const char* vertexSource = shaderCode.VertexSource.c_str();
	const char* fragmentSource = shaderCode.FragmentSource.c_str();


	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	compile_errors(vertexShader, "VERTEX");

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	compile_errors(fragmentShader, "FRAGMENT");

	m_ID = glCreateProgram();

	glAttachShader(m_ID, vertexShader);
	glAttachShader(m_ID, fragmentShader);
	compile_errors(vertexShader, "PROGRAM");

	glLinkProgram(m_ID);
	glValidateProgram(m_ID);


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

ShaderProgramSource get_file_contents(const std::string& filename)
{
	std::ifstream in(filename.c_str(), std::ios::binary);


	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	// 1 for vert and 1 for frag
	std::stringstream ss[2];

	ShaderType type = ShaderType::NONE;


	if (in)
	{


		std::string line("");


		while (getline(in, line))
		{

			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{

					type = ShaderType::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos)
				{

					type = ShaderType::FRAGMENT;

				}
			}
			
			else {
				ss[(int)type] << line << "\n";
			}
		}

		return { ss[0].str() , ss[1].str() };
	}
	throw(errno);
}


void Shader::set_uniform_mat4f(const std::string& uni_name, const glm::mat4& matrix)
{
	// obv id, then num of matrix's which is 1, then whether or not we have a row
	// major matrix or column to transpose, since its col we dont
	glUniformMatrix4fv(get_uniform(uni_name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::set_uniform_3fs(const std::string& uni_name, const glm::vec3 vector[6])
{
	glUniform3fv(get_uniform(uni_name), 6, glm::value_ptr(vector[0]));
}


void Shader::init_shaders()
{

	Shader* main_shader = new Shader("Resources/shaders/shader.glsl");

	m_ShaderLocationCache["main_shader"] = main_shader;

	// binding texture0 for worldatlas in main shader
	main_shader->bind();
	main_shader->set_uniform_1i("tex", 0);

	main_shader->unbind();



}


void Shader::bind_by_id(GLint ID)
{
	glUseProgram(ID);
}


// Activates the Shader Program
void Shader::bind() const
{
	glUseProgram(m_ID);
}
void Shader::unbind() const
{
	glUseProgram(0);
}


void Shader::delete_shaders()
{
	for (auto& it : m_ShaderLocationCache) 
	{
		glDeleteProgram(it.second->get_ID());
		delete it.second;
	}
}


GLint Shader::get_uniform(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];
	
	GLint loc = glGetUniformLocation(m_ID, name.c_str());
	if (loc == -1)
		std::cout << "Warning: uniform: " << name << " does not exist" << std::endl; 
	else
		m_UniformLocationCache[name] = loc;

	return loc;
}

Shader* Shader::get_shader(const std::string& name)
{
	if (m_ShaderLocationCache.find(name) != m_ShaderLocationCache.end())
		return m_ShaderLocationCache[name];

	else
		std::cout << "Couldnt find shader name " << name << '\n';
	

	return nullptr;
}

void Shader::set_uniform_vec4f(const std::string& uni_name, const glm::vec4& vector)
{
	glUniform4f(get_uniform(uni_name), vector.x, vector.y, vector.z, vector.w);

}

void Shader::set_uniform_vec3f(const std::string& uni_name, const glm::vec3& vector)
{
	glUniform3f(get_uniform(uni_name), vector.x, vector.y, vector.z);

}

void Shader::set_uniform_1f(const std::string& uni_name, const float val)
{
	glUniform1f(get_uniform(uni_name), val);
}

void Shader::set_uniform_1i(const std::string& uni_name, const int val)
{
	glUniform1i(get_uniform(uni_name), val);
}


// Checks if the different Shaders have compiled properly
void Shader::compile_errors(unsigned int shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}

