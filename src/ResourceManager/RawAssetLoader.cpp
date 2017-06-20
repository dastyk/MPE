#include "RawAssetLoader.h"
#include <fstream>

namespace MPE
{
	RawAssetLoader::RawAssetLoader(const char * assetFile) 
	{
		std::ifstream assetF(assetFile, std::ios::in);
		if (assetF.is_open())
		{
			char buff[256];
			while (assetF.getline(buff, 256))
			{
				_assets.insert({ GUID(buff), buff });
			}
			assetF.close();
		}
		else
		{
			printf("***Assetfile %s failed to load***\n\n", assetFile);
		}
		
	}

	RawAssetLoader::~RawAssetLoader()
	{
	}
	const bool RawAssetLoader::IsResourceInRegister(const GUID& guid)
	{
		auto&& find = _assets.find(guid);
		if (find == _assets.end())
			return false;
		return true;
	}
	const void RawAssetLoader::AddResourceToRegister(Resource * resource)
	{
		return void();
	}
	const bool RawAssetLoader::LoadResource(Resource* r)
	{
		const auto& assetFileName = _assets[r->guid];
			
		std::ifstream file(assetFileName, std::ios::in | std::ios::binary);
		if (!file.is_open())
		{
			r->state = Resource::READ_FAILED;
			return false;
		}

		std::string fileend;
		for (int i = assetFileName.size() - 1; i > 0; i--)
		{
			if (assetFileName[i] != '.')
				fileend.insert(0, 1, assetFileName[i]);
			else
				i = 0;
		}
		r->ext = FileExt(fileend);


		std::streampos filesize = file.tellg();
		file.seekg(0, std::ios::end);
		filesize = file.tellg() - filesize;
		file.seekg(0, std::ios::beg);
		r->size = filesize;

		r->data = operator new(r->size);
		file.read((char*)r->data, filesize);
		r->state = Resource::IN_MEMORY;
		return true;
	}
}