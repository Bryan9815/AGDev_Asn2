#include <iostream>
using namespace std;

#include "GameplaySettings.h"
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

GameplaySettings::GameplaySettings()
{

}

GameplaySettings::~GameplaySettings()
{

}

void GameplaySettings::Init()
{
	// Create and attach the camera to the scene
	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
	GraphicsManager::GetInstance()->AttachCamera(&camera);

	// Load all the meshes
	MeshBuilder::GetInstance()->GenerateQuad("Gameplay_bg", Color(0, 0, 0), 1.f);
	MeshBuilder::GetInstance()->GetMesh("Gameplay_bg")->textureID = LoadTGA("Image/GameStates/GameplaySettings.tga");
	halfWindowWidth = Application::GetInstance().GetWindowWidth() / 2.0f;
	halfWindowHeight = Application::GetInstance().GetWindowHeight() / 2.0f;
	GameplayBackground = Create::Sprite2DObject("Gameplay_bg", Vector3(halfWindowWidth, halfWindowHeight * 0.925, 3.0f), Vector3(halfWindowWidth * 1.75f, halfWindowHeight * 1.65f, 0.0f));

	CLuaInterface::GetInstance()->Init("LuaScript/Application.lua");

	sceneActive = true;
	MenuOption = 0;

	windowModeOption = CLuaInterface::GetInstance()->getIntValue("windowMode");
	ResolutionOption = CLuaInterface::GetInstance()->getIntValue("Resolution");
	MouseSensitivity = CLuaInterface::GetInstance()->getIntValue("MouseSensitivity");

	cout << "GameplaySettings loaded\n" << endl;
}

void GameplaySettings::Update(double dt)
{
	if (KeyboardController::GetInstance()->IsKeyReleased('Q'))
		SceneManager::GetInstance()->SetActiveCascadingScene("AudioSettings");

	if (KeyboardController::GetInstance()->IsKeyReleased('W'))
		if (MenuOption > 0)
			MenuOption--;
	if (KeyboardController::GetInstance()->IsKeyReleased('S'))
		if (MenuOption < 3)
			MenuOption++;

	switch (MenuOption)
	{
	case 0:
		if (KeyboardController::GetInstance()->IsKeyReleased('A') && windowModeOption > 0)
			windowModeOption--;
		else if (KeyboardController::GetInstance()->IsKeyReleased('D') && windowModeOption < 1)
			windowModeOption++;
		break;
	case 1:
		if (KeyboardController::GetInstance()->IsKeyReleased('A') && ResolutionOption > 0)
			ResolutionOption--;
		else if (KeyboardController::GetInstance()->IsKeyReleased('D') && ResolutionOption < 5)
			ResolutionOption++;
		break;
	case 2:
		if (KeyboardController::GetInstance()->IsKeyReleased('A') && MouseSensitivity > 1)
			MouseSensitivity--;
		else if (KeyboardController::GetInstance()->IsKeyReleased('D') && MouseSensitivity < 10)
			MouseSensitivity++;
		break;
	case 3:
		if (KeyboardController::GetInstance()->IsKeyReleased(VK_SPACE))
			SceneManager::GetInstance()->DeactivateCascadingScene("GameplaySettings");
		break;
	}

	switch (windowModeOption)
	{
	case 0:
		WindowMode_text = "Fullscreen";
		break;
	case 1:
		WindowMode_text = "Windowed";
		break;
	}

	switch (ResolutionOption)
	{
	case 0:
		windowWidth = 800;
		windowHeight = 600;
		sprintf(Resolution_text, "%d x %d", windowWidth, windowHeight);
		break;
	case 1:
		windowWidth = 1024;
		windowHeight = 720;
		sprintf(Resolution_text, "%d x %d", windowWidth, windowHeight);
		break;
	case 2:
		windowWidth = 1440;
		windowHeight = 810;
		sprintf(Resolution_text, "%d x %d", windowWidth, windowHeight);
		break;
	case 3:
		windowWidth = 1600;
		windowHeight = 900;
		sprintf(Resolution_text, "%d x %d", windowWidth, windowHeight);
		break;
	case 4:
		windowWidth = 1600;
		windowHeight = 1024;
		sprintf(Resolution_text, "%d x %d", windowWidth, windowHeight);
		break;
	case 5:
		windowWidth = 1920;
		windowHeight = 1080;
		sprintf(Resolution_text, "%d x %d", windowWidth, windowHeight);
		break;
	}

	MouseSensitivity_text = to_string(MouseSensitivity);
}

