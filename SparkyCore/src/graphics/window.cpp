#include "window.h"
#include <iostream>


namespace sparky { namespace graphics {	

	void window_size_callback(GLFWwindow *window, int width, int height);

	Window::Window(const char *title, int width, int height){
		m_title = title;
		m_width = width;
		m_height = height;
		if (!init()){
			glfwTerminate();
		}
	}

	Window::~Window(){
		glfwTerminate();
	}

	bool Window::init(){
		if (!glfwInit())		{
			std::cout << "failed to initialise glfw" << std::endl;
			return false;
		}
		m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
		if (!m_window){
			glfwTerminate();
			std::cout << "failed to create window" << std::endl;
			return false;
		}
		glfwMakeContextCurrent(m_window);
		glfwSetWindowSizeCallback(m_window, window_size_callback);
		return true;
	}

	bool Window::closed() const {
		return glfwWindowShouldClose(m_window) == 1;
	}

	void Window::clear() const {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::update() {		
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void window_size_callback(GLFWwindow *window, int width, int height){
		glViewport(0, 0, width, height);
		//m_width = width;
		//m_height = height;
	}

		
	
}}