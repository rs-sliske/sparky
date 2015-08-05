#include "batchrenderer3D.h"

namespace sparky{ namespace graphics {

		BatchRenderer3D::BatchRenderer3D()
		{
			init();
		}

		BatchRenderer3D::~BatchRenderer3D()
		{
			delete m_IBO;
			glDeleteBuffers(1, &m_VBO);
		}

		void BatchRenderer3D::init()
		{
			glGenVertexArrays(1, &m_VAO);
			glBindVertexArray(m_VAO);

			glGenBuffers(1, &m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE_3, NULL, GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(SHADER_VERTEX_INDEX_3);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX_3);

			glVertexAttribPointer(SHADER_VERTEX_INDEX_3, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE_3, (const GLvoid *)offsetof(VertexData3D, VertexData3D::vertex));
			glVertexAttribPointer(SHADER_COLOR_INDEX_3, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE_3, (const GLvoid *)offsetof(VertexData3D, VertexData3D::color));

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLuint* indices = new GLuint[RENDERER_INDICES_SIZE_3];
			int offset = 0;
			for (int i = 0; i < RENDERER_INDICES_SIZE_3; i += 24){
				//bottom
				indices[i + 0] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;
				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;

				//top
				indices[i + 6 + 0] = offset + 4 + 0;
				indices[i + 6 + 1] = offset + 4 + 1;
				indices[i + 6 + 2] = offset + 4 + 2;
				indices[i + 6 + 3] = offset + 4 + 2;
				indices[i + 6 + 4] = offset + 4 + 3;
				indices[i + 6 + 5] = offset + 4 + 0;

				//left
				indices[i + 12 + 0] = offset + 0 + 0;
				indices[i + 12 + 1] = offset + 0 + 1;
				indices[i + 12 + 2] = offset + 4 + 2;
				indices[i + 12 + 3] = offset + 4 + 2;
				indices[i + 12 + 4] = offset + 4 + 3;
				indices[i + 12 + 5] = offset + 0 + 0;

				//right
				indices[i + 18 + 0] = offset + 4 + 0;
				indices[i + 18 + 1] = offset + 4 + 1;
				indices[i + 18 + 2] = offset + 0 + 2;
				indices[i + 18 + 3] = offset + 0 + 2;
				indices[i + 18 + 4] = offset + 0 + 3;
				indices[i + 18 + 5] = offset + 4 + 0;
	

				offset += 8;
			}

			m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE_3);
			delete[] indices;
			glBindVertexArray(0);
		}

		void BatchRenderer3D::begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			m_buffer = (VertexData3D*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}


		void BatchRenderer3D::submit(const Renderable3D* renderable)
		{
			const maths::vec3 pos = renderable->getPosition();
			const maths::vec4 col = renderable->getColor();
			const maths::vec3 size = renderable->getSize();

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

			m_buffer->vertex = maths::vec3(pos.x, pos.y, pos.z + size.z);
			m_buffer->color = c;
			m_buffer++;

			m_buffer->vertex = maths::vec3(pos.x, pos.y + size.y, pos.z + size.z);
			m_buffer->color = c;
			m_buffer++;

			m_buffer->vertex = maths::vec3(pos.x + size.x, pos.y + size.y, pos.z + size.z);
			m_buffer->color = c;
			m_buffer++;

			m_buffer->vertex = maths::vec3(pos.x + size.x, pos.y, pos.z + size.z);
			m_buffer->color = c;
			m_buffer++;

			m_count += 36;

			if (m_count > RENDERER_INDICES_SIZE_3 - 36){
				//printf("refreshed indices with %d sprites\n", m_count/6);
				flush();
			}
		}

		void BatchRenderer3D::end()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void BatchRenderer3D::flush()
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