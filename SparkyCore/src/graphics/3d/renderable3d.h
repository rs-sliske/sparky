#pragma once

#include "../buffers/buffers.h"
#include "../../maths/maths.h"
#include "../shader.h"

namespace sparky { namespace graphics {
	struct VertexData3D
	{
		maths::vec3 vertex;
		//maths::vec4 color;
		unsigned int color;
	};

	class Renderable3D
	{
	protected:
		maths::vec3 m_position;
		maths::vec3 m_size;
		maths::vec4 m_color;

	public:
		Renderable3D(maths::vec3 position, maths::vec3 size, maths::vec4 color)
			: m_position(position), m_size(size), m_color(color)
		{
			
		}

	public:
		inline const maths::vec3& getPosition() const { return m_position; }
		inline const maths::vec3& getSize() const { return m_size; }
		inline const maths::vec4& getColor() const { return m_color; }

		

	};

}}