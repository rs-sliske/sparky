#pragma once
#include "renderable2d.h"
#include "sprite.h"
namespace sparky {	namespace graphics {

	class StaticSprite : public Renderable2D {
	private:
		VertexArray *m_vertexArray;
		IndexBuffer *m_indexBuffer;
		Shader& m_shader;
	public:
		StaticSprite(float x, float y, float width, float height, 
			const maths::vec4& color, Shader& shader);
		StaticSprite(maths::vec2 pos, maths::vec2 size,
			const maths::vec4& color, Shader& shader)
			: StaticSprite(pos.x, pos.y, size.x, size.y, color, shader){}
		StaticSprite(maths::vec3 pos, maths::vec2 size,
			const maths::vec4& color, Shader& shader)
			: StaticSprite(pos.x, pos.y, size.x, size.y, color, shader){}

		virtual ~StaticSprite();

		inline const VertexArray* getVAO() const { return m_vertexArray; }
		inline const IndexBuffer* getIBO() const { return m_indexBuffer; }
		inline Shader& getShader() const { return m_shader; }

		inline const maths::vec3& getPosition() const { return m_position; }
		inline const maths::vec2& getSize() const { return m_size; }
		inline const maths::vec4& getColor() const { return m_color; }
	};

}}