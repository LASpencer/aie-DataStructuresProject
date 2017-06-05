#pragma once
#include "stdafx.h"
#include "Map.h"
#include "Array.h"
#include "Texture.h"
#include "Audio.h"
#include "Font.h"

//TODO comment, document and test new resource manager
//TODO create specialized FontManager
template<class T>
class Resource
{
public:
	Resource(const std::string& filename) : m_filename(filename) {
		m_data = std::unique_ptr<T>(new T(filename.c_str()));
	}
	~Resource() 
	{ };

	std::string getFilename() {
		return m_filename;
	}

	T* get() {
		return m_data.get();
	}

	T& operator*() {
		return *m_data;
	}

	// Passes 
	T* operator->() {
		return m_data.get();
	}

private:
		std::unique_ptr<T> m_data;
		std::string m_filename;
};

class FontResource
{
public:
	FontResource(const std::string& filename, unsigned short height) : m_filename(filename), m_height(height) {
		m_data = std::unique_ptr<aie::Font>(new aie::Font(filename.c_str(), height));
	 }
	~FontResource() {};

	std::string getFilename() {
		return m_filename;
	}

	unsigned short getHeight() {
		return m_height;
	}

	aie::Font* get() {
		return m_data.get();
	}

	aie::Font& operator*() {
		return *m_data;
	}

	// Passes 
	aie::Font* operator->() {
		return m_data.get();
	}
private:
	std::unique_ptr<aie::Font> m_data;
	std::string m_filename;
	unsigned short m_height;
};

typedef std::shared_ptr<Resource<aie::Audio>> AudioPtr;
typedef std::shared_ptr<FontResource> FontPtr;
typedef std::shared_ptr<Resource<aie::Texture>> TexturePtr;

class ResourceManager
{
public:
	enum ResourceType {
		texture,
		audio,
		font
	};

	ResourceManager() {};
	~ResourceManager() {};
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	TexturePtr getTexture(const std::string& filename);

	AudioPtr getAudio(const std::string& filename); 

	FontPtr getFont(const std::string& filename, unsigned short size);//TODO set default font size

	size_t size(ResourceType type); 
		

	void collectGarbage();

private:
	las::Map<std::string, TexturePtr> m_textures;
	las::Map<std::string, AudioPtr> m_audio;
	las::Map<std::string, las::Map<unsigned short, FontPtr>> m_fonts;
};

