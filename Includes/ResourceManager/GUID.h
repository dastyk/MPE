#ifndef _GUID_H_
#define _GUID_H_
#pragma once
#include <string>
namespace MPE
{
	struct GUID
	{
		GUID(const char* name)
		{
			data = std::hash<std::string>{} (name);
		}
		GUID(const GUID&& other) { data = other.data; }
		void operator=(const GUID&& rhs)
		{
			this->data = rhs.data;
		}
		bool operator==(const GUID& rhs) const
		{
			return rhs.data == this->data;
		}
		bool operator<(const GUID& rhs)const
		{
			return this->data < rhs.data;
		}
		uint64_t data;
	};
}
#endif