void GameplaySettings::Render()
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();

	if (sceneActive)
	{
		for (int i = 0; i < 4; i++)
		{
			if (i == 0)
			{
				modelStack.PushMatrix();
				modelStack.Translate(halfWindowWidth * 0.4, halfWindowHeight * 1.26, 4.f);
				modelStack.Scale(halfWindowHeight * 0.17777, halfWindowHeight * 0.17777, 1.f);
				if (i == MenuOption)
					RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Select"));
				modelStack.PopMatrix();
			}

			if (i == 1)
			{
				modelStack.PushMatrix();
				modelStack.Translate(halfWindowWidth * 0.34, halfWindowHeight * 1.1, 4.f);
				modelStack.Scale(halfWindowHeight * 0.17777, halfWindowHeight * 0.17777, 1.f);
				if (i == MenuOption)
					RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Select"));
				modelStack.PopMatrix();
			}

			if (i == 2)
			{
				modelStack.PushMatrix();
				modelStack.Translate(halfWindowWidth * 0.35, halfWindowHeight * 0.93, 4.f);
				modelStack.Scale(halfWindowHeight * 0.17777, halfWindowHeight * 0.17777, 1.f);
				if (i == MenuOption)
					RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Select"));
				modelStack.PopMatrix();
			}

			if (i == 3)
			{
				modelStack.PushMatrix();
				modelStack.Translate(halfWindowWidth, (halfWindowHeight * 1.05 - (halfWindowHeight * 0.25 * 3)), 4.f);
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
		switch (windowModeOption)
		{
		case 0:
			modelStack.Translate(halfWindowWidth * 1.125, halfWindowHeight * 1.26, 5.f);
			break;
		case 1:
			modelStack.Translate(halfWindowWidth * 1.125, halfWindowHeight * 1.26, 5.f);
			break;
		}
		modelStack.Scale(halfWindowWidth * 0.03333, halfWindowHeight * 0.133333, 1.f);
		RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("Text"), WindowMode_text, (1.f, 1.f, 1.f));
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(halfWindowWidth * 1.1, halfWindowHeight * 1.1, 5.f);
		modelStack.Scale(halfWindowWidth * 0.03333, halfWindowHeight * 0.133333, 1.f);
		RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("Text"), Resolution_text, (1.f, 1.f, 1.f));
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(halfWindowWidth * 1.225, halfWindowHeight * 0.93, 5.f);
		modelStack.Scale(halfWindowWidth * 0.03333, halfWindowHeight * 0.133333, 1.f);
		RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("Text"), MouseSensitivity_text, (1.f, 1.f, 1.f));
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(halfWindowWidth * 0.925, halfWindowHeight * 1.05 - (halfWindowHeight * 0.25 * 3), 5.f);
		modelStack.Scale(halfWindowWidth * 0.03333, halfWindowHeight * 0.133333, 1.f);
		RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("Text"), "Exit", (1.f, 1.f, 1.f));
		modelStack.PopMatrix();
	}
}
void GameplaySettings::Exit()
{
	sceneActive = false;

	CLuaInterface::GetInstance()->saveIntValue("LuaScript/Application.lua", "windowMode", windowModeOption);
	CLuaInterface::GetInstance()->saveIntValue("LuaScript/Application.lua", "Resolution", ResolutionOption);
	CLuaInterface::GetInstance()->saveIntValue("LuaScript/Application.lua", "MouseSensitivity", MouseSensitivity);
	CLuaInterface::GetInstance()->saveIntValue("LuaScript/Gameplay.lua", "MouseSensitivity", MouseSensitivity);
	CLuaInterface::GetInstance()->saveIntValue("LuaScript/Application.lua", "width", windowWidth);
	CLuaInterface::GetInstance()->saveIntValue("LuaScript/Application.lua", "height", windowHeight);

	// Remove the entity from EntityManager
	EntityManager::GetInstance()->RemoveEntity(GameplayBackground);

	// Remove the meshes which are specific to GameplaySettings
	MeshBuilder::GetInstance()->RemoveMesh("Gameplay_bg");

	// Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();
}