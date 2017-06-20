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

		//! Checks to see if the resource can be loaded by this asset loader.
		virtual const bool IsResourceInRegister(const GUID& guid) = 0;

		//! Adds the resource to this asset loaders.
		virtual const void AddResourceToRegister(Resource* resource) = 0;

		//! Loads the specified resource.
		virtual const bool LoadResource(Resource* resource) = 0;
	};
}
#endif