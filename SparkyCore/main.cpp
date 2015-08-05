#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <vector>
#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/utils/fileutils.h"
#include "src\graphics\shader.h"

#include "src/graphics/buffers/buffers.h"

#include "src/graphics/2dgraphics.h"
#include "src/graphics/3dgraphics.h"
#include "src\utils\timer.h"


#define USE_BATCH 1

#define WINDOW_WIDTH  16.0f
#define WINDOW_HEIGHT 9.0f

#define println(a) std::cout << a << std::endl

void genSprites(float size, std::deque<sparky::graphics::Renderable2D*>& queue, sparky::graphics::Window& window, sparky::graphics::Shader& shader);
void genSprites3d(float size, int across, int depth, std::deque<sparky::graphics::Renderable3D*>& queue, sparky::graphics::Window& window);

int main() {
	using namespace sparky;
	using namespace maths;
	using namespace graphics;

	graphics::Window window("Sparky", 1280, 720);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	Shader shader("basic");

	std::deque<Renderable3D*> renderables;

	mat4 ortho = mat4::orthographic(0.0f, WINDOW_WIDTH, 0.0f, WINDOW_HEIGHT, -1.0f, 1.0f);
	mat4 perspective = mat4::perspective(70.0f, window.getWidth() / window.getHeight(), 0.01f, 1000.0f);
	shader.enable();

	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("pr_matrix", perspective);
	
	
#if USE_BATCH
	BatchRenderer3D renderer;
#else
	Simple2DRenderer renderer;
#endif

	genSprites3d(0.1f,10,50, renderables, window);

	println(renderables.size() << " sprites");

	Timer timer;
	Timer timer2;
	//timer.reset();
	long float t = 0;
	unsigned short frames = 0;
	vec2 mousePosModifier(WINDOW_WIDTH / window.getWidth(), -(WINDOW_HEIGHT / window.getHeight()));
	vec2 flipY(0, WINDOW_HEIGHT);

	vec3 cameraPos;
	vec3 movex(0.1f, 0, 0);
	vec3 movey(0, 0, 0.1f);

	while (!window.closed()){	
		float f = timer2.elapsed();
		if (window.isKeyPressed(GLFW_KEY_LEFT_CONTROL)){
			f *= 50;
		}
		else{
			f *= 5;
		}
		timer2.reset();
		frames++;
		window.clear();

		if (window.isKeyPressed(GLFW_KEY_UP)){
			cameraPos += (movey * f);
		}
		if (window.isKeyPressed(GLFW_KEY_DOWN)){
			cameraPos -= (movey * f);
		}
		if (window.isKeyPressed(GLFW_KEY_LEFT)){
			cameraPos += (movex * f);
		}
		if (window.isKeyPressed(GLFW_KEY_RIGHT)){
			cameraPos -= (movex * f);
		}
		
		

		vec2 mouse(0,window.getHeight());
		//window.getMousePosition(mouse);
		shader.setUniform2f("light_pos", flipY + mouse * mousePosModifier);
		shader.setUniformMat4("ml_matrix", mat4::translate(cameraPos));
		int sprites = 0;
		int s = 0;
		renderer.begin();
		for (Renderable3D* r:renderables)
		{
			if (sprites > 10000000){
				renderer.end();
				renderer.flush();
				renderer.begin();
				sprites = 0;
				s++;
			}
			sprites++;
			renderer.submit(&(*r));
		}
		renderer.end();
		renderer.flush();
		window.update();
		
		if ((timer.elapsed() - t) > 1.0f){
			t += 1.0f;
			printf("%d fps - %d draw calls \n",frames,s);
			frames = 0;
		}
	}
	
	return 0;
}

void genSprites(float size, std::deque<sparky::graphics::Renderable2D*>& queue, sparky::graphics::Window& window, sparky::graphics::Shader& shader){
	sparky::maths::vec2 s(size * 0.9f, size * 0.9f);
	 for (float y = size * 0.05; y < WINDOW_HEIGHT; y += size){
		 for (float x = size * 0.05; x < WINDOW_WIDTH; x += size){
			queue.push_back(new
#if USE_BATCH
				sparky::graphics::Renderable2D
#else
				sparky::graphics::StaticSprite
#endif
				(sparky::maths::vec3(x, y, 0),
				s,
				sparky::maths::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 1)
#if USE_BATCH
#else
				, shader
#endif
				));
		}
	}
}

void genSprites3d(float size,int across, int depth, std::deque<sparky::graphics::Renderable3D*>& queue, sparky::graphics::Window& window){
	sparky::maths::vec3 s(size * 0.9f,0.01f, size * 0.9f);
	for (float y = size * 0.05; y < 50; y += size){
		for (float x = size * 0.05; x < 10; x += size){
			queue.push_back(new
				sparky::graphics::Renderable3D
				(sparky::maths::vec3(x - (WINDOW_WIDTH/2), -0.5, y-1),
				s,
				sparky::maths::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 1)
				));
		}
	}
}
