#pragma once

#include "Scene.h"
#include "Mtx44.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "../FPSCamera.h"
#include "../SpriteEntity.h"

class SceneManager;
//class TextEntity;
class GameplaySettings : public Scene
{
public:
	GameplaySettings();
	~GameplaySettings();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	FPSCamera camera;
	SpriteEntity* GameplayBackground;
	
	bool sceneActive;
	float halfWindowWidth;
	float halfWindowHeight;

	unsigned int MenuOption, windowModeOption, ResolutionOption, windowWidth, windowHeight, MouseSensitivity;

	char Resolution_text[80];
	string WindowMode_text, MouseSensitivity_text;
};
