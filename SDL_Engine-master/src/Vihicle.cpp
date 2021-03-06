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
	if (m_currentAnimationState == TRUCK_DRIVE_LEFT)
	{
		getTransform()->position -= glm::vec2(5.0f, 0.0f);
	}
	if (m_currentAnimationState == TRUCK_DRIVE_RIGHT)
	{
		getTransform()->position += glm::vec2(5.0f, 0.0f);
	}
	if (m_currentAnimationState == TRUCK_DRIVE_UP)
	{
		getTransform()->position += glm::vec2(0.0f, 5.0f);
	}
	if (m_currentAnimationState == TRUCK_DRIVE_DOWN)
	{
		getTransform()->position += glm::vec2(0.0f, -5.0f);
	}
}

void Vihicle::clean()
{
}

void Vihicle::setAnimationState(const TruckAnimationState new_state)
{
	m_currentAnimationState = new_state;
}
