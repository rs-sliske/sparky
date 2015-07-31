#include <GLFW\glfw3.h>
#include <iostream>
#include "src/graphics/window.h"

int main() {

	sparky::graphics::Window window("Sparky", 800, 600);

	glClearColor(0.2f, 0.3f, 0.9f, 0.5f);

	std::cout << "OpenGL : " << glGetString(GL_VERSION) << std::endl;

	while (!window.closed()){
		window.clear();
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f( 0.0f,  0.5f);
		glVertex2f( 0.5f, -0.5f);
		glEnd();
		window.update();
	}

	return 0;
}