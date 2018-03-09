#pragma once
#include<map>
#include <string>
#include "ResourceImage.h"

template <class T>
class ResourceManager
{
	struct ResourcePointers {
	public:
		std::shared_ptr<T> sPtr;
		std::weak_ptr<T> wPtr;
	};
public:
	//it has to be static, because it is impossible to create static templated map without instantiation, first Get call will do this job
	static ResourceManager& get()
	{
		static ResourceManager instance;
		return instance;
	}
	std::shared_ptr<T> loadResource(const std::string& path, bool persistent = false);
private:
	ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	//this can't be static due to custom type in map value
	std::map<std::string, ResourcePointers> resourceMap;
};

template<class T>
inline std::shared_ptr<T> ResourceManager<T>::loadResource(const std::string& path, bool persistent)
{
	auto it = resourceMap.find(path);
	std::shared_ptr<T> ptr = nullptr;
	if (it != resourceMap.end())
	{
		ptr = it->second.wPtr.lock();
	}
	
	if (ptr)
		return ptr;

	ptr = std::make_shared<T>(path);
	resourceMap[path] = ResourcePointers{persistent ? ptr : nullptr, ptr};
	return ptr;
}
