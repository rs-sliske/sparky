#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/utils/fileutils.h"
#include "src\graphics\shader.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#define USE_TRIANGLE_TEST 1
#define SHOW_WINDOW 1
#define USE_BUFFERS 1

#define println(a) std::cout << a << std::endl

int main() {
	using namespace sparky;
	using namespace maths;
	using namespace graphics;

	graphics::Window window("Sparky", 800, 600);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
#if USE_BUFFERS == 0
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
#else
	GLfloat vertices[] =
	{
		0, 0, 0,
		8, 0, 0,
		0, 3, 0,
		8, 3, 0
	};

	GLushort indices[] =
	{
		0, 1, 2,
		2, 3, 1
	};

	VertexArray vao;
	Buffer *vbo = new Buffer(vertices, 4 * 3, 3);
	IndexBuffer *ibo = new IndexBuffer(indices,6);

	vao.addBuffer(vbo, 0);

#endif
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
		mousePos -= vec2(0.0f, 600.0f);
		mousePos /= vec2(800.0f / 16.0f, -600.0f / 9.0f);
		
		shader.setUniform2f("light_pos", mousePos);
#if USE_BUFFERS	 == 0
		glDrawArrays(GL_TRIANGLES, 0, 6);
#else		
		vao.bind();
		ibo->bind();

		shader.setUniformMat4("ml_matrix", mat4::translate(vec3(5, 5, 0)));
		glDrawElements(GL_TRIANGLES, ibo->getCount(), GL_UNSIGNED_SHORT, 0);

		shader.setUniformMat4("ml_matrix", mat4::translate(vec3(3, 1, 0)));
		glDrawElements(GL_TRIANGLES, ibo->getCount(), GL_UNSIGNED_SHORT, 0);

		ibo->unbind();
		vao.unbind();
#endif
		window.update();
	}

	return 0;
}