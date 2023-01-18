#include <stdexcept>
#include <SDL_ttf.h>
#include "Font.h"

TTF_Font* dae::Font::GetFont() const {
	return m_font;
}

dae::Font::Font(const std::string& fullPath, unsigned int size) : m_font(nullptr), m_size(size)
{
	m_font = TTF_OpenFont(fullPath.c_str(), size);
	if (m_font == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

dae::Font::~Font()
{
	TTF_CloseFont(m_font);
}
