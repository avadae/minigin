#pragma once
#include <string>

struct TTF_Font;
namespace dae
{
	/**
	 * Simple RAII wrapper for a TTF_Font
	 */
	class Font final
	{
	public:
		TTF_Font* GetFont() const;
		explicit Font(const std::string& fullPath, float size);
		~Font();

		Font(const Font &) = delete;
		Font(Font &&) = delete;
		Font & operator= (const Font &) = delete;
		Font & operator= (const Font &&) = delete;
	private:
		TTF_Font* m_font;
	};
}
