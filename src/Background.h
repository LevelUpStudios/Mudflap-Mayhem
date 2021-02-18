#pragma once
#ifndef _BACKGROUND_
#define _BACKGROUND_
#include "DisplayObject.h"

class Background : public DisplayObject
{
public:
	Background();
	~Background();

	void draw() override;
	void update() override;
	void clean() override;
};

#endif // !1
