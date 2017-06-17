#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#pragma once
#include <string>
#include <stack>
#include "GUID.h"
namespace MPE
{
	struct FileExt
	{
		FileExt(const uint16_t hash) : hash(hash){}
		FileExt(const std::string& ext)
		{
			hash = std::hash<std::string>{} (ext);
		}
		FileExt(const std::string&& ext)
		{
			hash = std::hash<std::string>{} (ext);
		}
		FileExt(const FileExt&& other) { hash = other.hash; }
		FileExt(const FileExt& other) { hash = other.hash; }
		void operator=(const FileExt&& rhs)
		{
			this->hash = rhs.hash;
		}
		void operator=(const FileExt& rhs)
		{
			this->hash = rhs.hash;
		}
		bool operator==(const FileExt& rhs) const
		{
			return rhs.hash == this->hash;
		}
		uint16_t hash;
	};

	struct Resource
	{
		struct Response
		{
			uint32_t dest;
			uint64_t tag;
			uint8_t prio;
		};
		enum : uint8_t
		{
			UNDEFINED,
			IN_MEMORY,
			CURRENTLY_READING,
			NOT_IN_MEMORY,
			ASSET_NOT_FOUND,
			READ_FAILED
			
		};
		Resource(const GUID& guid, uint8_t state = CURRENTLY_READING) : data(nullptr), size(0), ext(0), state(state), guid(guid), usageCount(0){}
		~Resource()
		{
			//operator delete(data);
		}
		void* data;
		size_t size;
		FileExt ext;
		uint8_t state;
		uint32_t usageCount;
		GUID guid;
		std::stack<Response> toNotify;

		
	};

}

#endif