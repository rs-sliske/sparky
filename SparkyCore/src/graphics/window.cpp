#include "window.h"
#include <iostream>

namespace sparky { namespace graphics {	

	bool Window::m_keys[MAX_KEYS];
	bool Window::m_buttons[MAX_BUTTONS];
	double Window::mx;
	double Window::my;

	Window::Window(const char *title, int width, int height){
		m_title = title;
		m_width = width;
		m_height = height;
		
		for (int i = 0; i < MAX_KEYS; i++){
			m_keys[i] = false;
		}
		for (int i = 0; i < MAX_BUTTONS; i++){
			m_buttons[i] = false;
		}
		
		if (!init()){
			glfwTerminate();
		}

		
	}

	Window::~Window(){
		glfwTerminate();
	}

	bool Window::init(){
		if (!glfwInit())		{
			std::cout << "failed to initialize GLFW" << std::endl;
			return false;
		}
		m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
		if (!m_window){
			std::cout << "failed to create window" << std::endl;
			return false;
		}
		glfwMakeContextCurrent(m_window);

		glfwSetWindowUserPointer(m_window, this);

		setCallbacks();

		if (glewInit() != GLEW_OK){
			std::cout << "failed to initialize GLEW" << std::endl;
			return false;
		}

		std::cout << "OpenGL : " << glGetString(GL_VERSION) << std::endl;

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

	bool Window::isKeyPressed(unsigned int keycode){
		if (keycode < MAX_KEYS){
			return m_keys[keycode];
		}
		return false;
	}
	bool Window::isButtonPressed(unsigned int button){
		if (button < MAX_BUTTONS){
			return m_buttons[button];
		}
		return false;
	}

	void Window::getMousePos(double& x, double& y){
		x = mx;
		y = my;
	}

	void Window::setCallbacks() const {
		glfwSetWindowSizeCallback(m_window, window_size_callback);
		glfwSetKeyCallback(m_window, key_callback);
		glfwSetCursorPosCallback(m_window, cursor_position_callback);
		glfwSetMouseButtonCallback(m_window, mouse_button_callback);
	}

	void window_size_callback(GLFWwindow *window, int width, int height){
		glViewport(0, 0, width, height);

		Window *win = (Window*)glfwGetWindowUserPointer(window);		
		win->m_width = width;
		win->m_height = height;		
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
		Window *win = (Window*) glfwGetWindowUserPointer(window);
		win->m_keys[key] = (action != GLFW_RELEASE);
		
	}

	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
		Window *win = (Window*)glfwGetWindowUserPointer(window);
		win->mx = xpos;
		win->my = ypos;
	}
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
		Window *win = (Window*)glfwGetWindowUserPointer(window);
		win->m_buttons[button] = (action != GLFW_RELEASE);
	}



		
	
}}