#pragma once
#include "DXManager.h"
#define RETURN_ON_FAIL(hr) if(FAILED(hr)){return hr;}
DXManager::DXManager()
	: _swap_chain(NULL)
	, _d3d_device(NULL)
	, _device_context(NULL)
	, _render_target_view(NULL)
	, _red(0)
	, _green(0)
	, _blue(0)
	, _colormodr(1)
	, _colormodg(1)
	, _colormodb(1)
{
}


DXManager::~DXManager()
{
	_swap_chain->Release();
	_d3d_device->Release();
	_device_context->Release();
	_render_target_view->Release();
}

DXManager * DXManager::get_insatance()
{
	static DXManager _instance;
	return &_instance;
}

HRESULT DXManager::initialize(int width, int height, DXGI_FORMAT format, HWND hwnd)
{
	HRESULT hr = S_OK;
	hr = create_swap_chain(width, height, format, hwnd);
	RETURN_ON_FAIL(hr);
	hr = create_render_target_view();
	RETURN_ON_FAIL(hr);

	return hr;
}

HRESULT DXManager::create_swap_chain(int width, int height, DXGI_FORMAT format, HWND hwnd)
{
	HRESULT hr = S_OK;

	//Describe the buffer
	DXGI_MODE_DESC buffer_desc;
	ZeroMemory(&buffer_desc, sizeof(DXGI_MODE_DESC));
	buffer_desc.Width = 100;
	buffer_desc.Height = 100;
	buffer_desc.RefreshRate.Numerator = 60;
	buffer_desc.RefreshRate.Denominator = 1;
	buffer_desc.Format = format;
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

	//Create Direct3D Device, Device context, Swap chain.
	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
		D3D11_SDK_VERSION, &swap_chain_desc, &_swap_chain, &_d3d_device, NULL, &_device_context);

	
	return hr;
}
HRESULT DXManager::create_render_target_view()
{
	HRESULT hr = S_OK;
	// Create the Backbuffer
	ID3D11Texture2D* back_buffer;
	hr = _swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&back_buffer);
	RETURN_ON_FAIL(hr);

	// Create the Render Target
	hr = _d3d_device->CreateRenderTargetView(back_buffer, NULL, &_render_target_view);
	back_buffer->Release();
	RETURN_ON_FAIL(hr);

	// Set the Render Target
	_device_context->OMSetRenderTargets(1, &_render_target_view, NULL);
	RETURN_ON_FAIL(hr);
}

bool DXManager::init_scene()
{
	//Place our objects, load our models, textures, sounds, all that must be done to start off that specific scene.
	return true;
}
void DXManager::updeate_scene()
{
	//Change objects locations, values, anything that changes in our scenes will be done here.
	_red += _colormodr * 0.00005f;
	_green += _colormodg * 0.00002f;
	_blue += _colormodb * 0.00001f;

	if (_red >= 1.0f || _red <= 0.0f)
		_colormodr *= -1;
	if (_green >= 1.0f || _green <= 0.0f)
		_colormodg *= -1;
	if (_blue >= 1.0f || _blue <= 0.0f)
		_colormodb *= -1;
}

//1.render to the back buffer
//2.back buffer is presented when Present method(Swap fb with bb) is called.
void DXManager::draw_scene()
{
	//Render our scene. Should avoid doing any updating
	//d3dDevice : For other things have to do with the GPU, other than rendering.
	//deviceContext : Rendering

	float bgColor[4] = { _red, _green, _blue, 1.0f };
	//float bgColor[4] = { 0.5, 0.0, 0.5, 0.0f };
	_device_context->ClearRenderTargetView(_render_target_view, bgColor);

	//Present the backbuffer to the screen
	_swap_chain->Present(0, 0);

	
}