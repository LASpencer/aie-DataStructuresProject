#include "stdafx.h"
#include "ResourceManager.h"

TexturePtr ResourceManager::getTexture(const std::string & filename)
{
	if (!m_textures.exists(filename)) {
	m_textures.insert(filename, std::make_shared<Resource<aie::Texture>>(filename));
	}
	return m_textures.at(filename);
}

AudioPtr ResourceManager::getAudio(const std::string & filename)
{
	if (!m_audio.exists(filename)) {
		m_audio.insert(filename, std::make_shared<Resource<aie::Audio>>(filename));
	}
	return m_audio.at(filename);
}

FontPtr ResourceManager::getFont(const std::string & filename, unsigned short size)
{
	if (!m_fonts.exists(filename)) {
		m_fonts.insert(filename, las::Map<unsigned short, FontPtr>({ std::make_pair(size, std::make_shared<FontResource>(filename, size)) }));
	} else if (!m_fonts.at(filename).exists(size)){
		m_fonts.at(filename).insert(size, std::make_shared<FontResource>(filename, size));
	}
	return m_fonts.at(filename).at(size);
}

size_t ResourceManager::size(ResourceType type)
{
	switch (type) {
	case(texture):
		return m_textures.size();
	case (audio):
		return m_audio.size();
	case(font):
	{	size_t total = 0;
		for (std::pair<std::string, las::Map<unsigned short, FontPtr >> fontMap : m_fonts) {
			total += fontMap.second.size();
		}
		return total;
	}
	default:
		throw std::invalid_argument("Type must be valid ResourceType");
	}
}

void ResourceManager::collectGarbage()
{
	las::Map<std::string, TexturePtr>::iterator textureIter = m_textures.begin();
	while (textureIter != m_textures.end()) {
		if (textureIter->second.use_count() == 1) {
			textureIter = m_textures.erase(textureIter);
		}
		else {
			++textureIter;
		}
	}
	las::Map<std::string, AudioPtr>::iterator audioIter = m_audio.begin();
	while (audioIter != m_audio.end()) {
		if (audioIter->second.use_count() == 1) {
			audioIter = m_audio.erase(audioIter);
		}
		else {
			++audioIter;
		}
	}
	las::Map<std::string, las::Map<unsigned short, FontPtr>>::iterator fontIter = m_fonts.begin();
	while (fontIter != m_fonts.end()) {
		las::Map<unsigned short, FontPtr>::iterator it = fontIter->second.begin();
		while (it != fontIter->second.end()) {
			if (it->second.use_count() == 1) {
				it = fontIter->second.erase(it);
			} else {
				++it;
			}
		}
		++fontIter;
	}
}
