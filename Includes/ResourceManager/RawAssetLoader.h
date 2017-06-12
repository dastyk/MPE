#ifndef _RAW_ASSET_LOADER_H_
#define _RAW_ASSET_LOADER_H_
#pragma once

#include "GUID.h"
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

		const void LoadResource(GUID guid, Resource* r);
	private:
		std::map<GUID, std::string> _assets;
	};
}
#endif