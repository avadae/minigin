#pragma once
#include <filesystem>
#include <string>
#include <memory>
#include <map>
#include "Singleton.h"

namespace dae
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::filesystem::path& data);
		void Destroy();
		[[nodiscard]] std::shared_ptr<Texture2D> LoadTexture(const std::string& file);
		[[nodiscard]] std::shared_ptr<Font> LoadFont(const std::string& file, uint8_t size);
	private:
		std::filesystem::path m_dataPath;
		std::map<std::string, std::shared_ptr<Texture2D>> m_loadedTextures;
		std::map<std::pair<std::string, uint8_t>, std::shared_ptr<Font>> m_loadedFonts;

		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		virtual ~ResourceManager() = default;
		void UnloadUnusedResources();
	};
}
