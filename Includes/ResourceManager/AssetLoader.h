#ifndef _ASSET_LOADER_H_
#define _ASSET_LOADER_H_
#pragma once
#include "GUID.h"
namespace MPE
{
	struct FileExt
	{
		FileExt(const char* ext)
		{
			data = std::hash<std::string>{} (ext);
		}
		FileExt(const std::string& ext)
		{
			data = std::hash<std::string>{} (ext);
		}
		FileExt(const std::string&& ext)
		{
			data = std::hash<std::string>{} (ext);
		}
		FileExt(const FileExt&& other) { data = other.data; }
		FileExt(const FileExt& other) { data = other.data; }
		void operator=(const FileExt&& rhs)
		{
			this->data = rhs.data;
		}
		void operator=(const FileExt& rhs)
		{
			this->data = rhs.data;
		}
		bool operator==(const FileExt& rhs) const
		{
			return rhs.data == this->data;
		}
		uint16_t data;
	};

	struct Resource
	{
		void* data;
		size_t size;
		FileExt ext;
	};

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