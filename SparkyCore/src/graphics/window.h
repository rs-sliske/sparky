#pragma once
#include <GLFW\glfw3.h>

namespace sparky { namespace graphics {

	class Window {
	private:
		const char *m_title;
		int m_width, m_height;
		GLFWwindow *m_window;
	public:
		Window(const char *name, int width, int height);
		~Window();
		void update();
		bool closed() const;
		void clear() const;

		inline int getWidth() const { return m_width; }
		inline int getHeight() const { return m_height; }
	private:
		bool init();

		//friend void window_size_callback(GLFWwindow *window, int width, int height);
	};
}
}