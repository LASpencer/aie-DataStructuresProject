#pragma once
#include "stdafx.h"
#include "Map.h"
#include "Array.h"

//TODO comment, document and test resource manager

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

template<class T>
class ResourceManager
{
public:
	typedef std::shared_ptr<Resource<T>> ResourcePtr;

	ResourceManager() {};
	~ResourceManager() {};
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	ResourcePtr get(const std::string& filename) {
		if (!m_resources.exists(filename)) {
			m_resources.insert(filename, std::make_shared<Resource<T>>(filename));
		}
		return m_resources.at(filename);
	}

	size_t size() {
		return m_resources.size();
	}

	void collectGarbage() {
		las::Array<std::pair<std::string, ResourcePtr>> resources = m_resources.flattenMap();
		for (las::Array<std::pair<std::string, ResourcePtr>>::iterator it = resources.begin(); it != resources.end();++it) {
			if (it->second.use_count() == 2) {		//2 as pointer is in both m_resources and resources array
				m_resources.erase(it->first);
			}
		}
	};

private:
	las::Map<std::string, ResourcePtr> m_resources;
};