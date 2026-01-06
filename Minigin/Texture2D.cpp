#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
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
    m_texture = IMG_LoadTexture(
        Renderer::GetInstance().GetSDLRenderer(),
        fullPath.c_str()
    );

    if (!m_texture)
    {
        throw std::runtime_error(
            std::string("Failed to create texture: ") + SDL_GetError()
        );
    }
}

dae::Texture2D::Texture2D(SDL_Texture* texture)	: m_texture{ texture } 
{
	assert(m_texture != nullptr);
}

