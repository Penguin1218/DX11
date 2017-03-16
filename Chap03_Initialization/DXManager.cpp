#pragma once
#include "DXManager.h"
DXManager::DXManager()
{
}


DXManager::~DXManager()
{
}

DXManager * DXManager::get_insatance()
{
	static DXManager _instance;
	return &_instance;
}

HRESULT DXManager::initialize()
{
	HRESULT hr = S_OK;
	return E_NOTIMPL;
}
HRESULT DXManager::create_swap_chain(int width, int height, DXGI_FORMAT format)
{
	//Describe the buffer
	DXGI_MODE_DESC buffer_desc;
	ZeroMemory(&buffer_desc, sizeof(DXGI_MODE_DESC));
	buffer_desc.Width = width;
	buffer_desc.Height = height;
	buffer_desc.RefreshRate.Numerator = 60;
	buffer_desc.RefreshRate.Denominator = 1;
	buffer_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	buffer_desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	buffer_desc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//Describe our swapchain
	DXGI_SWAP_CHAIN_DESC swap_chain_desc;
	ZeroMemory(&swap_chain_desc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swap_chain_desc.BufferDesc = buffer_desc;
	swap_chain_desc.SampleDesc.Count = 1;
	swap_chain_desc.SampleDesc.Quality = 0;
	swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_desc.BufferCount = 1;
	swap_chain_desc.OutputWindow = hwnd;
	swap_chain_desc.Windowed = TRUE;
	swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;


	return E_NOTIMPL;


}


