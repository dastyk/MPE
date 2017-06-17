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
	const bool RawAssetLoader::LoadResource(Resource* r)
	{
		auto&& find = _assets.find(r->guid);
		if (find == _assets.end())
		{
			r->state = Resource::ASSET_NOT_FOUND;
			return false;
		}
			
		std::ifstream file(find->second, std::ios::in | std::ios::binary);
		if (!file.is_open())
		{
			r->state = Resource::READ_FAILED;
			return false;
		}

		std::string filename = find->second;
		std::string fileend;
		for (int i = filename.size() - 1; i > 0; i--)
		{
			if (filename[i] != '.')
				fileend.insert(0, 1, filename[i]);
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