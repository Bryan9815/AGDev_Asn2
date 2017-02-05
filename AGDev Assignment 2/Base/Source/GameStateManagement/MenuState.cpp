#include <iostream>
using namespace std;

#include "MenuState.h"
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

CMenuState::CMenuState()
{

}
CMenuState::~CMenuState()
{

}

void CMenuState::Init()
{
	// Create and attach the camera to the scene
	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
	GraphicsManager::GetInstance()->AttachCamera(&camera);

	halfWindowWidth = Application::GetInstance().GetWindowWidth() / 2.0f;
	halfWindowHeight = Application::GetInstance().GetWindowHeight() / 2.0f;

	// Load all the meshes
	MeshBuilder::GetInstance()->GenerateQuad("MENUSTATE_BKGROUND", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("MENUSTATE_BKGROUND")->textureID = LoadTGA("Image/GameStates/MainMenu.tga");	
	MenuStateBackground = Create::Sprite2DObject("MENUSTATE_BKGROUND", Vector3(halfWindowWidth, halfWindowHeight, 0.0f), Vector3(Application::GetInstance().GetWindowWidth(), Application::GetInstance().GetWindowHeight(), 0.0f));

	MeshBuilder::GetInstance()->GenerateText("Text", 16, 16);
	MeshBuilder::GetInstance()->GetMesh("Text")->textureID = LoadTGA("Image//calibri.tga");

	MeshBuilder::GetInstance()->GenerateQuad("Button", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("Button")->textureID = LoadTGA("Image/UI/RoundedButton.tga");

	MeshBuilder::GetInstance()->GenerateQuad("Select", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("Select")->textureID = LoadTGA("Image/UI/Select.tga");

	MeshBuilder::GetInstance()->GenerateQuad("Bar", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("Bar")->textureID = LoadTGA("Image/UI/bar.tga");

	MeshBuilder::GetInstance()->GenerateQuad("BarShadow", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("BarShadow")->textureID = LoadTGA("Image/UI/barShadow.tga");

	MenuOption = 0;

	cout << "CMenuState loaded\n" << endl;
}
void CMenuState::Update(double dt)
{
	//if (KeyboardController::GetInstance()->IsKeyReleased(VK_SPACE))
	//	SceneManager::GetInstance()->SetActiveScene("GameState");
	//if (KeyboardController::GetInstance()->IsKeyReleased('O'))
	//	SceneManager::GetInstance()->SetActiveScene("Options");
	//if (KeyboardController::GetInstance()->IsKeyReleased('S'))
	//	SceneManager::GetInstance()->SetActiveScene("Score");

	if (KeyboardController::GetInstance()->IsKeyReleased('W'))
		if (MenuOption > 0)
			MenuOption--;
	if (KeyboardController::GetInstance()->IsKeyReleased('S'))
		if (MenuOption < 2)
			MenuOption++;

	if (KeyboardController::GetInstance()->IsKeyReleased(VK_SPACE))
	{
		if (MenuOption == 0)
			SceneManager::GetInstance()->SetActiveScene("GameState");
		else if (MenuOption == 1)
			SceneManager::GetInstance()->SetActiveScene("Options");
		else if (MenuOption == 2)
			SceneManager::GetInstance()->SetActiveScene("Score");
	}
}
void CMenuState::Render()
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
		modelStack.PushMatrix();
		modelStack.Translate(halfWindowWidth, (halfWindowHeight * 0.8 - (halfWindowHeight * 0.25 * i)), 1.f);
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

	// Text
	modelStack.PushMatrix();
	modelStack.Translate(halfWindowWidth * 0.95, (halfWindowHeight * 0.8), 2.f);
	modelStack.Scale(halfWindowWidth * 0.03333, halfWindowHeight * 0.133333, 1.f);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("Text"), "Play", (1.f, 1.f, 1.f));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(halfWindowWidth * 0.95, (halfWindowHeight * 0.8 - (halfWindowHeight * 0.25)), 2.f);
	modelStack.Scale(halfWindowWidth * 0.03333, halfWindowHeight * 0.133333, 1.f);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("Text"), "Options", (1.f, 1.f, 1.f));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(halfWindowWidth * 0.95, (halfWindowHeight * 0.8 - (halfWindowHeight * 0.25 * 2)), 2.f);
	modelStack.Scale(halfWindowWidth * 0.03333, halfWindowHeight * 0.133333, 1.f);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("Text"), "Score", (1.f, 1.f, 1.f));
	modelStack.PopMatrix();
}
void CMenuState::Exit()
{
	// Remove the entity from EntityManager
	EntityManager::GetInstance()->RemoveEntity(MenuStateBackground);

	// Remove the meshes which are specific to CMenuState
	MeshBuilder::GetInstance()->RemoveMesh("MENUSTATE_BKGROUND");

	// Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();
}