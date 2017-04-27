#ifndef _RENDERER_DIRECTX11_H_
#define _RENDERER_DIRECTX11_H_

#pragma once
#include <Renderer\Renderer.h>
#include "Direct3D11.h"

namespace MPE
{
	class Renderer_DirectX11 : public Renderer
	{
	public:
		Renderer_DirectX11(threadIdentifier identifier, uint8_t frameSyncTime = 16);
		~Renderer_DirectX11();


		const void Start();

	private:
		Direct3D11 _d3d;
	};
}
#endif