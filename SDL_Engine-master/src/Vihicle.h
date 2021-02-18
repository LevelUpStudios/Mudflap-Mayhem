#pragma once
#ifndef _VIHICLE_
#define _VIHICLE_
#include "DisplayObject.h"
#include "TextureManager.h"
#include "TruckAnimationState.h"

class Vihicle :public DisplayObject
{
public:
	Vihicle();
	~Vihicle();

	void draw() override;
	void update() override;
	void clean() override;

	void setAnimationState(const TruckAnimationState new_state);

private:
	TruckAnimationState m_currentAnimationState;

};
#endif // !_VIHICLE_
