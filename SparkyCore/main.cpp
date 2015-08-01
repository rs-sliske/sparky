#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/utils/fileutils.h"
#include "src\graphics\shader.h"

#define USE_TRIANGLE_TEST 1
#define SHOW_WINDOW 1

#define println(a) std::cout << a << std::endl

int main() {
	using namespace sparky;
	using namespace maths;
	using namespace graphics;

	graphics::Window window("Sparky", 800, 600);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	GLfloat vertices[] =
	{
		0, 0, 0,
		8, 0, 0,
		0, 3, 0,
		0, 3, 0,
		8, 3, 0,
		8, 0, 0
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");
	shader.enable();

	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", mat4::translate(vec3(4, 3, 0)));

	shader.setUniform2f("light_pos", vec2(4, 1.5f));
	shader.setUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));
	double xp = 0, yp = 0;

	while (!window.closed()){
		window.clear();
		window.getMousePos(xp, yp);
		vec2 mousePos(xp, yp);
		mousePos -= vec2(400.0f, 300.0f);
		mousePos /= vec2(800.0f / 16.0f, -600.0f / 9.0f);
		mousePos += vec2(4.0f, 1.5f);
		shader.setUniform2f("light_pos", mousePos);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		window.update();
	}

	return 0;
}