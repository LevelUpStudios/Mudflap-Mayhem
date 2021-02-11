#pragma once
#ifndef _VIHICLE_
#define _VIHICLE_
#include "DisplayObject.h"
#include "TextureManager.h"

class Vihicle :public DisplayObject
{
public:
	Vihicle();
	~Vihicle();

	void draw() override;
	void update() override;
	void clean() override;

private:
};
#endif // !_VIHICLE_
