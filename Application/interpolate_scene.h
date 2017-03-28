#pragma once
#include "scene_manager.h"
class interpolate_scene :
	public scene_manager
{
public:
	interpolate_scene();
	~interpolate_scene();

	virtual HRESULT init_scene();
	virtual void updeate_scene();
	virtual void draw_scene();
};

