#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class App
{
public:

	App() = default;
	~App() = default;

	void run();



private:

	bool init();

	GLFWwindow* m_Window;
};