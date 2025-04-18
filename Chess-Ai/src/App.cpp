#include "App.h"
#include "util.h"
#include "Texture.h"
#include "Shader.h"
#include "Board.h"
#include <iostream>


void App::run()
{

	if (!init()) return;

	Board chess_board;

	while (!glfwWindowShouldClose(m_Window))
	{

		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	Shader::delete_shaders();
	Texture::delete_textures();
}

bool App::init()
{
	bool success = true;

	// init GLFW
	if (!glfwInit())
		success = false;

	else
	{

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Create window
		m_Window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess", NULL, NULL);
		if (m_Window == NULL)
		{
			std::cout << "Failed to create GLFW window\n";
			glfwTerminate();
			success = false;
		}

		glfwMakeContextCurrent(m_Window);
		glfwSwapInterval(1);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD\n";
			success = false;
		}

		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	}


	Texture::init_textures();
	Shader::init_shaders();

	return success;
}