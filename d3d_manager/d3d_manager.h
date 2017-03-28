#pragma once
#include "scene_manager.h"
class d3d_manager
{
	friend scene_manager;
public:
	static d3d_manager* get_insatance();

	HRESULT initialize(int width, int height, DXGI_FORMAT format, HWND hwnd);
	void release();
	/*HRESULT init_scene();
	void updeate_scene();
	void draw_scene();*/

private:
	HRESULT			create_swap_chain(int width, int height, DXGI_FORMAT format, HWND hwnd);
	HRESULT			create_render_target_view();

	d3d_manager();
	~d3d_manager();
	d3d_manager(const d3d_manager& instance) {};
	

	
	float _red, _green, _blue;
	int _colormodr, _colormodg, _colormodb;

//Init Scene
	//Input Assember
	HRESULT create_shader(const scene_manager::SHADER_TYPE shader_type, LPCTSTR file_name, LPCSTR function_name);
	HRESULT create_vertex_buffer(const void * vertices, const int& size_vertex, const int& num_vertices);
	HRESULT	create_input_layout(const D3D11_INPUT_ELEMENT_DESC* layout, const int& num_elements);
	void	set_primitive_topology(D3D11_PRIMITIVE_TOPOLOGY topology);

	//Rasterize 
	void	create_view_port(const float& top_left_x, const float& top_left_y, const float& width, const float& height, D3D11_VIEWPORT* viewport);
	void	set_view_port(const D3D11_VIEWPORT* viewport, const int size);


//Draw Scene
	void clear_render_target();
	void draw(UINT count, UINT start_index);
	void present();

	//Interface
private:
	IDXGISwapChain*			_swap_chain;
	ID3D11Device *			_d3d_device;
	ID3D11DeviceContext*	_device_context;

	ID3DBlob*				_vertex_shader_buffer;
	ID3DBlob*				_pixel_shader_buffer;
	ID3D11VertexShader*		_vertex_shader;
	ID3D11PixelShader*		_pixel_shader;

	ID3D11Buffer*			_vertex_buffer;
	ID3D11RenderTargetView* _render_target_view;

	ID3D11InputLayout * _vertex_layout;

	int _width;
	int _height;
};

