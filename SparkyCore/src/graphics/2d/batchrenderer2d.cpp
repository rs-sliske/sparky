#include "batchrenderer2d.h"

namespace sparky{ namespace graphics {

	BatchRenderer2D::BatchRenderer2D()
	{
		init();
	}

	BatchRenderer2D::~BatchRenderer2D()
	{
		delete m_IBO;
		glDeleteBuffers(1, &m_VBO);
	}

	void BatchRenderer2D::init()
	{		
		glGenVertexArrays(1, &m_VAO);		
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);

		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *)offsetof(VertexData, VertexData::vertex));
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid *)offsetof(VertexData, VertexData::color));
	
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	
		GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];
		int offset = 0;
		for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6){
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);
		delete[] indices;
		glBindVertexArray(0);
	}

	void BatchRenderer2D::begin()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		m_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}


	void BatchRenderer2D::submit(const Renderable2D* renderable)
	{		
		const maths::vec3 pos = renderable->getPosition();
		const maths::vec4 col = renderable->getColor();
		const maths::vec2 size = renderable->getSize();

		int r = col.x * 255.0f;
		int g = col.y * 255.0f;
		int b = col.z * 255.0f;
		int a = col.w * 255.0f;

		unsigned int c = a << 24 | b << 16 | g << 8 | r;

		m_buffer->vertex = pos;
		m_buffer->color = c;
		m_buffer++;

		m_buffer->vertex = maths::vec3(pos.x, pos.y + size.y, pos.z);
		m_buffer->color = c;
		m_buffer++;

		m_buffer->vertex = maths::vec3(pos.x + size.x, pos.y + size.y, pos.z);
		m_buffer->color = c;
		m_buffer++;

		m_buffer->vertex = maths::vec3(pos.x + size.x, pos.y, pos.z);
		m_buffer->color = c;
		m_buffer++;

		m_count += 6;

		if (m_count > RENDERER_INDICES_SIZE -6){
			//printf("refreshed indices with %d sprites\n", m_count/6);
			flush();
		}
	}

	void BatchRenderer2D::end()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void BatchRenderer2D::flush()
	{
		glBindVertexArray(m_VAO);
		m_IBO->bind();

		glDrawElements(GL_TRIANGLES, m_count, GL_UNSIGNED_INT, NULL);

		m_IBO->unbind();
		glBindVertexArray(0);

		m_count = 0;
	}

}
}