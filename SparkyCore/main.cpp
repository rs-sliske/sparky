#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include "src/graphics/window.h"

#define USE_TRIANGLE_TEST 1;

int main() {

	sparky::graphics::Window window("Sparky", 800, 600);

	glClearColor(0.2f, 0.3f, 0.9f, 0.5f);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	while (!window.closed()){
		window.clear();
#if USE_TRIANGLE_TEST
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f( 0.0f,  0.5f);
		glVertex2f( 0.5f, -0.5f);
		glEnd();

#else

		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);

#endif

		window.update();
	}

	return 0;
}