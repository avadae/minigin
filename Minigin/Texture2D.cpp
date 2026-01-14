#include <SDL3/SDL.h>
#include "Texture2D.h"
#include "Renderer.h"
#include <stdexcept>

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_texture);
}

glm::vec2 dae::Texture2D::GetSize() const
{
    float w{}, h{};
    SDL_GetTextureSize(m_texture, &w, &h);
    return { w, h };
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_texture;
}

dae::Texture2D::Texture2D(const std::string &fullPath)
{
    SDL_Surface* surface = SDL_LoadPNG(fullPath.c_str());
    if (!surface)
    {
        throw std::runtime_error(
            std::string("Failed to load PNG: ") + SDL_GetError()
        );
    }

    m_texture = SDL_CreateTextureFromSurface(
        Renderer::GetInstance().GetSDLRenderer(),
        surface
    );

    SDL_DestroySurface(surface);

    if (!m_texture)
    {
        throw std::runtime_error(
            std::string("Failed to create texture from surface: ") + SDL_GetError()
        );
    }
}

dae::Texture2D::Texture2D(SDL_Texture* texture)	: m_texture{ texture } 
{
	assert(m_texture != nullptr);
}

