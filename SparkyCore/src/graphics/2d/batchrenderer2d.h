#pragma once

#include <cstddef>

#include "renderer2d.h"
#include "../buffers/buffers.h"


#define RENDERER_MAX_SPRITES 100000

#define RENDERER_VERTEX_SIZE sizeof(VertexData)
#define RENDERER_SPRITE_SIZE RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_COLOR_INDEX 1

namespace sparky{ namespace graphics{

	class BatchRenderer2D : Renderer2D
	{
	private:
		GLuint m_VAO;
		GLuint m_VBO;

		IndexBuffer *m_IBO;
		GLsizei m_count;

		VertexData* m_buffer;
		
	public:
		BatchRenderer2D();
		~BatchRenderer2D();
		
		void submit(const Renderable2D* renderable) override;
		void begin();
		void end();
		void flush() override;
	private:
		void init();
	};

}}