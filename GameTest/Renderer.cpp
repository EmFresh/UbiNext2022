#include "stdafx.h"
#include "Renderer.h"

void Renderer::setCustumRender(std::function<void(util::GameObject*)> render)
{
	m_render = render;
}
