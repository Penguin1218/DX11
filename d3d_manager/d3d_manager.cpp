#pragma once
#include "d3d_manager.h"
#include <d3dcompiler.h>
#include "common_macros.h"

d3d_manager::d3d_manager()
	: _swap_chain(NULL)
	, _d3d_device(NULL)
	, _device_context(NULL)
	, _render_target_view(NULL)
	, _vertex_shader_buffer(NULL)
	, _pixel_shader_buffer(NULL)
	, _vertex_shader(NULL)
	, _pixel_shader(NULL)
	, _vertex_buffer(NULL)
	, _vertex_layout(NULL)
	, _red(0)
	, _green(0)
	, _blue(0)
	, _colormodr(1)
	, _colormodg(1)
	, _colormodb(1)
	, _width(0)
	, _height(0)
{
}


d3d_manager::~d3d_manager()
{
	release();
}


d3d_manager * d3d_manager::get_insatance()
{
	static d3d_manager _instance;
	return &_instance;
}

HRESULT d3d_manager::initialize(int width, int height, DXGI_FORMAT format, HWND hwnd)
{
	HRESULT hr = S_OK;
	_width = width;
	_height = height;
	hr = create_swap_chain(width, height, format, hwnd);
	RETURN_ON_FAIL(hr);
	hr = create_render_target_view();
	RETURN_ON_FAIL(hr);

	return hr;
}

void d3d_manager::release()
{
	_swap_chain->Release();
	_d3d_device->Release();
	_device_context->Release();

	_render_target_view->Release();

	_vertex_shader_buffer->Release();
	_pixel_shader_buffer->Release();
	_vertex_shader->Release();
	_pixel_shader->Release();

	_vertex_buffer->Release();
	_vertex_layout->Release();
}

HRESULT d3d_manager::create_swap_chain(int width, int height, DXGI_FORMAT format, HWND hwnd)
{
	HRESULT hr = S_OK;

	//Describe the buffer
	DXGI_MODE_DESC buffer_desc;
	ZeroMemory(&buffer_desc, sizeof(DXGI_MODE_DESC));
	buffer_desc.Width = width;
	buffer_desc.Height = height;
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
HRESULT d3d_manager::create_render_target_view()
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
	return hr;
}
//
//HRESULT d3d_manager::init_scene()
//{
//	
//	return S_OK;
//}
//void d3d_manager::updeate_scene()
//{
//	_red += _colormodr * 0.00005f;
//	_green += _colormodg * 0.00002f;
//	_blue += _colormodb * 0.00001f;
//
//	if (_red >= 1.0f || _red <= 0.0f)
//		_colormodr *= -1;
//	if (_green >= 1.0f || _green <= 0.0f)
//		_colormodg *= -1;
//	if (_blue >= 1.0f || _blue <= 0.0f)
//		_colormodb *= -1;
//}
//
//void d3d_manager::draw_scene()
//{
//	//Render our scene. Should avoid doing any updating
//	//d3dDevice : For other things have to do with the GPU, other than rendering.
//	//deviceContext : Rendering
//
//	float bgColor[4] = { _red, _green, _blue, 1.0f };
//	//float bgColor[4] = { 0.5, 0.0, 0.5, 0.0f };
//	_device_context->ClearRenderTargetView(_render_target_view, bgColor);
//
//	_device_context->Draw(6, 0);
//
//	//Present the backbuffer to the screen
//	_swap_chain->Present(0, 0);
//}

void d3d_manager::clear_render_target()
{
	float bgColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	_device_context->ClearRenderTargetView(_render_target_view, bgColor);
}

void d3d_manager::draw(UINT count, UINT start_index)
{
	_device_context->Draw(count, start_index);
}

void d3d_manager::present()
{
	_swap_chain->Present(0, 0);
}

