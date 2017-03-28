#pragma once
#include "common_macros.h"
#include "primitive_scene_manager.h"

primitive_scene_manager::primitive_scene_manager()
{
}
primitive_scene_manager::~primitive_scene_manager()
{
}

HRESULT primitive_scene_manager::init_scene()
{
	HRESULT hr = S_OK;
	hr = create_shader(VERTEX_SHADER, L"C:\\000\\dev\\2017\\git\\DX11\\Chap4_BeginDrawing\\Effects.fx", "VS");
	RETURN_ON_FAIL(hr);

	hr = create_shader(PIXEL_SHADER, L"C:\\000\\dev\\2017\\git\\DX11\\Chap4_BeginDrawing\\Effects.fx", "PS");
	RETURN_ON_FAIL(hr);

	vertex_base v[] =
	{
		vertex_base(-0.5, -0.5, 0.5),
		vertex_base(0, 0.5, 0.5),
		vertex_base(0.5, -0.5, 0.5)
	};
	hr = create_vertex_buffer(v, sizeof(vertex_base), ARRAYSIZE(v));
	RETURN_ON_FAIL(hr);


	D3D11_INPUT_ELEMENT_DESC vertex_base_layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	hr = create_input_layout(vertex_base_layout, 1);
	RETURN_ON_FAIL(hr);

	set_primitive_topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	D3D11_VIEWPORT viewport;
	create_view_port(0, 0, 0, 0, &viewport);
	set_view_port(&viewport, 1);

	return E_NOTIMPL;
}

void primitive_scene_manager::updeate_scene()
{
}

void primitive_scene_manager::draw_scene()
{
	clear_render_target();
	draw(3, 0);
	present();
}
