#ifndef _MSG_H_
#define _MSG_H_
#pragma once

#define CreateTag(destination, tag) ( (uint64_t(destination) << 32) | uint64_t(tag) )

namespace MPE
{
	struct Destination
	{
		enum : uint32_t
		{
			ThreadMessageController = 0, /**< 0 is reserved for ThreadMessageController. */
			Any = UINT32_MAX,/**< Specify to allow messages from any source. */
			DataManager = 1 << 0,
			ScriptManager = 1 << 1,
			Renderer = 1 << 2,
			ResourceManager = 1 << 3
		};
		Destination() { destination = ThreadMessageController; }
		Destination(const Destination& other) { destination = other.destination; }
		Destination(const uint32_t& other) { destination = other; }
		const Destination& operator=(const uint32_t& oDest) { destination = oDest; }
		operator const uint32_t()const { return destination; }
	private:
		uint32_t destination;

	};

	struct Tag
	{
		//! The basic tags used during message passing.
		enum : uint64_t
		{
			Any = CreateTag(Destination::ThreadMessageController, 0),
			Shutdown = CreateTag(Destination::ThreadMessageController, 1),
			Start = CreateTag(Destination::ThreadMessageController, 2)
		};
		//! The tags used in the DataManager
		struct DataManager
		{
			enum : uint64_t
			{
				RegisterEntity = CreateTag(Destination::DataManager, 0),
			};
		};
		struct ResourceManager
		{
			enum : uint64_t
			{
				LoadResource = CreateTag(Destination::ResourceManager, 0),
				LoadResourceAndForward = CreateTag(Destination::ResourceManager, 1),
			};
		};
		struct Renderer
		{
			enum : uint64_t
			{
				RegisterScene = CreateTag(Destination::Renderer, 0),
				RegisterEntity = CreateTag(Destination::Renderer, 1),
				SetRenderScene = CreateTag(Destination::Renderer, 2)
			};
		};
		Tag() { tag = Any; }
		Tag(const Tag& other) { tag = other.tag; }
		Tag(const uint32_t& other) { tag = other; }
		const Tag& operator=(const uint32_t& oTag) { tag = oTag; }


		operator const uint32_t()const { return tag; }
	private:
		uint32_t tag;
	};

	struct Msg
	{
		void* data;
		Destination src; /**< Source*/
		Tag tag; /**< Tag, if Tag::Any was specified. */
		uint8_t prio;
	};
	struct MsgComp
	{
		bool operator()(const Msg& lhs, const Msg& rhs) const
		{
			return lhs.prio >= rhs.prio;
		}
	};
}
#endif