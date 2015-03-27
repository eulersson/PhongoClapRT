#include "Renderer.h"

Renderer::Renderer(Film &film)
{
  m_film = &film;
  m_width = m_film->m_width;
  m_height = m_film->m_height;
}

Renderer::~Renderer()
{

}
