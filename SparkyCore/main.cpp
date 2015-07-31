#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include "src/graphics/window.h"
#include "src/maths/maths.h"

#define USE_TRIANGLE_TEST 1
#define println(a) std::cout << a << std::endl

int main() {
	using namespace sparky;
	using namespace maths;

	graphics::Window window("Sparky", 800, 600);

	glClearColor(0.2f, 0.3f, 0.9f, 0.5f);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	vec2 v1(6, 2);
	vec2 v2(1,-4);

	vec2 v3 = v1 * v2;

	float xp = 0, yp = 0;

	mat4 m1 = mat4::scale(vec3(2, 3, 1));
	mat4 m2 = mat4::translate(vec3(1, 3, 7));

	mat4 m3 = m1 * m2;
	println(m1);
	println(m2);
	println(m3);

	while (!window.closed()){
		window.clear();
		double x, y;
		window.getMousePos(x, y);
		if (window.isButtonPressed(GLFW_MOUSE_BUTTON_LEFT)){
			std::cout << x << ":" << y << std::endl;
		}
		if (window.isKeyPressed(GLFW_KEY_UP)){
			yp += 0.01f;
		}
		if (window.isKeyPressed(GLFW_KEY_DOWN)){
			yp -= 0.01f;
		}
		if (window.isKeyPressed(GLFW_KEY_LEFT)){
			xp -= 0.01f;
		}
		if (window.isKeyPressed(GLFW_KEY_RIGHT)){
			xp += 0.01f;
		}
		if (window.isButtonPressed)
#if USE_TRIANGLE_TEST
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f + xp, -0.5f + yp);
		glVertex2f( 0.0f + xp,  0.5f + yp);
		glVertex2f( 0.5f + xp, -0.5f + yp);
		glEnd();

#else

		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);

#endif

		window.update();
	}

	return 0;
}