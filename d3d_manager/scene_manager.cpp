#pragma once
#include "scene_manager.h"

#include <process.h>
#include "d3d_manager.h"
#include "common_macros.h"

scene_manager::scene_manager()
	: _run(false)
	, _d3d_thread(INVALID_HANDLE_VALUE)
	, _hwnd(NULL)
	, _d3d_manager(NULL)
{
}


scene_manager::~scene_manager()
{
	release();
}

HRESULT scene_manager::initialize(int width, int height, DXGI_FORMAT format, HWND hwnd)
{
	_d3d_manager = d3d_manager::get_insatance();

	HRESULT hr = S_OK;
	hr = _d3d_manager->initialize(width, height, format, hwnd);
	RETURN_ON_FAIL(hr);

	unsigned int thrdaddr = 0;
	_d3d_thread = (HANDLE)::_beginthreadex(NULL, 0, process_callback, this, 0, &thrdaddr);
	if (_d3d_thread == INVALID_HANDLE_VALUE)
		return E_FAIL;
}

void scene_manager::release()
{
	_run = false;
	::WaitForSingleObject(_d3d_thread, INFINITE);
	::CloseHandle(_d3d_thread);
	_d3d_thread = INVALID_HANDLE_VALUE;
}

unsigned scene_manager::process_callback(void * param)
{
	scene_manager * self = static_cast<scene_manager*>(param);
	self->process();
	return 0;
}

void scene_manager::process(void)
{
	_run = true;
	init_scene();
	while (_run)
	{
		updeate_scene();
		draw_scene();
	}
}

HRESULT scene_manager::create_shader(const SHADER_TYPE shader_type, LPCTSTR file_name, LPCSTR function_name)
{
	return _d3d_manager->create_shader(shader_type, file_name, function_name);
}

HRESULT scene_manager::create_vertex_buffer(const void * vertices, const int& size_vertex, const int& num_vertices)
{
	return _d3d_manager->create_vertex_buffer(vertices, size_vertex, num_vertices);
}

HRESULT scene_manager::create_input_layout(const D3D11_INPUT_ELEMENT_DESC * layout, const int& num_elements)
{
	return _d3d_manager->create_input_layout(layout, num_elements);
}

void scene_manager::set_primitive_topology(D3D11_PRIMITIVE_TOPOLOGY  topology)
{
	_d3d_manager->set_primitive_topology(topology);
}

void scene_manager::create_view_port(const float & top_left_x, const float & top_left_y, const float & width, const float & height, D3D11_VIEWPORT * viewport)
{
	_d3d_manager->create_view_port(top_left_x, top_left_y, width, height, viewport);
}

void scene_manager::set_view_port(const D3D11_VIEWPORT * viewport, const int size)
{
	_d3d_manager->set_view_port(viewport, size);
}

void scene_manager::clear_render_target()
{
	_d3d_manager->clear_render_target();
}

void scene_manager::draw(UINT count, UINT start_index)
{
	_d3d_manager->draw(count, start_index);
}

void scene_manager::present()
{
	_d3d_manager->present();
}
