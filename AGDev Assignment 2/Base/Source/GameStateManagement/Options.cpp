#include <iostream>
using namespace std;

#include "Options.h"
#include "GL\glew.h"
#include "../Application.h"
#include "LoadTGA.h"
#include "GraphicsManager.h"
#include "MeshBuilder.h"
#include "../TextEntity.h"
#include "RenderHelper.h"
#include "../SpriteEntity.h"
#include "../EntityManager.h"

#include "KeyboardController.h"
#include "SceneManager.h"
#include "../Lua/LuaInterface.h"


Options::Options()
{

}
Options::~Options()
{

}

void Options::Init()
{
	//CLuaInterface::GetInstance()->Init("LuaScript/DM2240.lua");
	// Create and attach the camera to the scene
	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
	GraphicsManager::GetInstance()->AttachCamera(&camera);

	// Load all the meshes
	MeshBuilder::GetInstance()->GenerateQuad("options_bg", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("options_bg")->textureID = LoadTGA("Image//IntroState.tga");
	halfWindowWidth = Application::GetInstance().GetWindowWidth() / 2.0f;
	halfWindowHeight = Application::GetInstance().GetWindowHeight() / 2.0f;
	Options_BG = Create::Sprite2DObject("options_bg", Vector3(halfWindowWidth, halfWindowHeight, 0.0f), Vector3(Application::GetInstance().GetWindowWidth(), Application::GetInstance().GetWindowHeight(), 0.0f));

	//SceneManager::GetInstance()->SetActiveCascadingScene("AudioSettings");
	
	for (int i = 0; i < 3; i++)
	{
		Buttons[i] = Create::Sprite2DObject("Button", Vector3(halfWindowWidth, halfWindowHeight * 1.5f - (halfWindowHeight * 0.5 * i), 1.f), Vector3(600.f, 100.f, 1.f));
		textObj[i] = Create::Text2DObject("Text", Vector3(halfWindowWidth * 0.9f, halfWindowHeight * 1.5f - (halfWindowHeight * 0.5 * i), 2.f), "text", Vector3(30.f, 70.f, 1.f), (1.f, 1.f, 1.f));
	}

	textObj[0]->SetText("Audio");
	textObj[1]->SetText("Controls");
	textObj[2]->SetText("Exit");

	MenuOption = 0;
}
void Options::Update(double dt)
{
	if (KeyboardController::GetInstance()->IsKeyReleased(VK_SPACE))
	{
		cout << "Loading MenuState" << endl;
		SceneManager::GetInstance()->SetActiveScene("MenuState");
	}
	if (KeyboardController::GetInstance()->IsKeyReleased('W'))
		if(MenuOption > 0)
			MenuOption--;
	if (KeyboardController::GetInstance()->IsKeyReleased('S'))
		if (MenuOption < 2)
			MenuOption++;
}
void Options::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	//GraphicsManager::GetInstance()->UpdateLightUniforms();

	// Setup 3D pipeline then render 3D
	GraphicsManager::GetInstance()->SetPerspectiveProjection(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	GraphicsManager::GetInstance()->AttachCamera(&camera);

	// Render the required entities
	EntityManager::GetInstance()->Render();

	// Setup 2D pipeline then render 2D
	GraphicsManager::GetInstance()->SetOrthographicProjection(0, Application::GetInstance().GetWindowWidth(), 0, Application::GetInstance().GetWindowHeight(), -10, 10);
	GraphicsManager::GetInstance()->DetachCamera();

	// Render the required entities
	EntityManager::GetInstance()->RenderUI();

	for (int i = 0; i < 3; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(halfWindowWidth - (halfWindowWidth * 0.6f), halfWindowHeight * 1.5f - (halfWindowHeight * 0.5 * i), 1.0f);
		modelStack.Scale(100.f, 100.f, 1.f);
		if (i == MenuOption)
			RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Select"));
		modelStack.PopMatrix();
	}
}
void Options::Exit()
{
	// Remove the entity from EntityManager
	EntityManager::GetInstance()->RemoveEntity(Options_BG);

	// Remove the meshes which are specific to Options
	MeshBuilder::GetInstance()->RemoveMesh("options_bg");

	// Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();
}