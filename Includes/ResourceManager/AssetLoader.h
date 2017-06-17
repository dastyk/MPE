#ifndef _ASSET_LOADER_H_
#define _ASSET_LOADER_H_
#pragma once
#include "Resource.h"
namespace MPE
{


	//! An abstract class for loading files, can be from disk, from zip, from network, etc.
	class AssetLoader
	{
	protected:
		AssetLoader() {};


	public:
		~AssetLoader() {}

		virtual const bool LoadResource(Resource* resource) = 0;
	};
}
#endif