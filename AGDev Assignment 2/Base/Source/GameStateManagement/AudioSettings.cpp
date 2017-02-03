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
	//MeshBuilder::GetInstance()->GetMesh("audio_bg")->textureID = LoadTGA("Image//IntroState.tga");
	float halfWindowWidth = Application::GetInstance().GetWindowWidth() / 2.0f;
	float halfWindowHeight = Application::GetInstance().GetWindowHeight() / 2.0f;
	AudioBackground = Create::Sprite2DObject("audio_bg", Vector3(halfWindowWidth, halfWindowHeight + Application::GetInstance().GetWindowHeight() / 15.0f, 3.0f), Vector3(halfWindowWidth * 1.75f, halfWindowHeight * 1.65f, 0.0f));

	cout << "AudioSettings loaded\n" << endl;
}

void AudioSettings::Update(double dt)
{
	if (KeyboardController::GetInstance()->IsKeyReleased(VK_SPACE))
		SceneManager::GetInstance()->DeactivateCascadingScene("AudioSettings");
	if (KeyboardController::GetInstance()->IsKeyReleased('E'))
		SceneManager::GetInstance()->SetActiveCascadingScene("InputSettings");
}

void AudioSettings::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
}
void AudioSettings::Exit()
{
	// Remove the entity from EntityManager
	EntityManager::GetInstance()->RemoveEntity(AudioBackground);

	// Remove the meshes which are specific to AudioSettings
	MeshBuilder::GetInstance()->RemoveMesh("audio_bg");

	// Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();
}