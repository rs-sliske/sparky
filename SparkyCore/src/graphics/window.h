#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "..\maths\vec2.h"

#define MAX_KEYS 1024
#define MAX_BUTTONS 256

namespace sparky { namespace graphics {

	class Window {
	private:
		const char *m_title;
		int m_width, m_height;
		GLFWwindow *m_window;

		static bool m_keys[MAX_KEYS];
		static bool m_buttons[MAX_BUTTONS];
		static double mx, my;
	public:
		Window(const char *name, int width, int height);
		~Window();
		void update();
		bool closed() const;
		void clear() const;

		inline int getWidth() const { return m_width; }
		inline int getHeight() const { return m_height; }

		static  bool isKeyPressed(unsigned int keycode) ;
		static  bool isButtonPressed(unsigned int button);
		static  void getMousePosition(double& x, double& y);
		static  void getMousePosition(maths::vec2& pos);
	private:
		bool init();
		void setCallbacks() const;

		friend static void window_size_callback(GLFWwindow *window, int width, int height);
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

	};
}
}