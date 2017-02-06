#include <iostream>
using namespace std;

#include "AudioSettings.h"
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

AudioSettings::AudioSettings()
{

}
AudioSettings::~AudioSettings()
{

}

void AudioSettings::Init()
{
	// Create and attach the camera to the scene
	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
	GraphicsManager::GetInstance()->AttachCamera(&camera);

	// Load all the meshes
	MeshBuilder::GetInstance()->GenerateQuad("audio_bg", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("audio_bg")->textureID = LoadTGA("Image/GameStates/Audio.tga");
	
	halfWindowWidth = Application::GetInstance().GetWindowWidth() * 0.5f;
	halfWindowHeight = Application::GetInstance().GetWindowHeight() * 0.5f;

	AudioBackground = Create::Sprite2DObject("audio_bg", Vector3(halfWindowWidth, halfWindowHeight * 0.925, 3.0f), Vector3(halfWindowWidth * 1.75f, halfWindowHeight * 1.65f, 0.0f));

	sceneActive = true;
	MenuOption = 0;

	CLuaInterface::GetInstance()->Init("LuaScript/Gameplay.lua");

	SFX = CLuaInterface::GetInstance()->getIntValue("SFX");
	Music = CLuaInterface::GetInstance()->getIntValue("Music");

	SFX_text = to_string(SFX);
	Music_text = to_string(Music);

	cout << "AudioSettings loaded\n" << endl;
}

void AudioSettings::Update(double dt)
{
	if (KeyboardController::GetInstance()->IsKeyReleased('E'))
		SceneManager::GetInstance()->SetActiveCascadingScene("GameplaySettings");

	if (KeyboardController::GetInstance()->IsKeyReleased('W'))
		if (MenuOption > 0)
			MenuOption--;
	if (KeyboardController::GetInstance()->IsKeyReleased('S'))
		if (MenuOption < 2)
			MenuOption++;

	switch (MenuOption)
	{
	case 0:
		if (KeyboardController::GetInstance()->IsKeyDown('A') && SFX > 0)
			SFX--;
		else if (KeyboardController::GetInstance()->IsKeyDown('D') && SFX < 100)
			SFX++;
		break;
	case 1:
		if (KeyboardController::GetInstance()->IsKeyDown('A') && Music > 0)
			Music--;
		else if (KeyboardController::GetInstance()->IsKeyDown('D') && Music < 100)
			Music++;
		break;
	case 2:
		if (KeyboardController::GetInstance()->IsKeyReleased(VK_SPACE))
			SceneManager::GetInstance()->DeactivateCascadingScene("AudioSettings");
		break;
	}

	SFX_text = to_string(SFX);
	Music_text = to_string(Music);
}

void AudioSettings::Render()
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();

	if (sceneActive)
	{
		for (int i = 0; i < 3; i++)
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
				modelStack.Translate(halfWindowWidth * 0.4, halfWindowHeight * 1.1, 4.f);
				modelStack.Scale(halfWindowHeight * 0.17777, halfWindowHeight * 0.17777, 1.f);
				if (i == MenuOption)
					RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Select"));
				modelStack.PopMatrix();
			}

			if (i == 2)
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

		// Bars
		// SFX
		float sfxBarScale = (halfWindowWidth * 0.8) * (static_cast<float>(SFX) / 100.f);
		Math::Clamp(sfxBarScale, 0.01f, (float)(halfWindowWidth * 0.8));
		float sfxBarPosition = (halfWindowWidth * 1.185) + sfxBarScale * 0.5 - halfWindowWidth * 0.4;

		modelStack.PushMatrix();
		modelStack.Translate(sfxBarPosition, halfWindowHeight * 1.26, 4.f);
		modelStack.Scale(sfxBarScale, halfWindowHeight * 0.15, 1.f);
		RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Bar"));
		modelStack.PopMatrix();
		
		modelStack.PushMatrix();
		modelStack.Translate(halfWindowWidth * 1.185, halfWindowHeight * 1.26, 4.f);
		modelStack.Scale(halfWindowWidth * 0.8, halfWindowHeight * 0.15, 1.f);
		RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("BarShadow"));
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(halfWindowWidth * 1.575, halfWindowHeight * 1.26, 4.f);
		modelStack.Scale(halfWindowWidth * 0.03333, halfWindowHeight * 0.133333, 1.f);
		RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("Text"), SFX_text, (1.f, 1.f, 1.f));
		modelStack.PopMatrix();

		// Music
		float musicBarScale = (halfWindowWidth * 0.8) * (static_cast<float>(Music) / 100.f);
		Math::Clamp(musicBarScale, 0.01f, (float)(halfWindowWidth * 0.8));
		float musicBarPosition = (halfWindowWidth * 1.185) + musicBarScale * 0.5 - halfWindowWidth * 0.4;

		modelStack.PushMatrix();
		modelStack.Translate(musicBarPosition, halfWindowHeight * 1.1, 4.f);
		modelStack.Scale(musicBarScale, halfWindowHeight * 0.15, 1.f);
		RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Bar"));
		modelStack.PopMatrix();
		
		modelStack.PushMatrix();
		modelStack.Translate(halfWindowWidth * 1.185, halfWindowHeight * 1.1, 4.f);
		modelStack.Scale(halfWindowWidth * 0.8, halfWindowHeight * 0.15, 1.f);
		RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("BarShadow"));
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(halfWindowWidth * 1.575, halfWindowHeight * 1.1, 4.f);
		modelStack.Scale(halfWindowWidth * 0.03333, halfWindowHeight * 0.133333, 1.f);
		RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("Text"), Music_text, (1.f, 1.f, 1.f));
		modelStack.PopMatrix();

		// Text
		modelStack.PushMatrix();
		modelStack.Translate(halfWindowWidth * 0.925, halfWindowHeight * 1.05 - (halfWindowHeight * 0.25 * 3), 5.f);
		modelStack.Scale(halfWindowWidth * 0.03333, halfWindowHeight * 0.133333, 1.f);
		RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("Text"), "Exit", (1.f, 1.f, 1.f));
		modelStack.PopMatrix();
	}
}

void AudioSettings::Exit()
{
	sceneActive = false;

	CLuaInterface::GetInstance()->saveIntValue("LuaScript/Gameplay.lua", "SFX", SFX);
	CLuaInterface::GetInstance()->saveIntValue("LuaScript/Gameplay.lua", "Music", Music);

	// Remove the entity from EntityManager
	EntityManager::GetInstance()->RemoveEntity(AudioBackground);

	// Remove the meshes which are specific to AudioSettings
	MeshBuilder::GetInstance()->RemoveMesh("audio_bg");

	// Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();
}