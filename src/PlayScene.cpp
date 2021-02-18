#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Target.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

	drawDisplayList();
}

void PlayScene::update()
{
	updateDisplayList();
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	//Movement with controller.
	if (SDL_NumJoysticks() > 0)
	{
		if (EventManager::Instance().getGameController(0) != nullptr)
		{
			const auto deadZone = 10000;
			if (EventManager::Instance().getGameController(0)->LEFT_STICK_X < -deadZone)
			{
				m_pVihicle->setAnimationState(TRUCK_DRIVE_LEFT);
			}
			else if (EventManager::Instance().getGameController(0)->LEFT_STICK_X > deadZone)
			{
				m_pVihicle->setAnimationState(TRUCK_DRIVE_RIGHT);
			}
			else if (EventManager::Instance().getGameController(0)->LEFT_STICK_Y > deadZone)
			{
				m_pVihicle->setAnimationState(TRUCK_DRIVE_UP);
			}
			else if (EventManager::Instance().getGameController(0)->LEFT_STICK_Y < -deadZone)
			{
				m_pVihicle->setAnimationState(TRUCK_DRIVE_DOWN);
			}
			else
			{
				m_pVihicle->setAnimationState(TRUCK_IDLE_RIGHT);
			}
		}

		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
		{
			TheGame::Instance()->quit();
		}
	}

	// handle player movement if no Game Controllers found
	if (SDL_NumJoysticks() < 1)
	{
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		{
			m_pVihicle->setAnimationState(TRUCK_DRIVE_LEFT);
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			m_pVihicle->setAnimationState(TRUCK_DRIVE_RIGHT);
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
		{
			m_pVihicle->setAnimationState(TRUCK_DRIVE_DOWN); // fix later
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
		{
			m_pVihicle->setAnimationState(TRUCK_DRIVE_UP); // fix later
		}
		else
		{
			m_pVihicle->setAnimationState(TRUCK_IDLE_RIGHT);
		}
	}

	for (int i = 0; i < 3; i++) // for health system down the line.
	{
		if (CollisionManager::AABBCheck(m_pVihicle, m_pTarget))
			TheGame::Instance()->changeSceneState(LOSE_SCENE);
	}

	//forcing the win scene
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
		TheGame::Instance()->changeSceneState(WIN_SCENE);
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";
	// Background test 1
	m_pBackground = new Background();
	m_pBackground->getTransform()->position = glm::vec2(0.0f, 0.0f);
	addChild(m_pBackground);
	
	m_pVihicle = new Vihicle();
	m_pVihicle->getTransform()->position = glm::vec2(50.0f, 100.0f);
	m_pVihicle->setEnabled(true);
	addChild(m_pVihicle);

	m_pTarget = new Target();
	m_pTarget->getTransform()->position = glm::vec2(500.0f, 300.0f);
	addChild(m_pTarget);
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if(ImGui::Button("My Button"))
	{
		std::cout << "My Button Pressed" << std::endl;
	}

	ImGui::Separator();

	static float float3[3] = { 0.0f, 1.0f, 1.5f };
	if(ImGui::SliderFloat3("My Slider", float3, 0.0f, 2.0f))
	{
		std::cout << float3[0] << std::endl;
		std::cout << float3[1] << std::endl;
		std::cout << float3[2] << std::endl;
		std::cout << "---------------------------\n";
	}
	
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
