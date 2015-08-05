#pragma once

#include "renderer3d.h"
#include "../buffers/buffers.h"


#define RENDERER_MAX_SPRITES_3 100000

#define RENDERER_VERTEX_SIZE_3 sizeof(VertexData3D)
#define RENDERER_SPRITE_SIZE_3 RENDERER_VERTEX_SIZE_3 * 4
#define RENDERER_BUFFER_SIZE_3 RENDERER_SPRITE_SIZE_3 * RENDERER_MAX_SPRITES_3
#define RENDERER_INDICES_SIZE_3 RENDERER_MAX_SPRITES_3 * 36

#define SHADER_VERTEX_INDEX_3 0
#define SHADER_COLOR_INDEX_3 1

namespace sparky{ namespace graphics{

	class BatchRenderer3D : Renderer3D
	{
	private:
		GLuint m_VAO;
		GLuint m_VBO;

		IndexBuffer *m_IBO;
		GLsizei m_count;

		VertexData3D* m_buffer;
		
	public:
		BatchRenderer3D();
		~BatchRenderer3D();
		
		void submit(const Renderable3D* renderable) override;
		void begin();
		void end();
		void flush() override;
	private:
		void init();
	};

}}