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
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 0, 0, 0, 0);
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
			m_pVihicle->setAnimationState(TRUCK_DRIVE_DOWN);
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
		{
			m_pVihicle->setAnimationState(TRUCK_DRIVE_UP);
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

	//Force into the Win scene.
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(WIN_SCENE);
	}

	//Health system
	for (unsigned i=0;i<m_pTarget.size();i++)
	{
		int health = 3;
		if (CollisionManager::AABBCheck(m_pVihicle, m_pTarget[i])||health>0)
		{
			delete m_pTarget[i];
			m_pTarget[i] = nullptr;
			m_pTarget.erase(m_pTarget.begin() + i);
			m_pTarget.shrink_to_fit();
			health--;
			break;
			//Later add in animations for both the health bar and the truck when hit.
		}
		if (health <= 0)
		{
			delete m_pTarget[i];
			m_pTarget[i] = nullptr;
			m_pTarget.erase(m_pTarget.begin() + i);
			m_pTarget.shrink_to_fit();
			removeChild(m_pVihicle);
			
			Game::Instance()->changeSceneState(LOSE_SCENE);
		}
	}
	
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";
	
	m_pVihicle = new Vihicle();
	m_pVihicle->getTransform()->position = glm::vec2(50.0f, 100.0f);
	m_pVihicle->setEnabled(true);
	addChild(m_pVihicle);
	
	bool spawn = true;
	float x= 1+(rand()%800);
	float y = 1 + (rand() % 600);
	//using the target object as a placeholder for enemies 
	//Change to enemies later.
	if (SDL_GetTicks() % 60 * 5 == 0)
	{
		spawn = true;
		for (unsigned i = 0; i < m_pTarget.size(); i++)
		{
			m_pTarget.push_back(new Target());
			m_pTarget[i]->getTransform()->position = glm::vec2(x,y);
			m_pTarget.shrink_to_fit();
			addChild(m_pTarget[i]);
		}
	}
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
