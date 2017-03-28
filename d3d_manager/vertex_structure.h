#pragma once
#include "DirectXMath.h"

using namespace DirectX;
class vertex_base
{
public:
	vertex_base() {};
	vertex_base(float x, float y, float z)
		: pos(x, y, z) {};

	XMFLOAT3 pos;
};
class vertex_with_color : public vertex_base
{
public:
	vertex_with_color() {};
	vertex_with_color(float x, float y, float z, float r, float g, float b, float a)
		: vertex_base(x, y, z), color(r,g,b,a)
		 {};
	XMFLOAT4 color;
};