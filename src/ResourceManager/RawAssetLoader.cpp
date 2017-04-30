#include "RawAssetLoader.h"
#include <fstream>

namespace MPE
{
	RawAssetLoader::RawAssetLoader(const char * assetFile) 
	{
		std::ifstream assetF(assetFile, std::ios::in);
		if (!assetF.is_open())
			throw std::runtime_error((std::string("Could not open asset file: ") + assetFile).c_str());

		char buff[256];
		while (assetF.getline(buff, 256))
		{
			_assets.insert({ GUID(buff), buff });
		}
		assetF.close();
	}

	RawAssetLoader::~RawAssetLoader()
	{
	}
	Resource RawAssetLoader::LoadResource(GUID guid)
	{
		auto&& find = _assets.find(guid);
		if (find == _assets.end())
		{
			throw std::runtime_error("Asset not found, GUID: " + std::to_string(guid.data));
		}
		std::ifstream file(find->second, std::ios::in | std::ios::binary);
		if(!file.is_open())
			throw std::runtime_error("Asset not found, GUID: " + std::to_string(guid.data));

		std::string filename = find->second;
		std::string fileend;
		for (int i = filename.size() - 1; i > 0; i--)
		{
			if (filename[i] != '.')
				fileend.insert(0, 1, filename[i]);
			else
				i = 0;
		}
		FileExt ext(fileend);


		std::streampos filesize = file.tellg();
		file.seekg(0, std::ios::end);
		filesize = file.tellg() - filesize;
		file.seekg(0, std::ios::beg);
		size_t size = filesize;

		void* data = operator new(size);
		file.read((char*)data, filesize);


		return { data, size, ext };
	}
}