#pragma once
#include "scene_manager.h"
class primitive_scene_manager :
	public scene_manager
{
public:
	primitive_scene_manager();
	~primitive_scene_manager();

	virtual HRESULT init_scene();
	virtual void updeate_scene();
	virtual void draw_scene();
};

