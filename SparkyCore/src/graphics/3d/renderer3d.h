#pragma once

#include <GL/glew.h>
#include "../../maths/maths.h"
#include "renderable3d.h"


namespace sparky {
	namespace graphics {
		class Renderer3D
		{
		public:
			Renderer3D(){}
			~Renderer3D(){}
			virtual void begin() = 0;
			virtual void end() = 0;
			virtual void submit(const Renderable3D* renderable) = 0;
			virtual void flush() = 0;
		};


		

	}
}