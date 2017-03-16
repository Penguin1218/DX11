//#pragma once
#include <d3d11.h>
class DXManager
{
public:
	DXManager* get_insatance();

	HRESULT initialize();
	HRESULT create_swap_chain(int width, int height, DXGI_FORMAT format);
private:
	DXManager();
	~DXManager();
	DXManager(const DXManager& instance) {};
	
};

