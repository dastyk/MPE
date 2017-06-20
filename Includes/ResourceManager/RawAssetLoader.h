#ifndef _RAW_ASSET_LOADER_H_
#define _RAW_ASSET_LOADER_H_
#pragma once

#include <map>
#include "AssetLoader.h"
namespace MPE
{
	//! Asset loader for loading files directly by their names. Files that can be loaded still needs to be converted to a GUID.
	class RawAssetLoader : public AssetLoader
	{
	public:
		RawAssetLoader(const char* assetFile);
		~RawAssetLoader();

		const bool IsResourceInRegister(const GUID& guid);
		const void AddResourceToRegister(Resource* resource);
		const bool LoadResource(Resource* r);
	private:
		std::map<GUID, std::string> _assets;
	};
}
#endif