#include "ResourceManager.h"

 void ResourceManager::Register(string name , Resource* resource)
	{
		Resources[name] = resource;
	}

 Resource* ResourceManager::Get(string name)
	{
		return Resources[name] ;
	}
 
 void ResourceManager::Delete(string name)
	{
		Resources.erase(name) ;
	}
	