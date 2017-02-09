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
	// Create and attach the camera to the scene
	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
	GraphicsManager::GetInstance()->AttachCamera(&camera);

	// Load all the meshes
	MeshBuilder::GetInstance()->GenerateQuad("options_bg", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("options_bg")->textureID = LoadTGA("Image/GameStates/Options.tga");
	halfWindowWidth = Application::GetInstance().GetWindowWidth() / 2.0f;
	halfWindowHeight = Application::GetInstance().GetWindowHeight() / 2.0f;
	Options_BG = Create::Sprite2DObject("options_bg", Vector3(halfWindowWidth, halfWindowHeight, 0.0f), Vector3(Application::GetInstance().GetWindowWidth(), Application::GetInstance().GetWindowHeight(), 0.0f));
	
	MenuOption = 0;

	cout << "Options loaded\n" << endl;
}
void Options::Update(double dt)
{
	if (KeyboardController::GetInstance()->IsKeyReleased('W'))
		if(MenuOption > 0)
			MenuOption--;
	if (KeyboardController::GetInstance()->IsKeyReleased('S'))
		if (MenuOption < 2)
			MenuOption++;

	if (KeyboardController::GetInstance()->IsKeyReleased(VK_SPACE))
	{
		if (MenuOption == 0)
			SceneManager::GetInstance()->SetActiveCascadingScene("AudioSettings");
		else if (MenuOption == 1)
			SceneManager::GetInstance()->SetActiveCascadingScene("GameplaySettings");
		else if (MenuOption == 2)
			SceneManager::GetInstance()->SetActiveScene("MenuState");
	}
}
void Options::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//GraphicsManager::GetInstance()->UpdateLightUniforms();
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();

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
		if (i != 2)
		{
			modelStack.PushMatrix();
			modelStack.Translate(halfWindowWidth, (halfWindowHeight * 1.5 - (halfWindowHeight * 0.25 * i)), 1.f);
			modelStack.Scale(halfWindowWidth * 0.75, halfWindowHeight * 0.222222, 1.f);
			RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Button"));
			if (i == MenuOption)
			{
				modelStack.PushMatrix();
				modelStack.Translate(-0.6f, 0.f, 0.f);
				modelStack.Scale(0.16666f, 1.f, 1.f);
				RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Select"));
				modelStack.PopMatrix();
			}
			modelStack.PopMatrix();
		}
		if (i == 2)
		{
			modelStack.PushMatrix();
			modelStack.Translate(halfWindowWidth, (halfWindowHeight - (halfWindowHeight * 0.75)), 1.f);
			modelStack.Scale(halfWindowWidth * 0.75, halfWindowHeight * 0.222222, 1.f);
			RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Button"));
			if (i == MenuOption)
			{
				modelStack.PushMatrix();
				modelStack.Translate(-0.6f, 0.f, 0.f);
				modelStack.Scale(0.16666f, 1.f, 1.f);
				RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Select"));
				modelStack.PopMatrix();
			}
			modelStack.PopMatrix();
		}
	}

	// Text
	modelStack.PushMatrix();
	modelStack.Translate(halfWindowWidth * 0.925, (halfWindowHeight * 1.5), 2.f);
	modelStack.Scale(halfWindowWidth * 0.03333, halfWindowHeight * 0.133333, 1.f);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("Text"), "Audio", (1.f, 1.f, 1.f));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(halfWindowWidth * 0.875, halfWindowHeight * 1.5 - (halfWindowHeight * 0.25), 2.f);
	modelStack.Scale(halfWindowWidth * 0.03333, halfWindowHeight * 0.133333, 1.f);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("Text"), "Gameplay", (1.f, 1.f, 1.f));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(halfWindowWidth * 0.925, (halfWindowHeight - (halfWindowHeight * 0.75)), 2.f);
	modelStack.Scale(halfWindowWidth * 0.03333, halfWindowHeight * 0.133333, 1.f);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("Text"), "Exit", (1.f, 1.f, 1.f));
	modelStack.PopMatrix();
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