HRESULT d3d_manager::create_shader(const scene_manager::SHADER_TYPE shader_type, LPCTSTR file_name, LPCSTR function_name)
{
	HRESULT hr = S_OK;
	switch (shader_type)
	{
	case scene_manager::VERTEX_SHADER:
		{
			hr = D3DCompileFromFile(file_name, 0, 0, function_name, "vs_5_0", 0, 0, &_vertex_shader_buffer, 0);
			RETURN_ON_FAIL(hr);
			
			hr = _d3d_device->CreateVertexShader(_vertex_shader_buffer->GetBufferPointer(), _vertex_shader_buffer->GetBufferSize(), NULL, &_vertex_shader);
			RETURN_ON_FAIL(hr);

			_device_context->VSSetShader(_vertex_shader, 0, 0);
		}
		break;
	case scene_manager::PIXEL_SHADER:
		{
			hr = D3DCompileFromFile(file_name, 0, 0, function_name, "ps_5_0", 0, 0, &_pixel_shader_buffer, 0);
			RETURN_ON_FAIL(hr);

			hr = _d3d_device->CreatePixelShader(_pixel_shader_buffer->GetBufferPointer(), _pixel_shader_buffer->GetBufferSize(), NULL, &_pixel_shader);
			RETURN_ON_FAIL(hr);

			_device_context->PSSetShader(_pixel_shader, 0, 0);
		}
		break;
	}
}
HRESULT d3d_manager::create_vertex_buffer(const void * vertices, const int& size_vertex, const int& num_vertices)
{
	//Create Vertex Buffer
	D3D11_BUFFER_DESC buffer_desc;
	ZeroMemory(&buffer_desc, sizeof(buffer_desc));
	buffer_desc.ByteWidth = size_vertex * num_vertices;
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertex_buffer_data;
	ZeroMemory(&vertex_buffer_data, sizeof(vertex_buffer_data));
	vertex_buffer_data.pSysMem = vertices;
	
	HRESULT hr = _d3d_device->CreateBuffer(&buffer_desc, &vertex_buffer_data, &_vertex_buffer);
	RETURN_ON_FAIL(hr);

	//Bind Vertex buffer to the IA
	UINT stride = size_vertex;
	UINT offset = 0;
	_device_context->IASetVertexBuffers(0, 1, &_vertex_buffer, &stride, &offset);

	return hr;
}
HRESULT d3d_manager::create_input_layout(const D3D11_INPUT_ELEMENT_DESC* layout, const int& num_elements)
{
	//Create input layout
	HRESULT hr = S_OK;
	hr = _d3d_device->CreateInputLayout(layout, num_elements, _vertex_shader_buffer->GetBufferPointer(), _vertex_shader_buffer->GetBufferSize(), &_vertex_layout);

	//Bind input layout to the IA
	_device_context->IASetInputLayout(_vertex_layout);
	return hr;
}

void d3d_manager::set_primitive_topology(D3D11_PRIMITIVE_TOPOLOGY topology)
{
	_device_context->IASetPrimitiveTopology(topology);
}

void d3d_manager::create_view_port(const float& top_left_x, const float& top_left_y, const float& width, const float& height, D3D11_VIEWPORT * viewport)
{
	if (viewport == NULL)
		return;
	ZeroMemory(viewport, sizeof(D3D11_VIEWPORT));
	viewport->TopLeftX = top_left_x;
	viewport->TopLeftY = top_left_y;
	viewport->Width = (width != 0) ? width : _width;
	viewport->Height = (height != 0) ? height : _height;
}

void d3d_manager::set_view_port(const D3D11_VIEWPORT* viewport, const int size)
{
	if(viewport)
		_device_context->RSSetViewports(size, viewport);
	else
	{
		D3D11_VIEWPORT default_viewport;
		default_viewport.TopLeftX = 0;
		default_viewport.TopLeftY = 0;
		default_viewport.Width = _width;
		default_viewport.Height = _height;
		_device_context->RSSetViewports(1, &default_viewport);
	}
}
