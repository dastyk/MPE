#ifndef _ASSET_LOADER_H_
#define _ASSET_LOADER_H_
#pragma once
#include "GUID.h"
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

		virtual Resource LoadResource(GUID guid) = 0;
	};
}
#endif