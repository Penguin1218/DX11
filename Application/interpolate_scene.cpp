#pragma once
#include "common_macros.h"
#include "interpolate_scene.h"


interpolate_scene::interpolate_scene()
{
}


interpolate_scene::~interpolate_scene()
{
}

HRESULT interpolate_scene::init_scene()
{
	HRESULT hr = S_OK;
	hr = create_shader(VERTEX_SHADER, L"C:\\000\\dev\\2017\\git\\DX11\\Application\\Effects_interpolation.fx", "VS");
	RETURN_ON_FAIL(hr);

	hr = create_shader(PIXEL_SHADER, L"C:\\000\\dev\\2017\\git\\DX11\\Application\\Effects_interpolation.fx", "PS");
	RETURN_ON_FAIL(hr);

	vertex_with_color v[] =
	{
		vertex_with_color(-0.5, -0.5, 0.5, 1.0, 0.0, 0.0, 1.0),
		vertex_with_color(0, 0.5, 0.5, 0.0, 1.0, 0.0, 1.0),
		vertex_with_color(0.5, -0.5, 0.5, 0.0, 0.0, 1.0, 1.0)
	};
	hr = create_vertex_buffer(v, sizeof(vertex_with_color), ARRAYSIZE(v));
	RETURN_ON_FAIL(hr);


	D3D11_INPUT_ELEMENT_DESC vertex_base_layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	hr = create_input_layout(vertex_base_layout, ARRAYSIZE(vertex_base_layout));
	RETURN_ON_FAIL(hr);

	set_primitive_topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_VIEWPORT viewport;
	create_view_port(0, 0, 0, 0, &viewport);
	set_view_port(&viewport, 1);

	return E_NOTIMPL;
}

void interpolate_scene::updeate_scene()
{
}

void interpolate_scene::draw_scene()
{
	clear_render_target();
	draw(3, 0);
	present();
}
