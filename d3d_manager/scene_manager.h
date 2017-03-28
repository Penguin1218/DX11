#pragma once
#include <d3d11.h>
#include "vertex_structure.h"
class d3d_manager;
class scene_manager
{
public:
	enum SHADER_TYPE
	{
		VERTEX_SHADER,
		PIXEL_SHADER
	};
	scene_manager();
	virtual ~scene_manager();

	virtual HRESULT initialize(int width, int height, DXGI_FORMAT format, HWND hwnd);
	virtual void release();

	//Place our objects, load our models, textures, sounds, all that must be done to start off that specific scene.
	virtual HRESULT init_scene() = 0;
	//Change objects locations, values, anything that changes in our scenes will be done here.
	virtual void updeate_scene() = 0;
	//1.render to the back buffer
	//2.back buffer is presented when Present method(Swap fb with bb) is called.
	virtual void draw_scene() = 0;

private:
	d3d_manager * _d3d_manager;
	HWND _hwnd;
	//Rendering thread
	static unsigned __stdcall process_callback(void * param);
	void process(void);
	HANDLE	_d3d_thread;
	bool	_run;

protected:
	//Input Assember
	HRESULT create_shader(const SHADER_TYPE shader_type, LPCTSTR file_name, LPCSTR function_name);
	HRESULT create_vertex_buffer(const void * vertices, const int& size_vertex, const int& num_vertices);
	HRESULT	create_input_layout(const D3D11_INPUT_ELEMENT_DESC* layout, const int& num_elements);
	void	set_primitive_topology(D3D11_PRIMITIVE_TOPOLOGY topology);

	//Rasterize 
	void	create_view_port(const float& top_left_x, const float& top_left_y, const float& width, const float& height, D3D11_VIEWPORT* viewport);
	void	set_view_port(const D3D11_VIEWPORT* viewport, const int size);


	//draw
protected:
	void clear_render_target();
	void draw(UINT count, UINT start_index);
	void present();
};

