#include "simple2Drenderer.h"
#include "renderable2d.h"

namespace sparky { namespace graphics {
	Renderer2D::Renderer2D()
	{
	}


	Renderer2D::~Renderer2D()
	{
	}

	void Simple2DRenderer::submit(const Renderable2D* renderable)
	{
		m_renderQueue.push_back((StaticSprite*)renderable);
	}

	

	void Simple2DRenderer::flush()
	{
		while (!m_renderQueue.empty()){
			const StaticSprite* renderable = m_renderQueue.front();
			renderable->getVAO()->bind();
			renderable->getIBO()->bind();

			renderable->getShader().setUniformMat4("ml_matrix", maths::mat4::translate(renderable->getPosition()));
			glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

			renderable->getIBO()->unbind();
			renderable->getVAO()->unbind();

			m_renderQueue.pop_front();

		}
	}

}
}