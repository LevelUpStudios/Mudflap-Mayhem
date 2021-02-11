#include "Vihicle.h"

Vihicle::Vihicle()
{
	TextureManager::Instance()->load("../Assets/textures/Truck.png", "Truck");

	auto size = TextureManager::Instance()->getTextureSize("Truck");
	setWidth(size.x);
	setHeight(size.y);
	setType(VIHICLE);
	getTransform()->position = glm::vec2(400.0f, 400.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
}

Vihicle::~Vihicle()
= default;

void Vihicle::draw()
{
	TextureManager::Instance()->draw("Truck",
		getTransform()->position.x, getTransform()->position.y, 0, 255, true);
}

void Vihicle::update()
{
}

void Vihicle::clean()
{
}
