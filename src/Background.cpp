#include "Background.h"
#include "TextureManager.h"

Background::Background()
{
	TextureManager::Instance()->load("../Assets/textures/mud_background.png", "Background");
	auto size = TextureManager::Instance()->getTextureSize("Background");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(800.0f, 600.0f);
	setType(BACKGROUND);
}

Background::~Background()
= default;

void Background::draw()
{
	TextureManager::Instance()->draw("Background", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
}

void Background::update()
{
}

void Background::clean()
{
}
