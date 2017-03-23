//#pragma once
#include <d3d11.h>
class DXManager
{
public:
	static DXManager* get_insatance();

	HRESULT initialize(int width, int height, DXGI_FORMAT format);
	
	
	bool init_scene();
	void updeate_scene();
	void draw_scene();

private:
	HRESULT			create_swap_chain(int width, int height, DXGI_FORMAT format);
	HRESULT			create_render_target_view();

	DXManager();
	~DXManager();
	DXManager(const DXManager& instance) {};
	
	IDXGISwapChain*			_swap_chain;
	ID3D11Device *			_d3d_device;
	ID3D11DeviceContext*	_device_context;

	ID3D11RenderTargetView* _render_target_view;
	
	
	float _red, _green, _blue;
	int _colormodr, _colormodg, _colormodb;
};

