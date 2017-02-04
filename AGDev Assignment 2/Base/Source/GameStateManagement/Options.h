#pragma once

#include "Scene.h"
#include "../FPSCamera.h"
#include "../SpriteEntity.h"
#include "../TextEntity.h"

class SceneManager;
//class TextEntity;
class Options : public Scene
{
public:
	Options();
	~Options();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	FPSCamera camera;
	SpriteEntity* Options_BG;

	float halfWindowWidth;
	float halfWindowHeight;
	unsigned int MenuOption;
};
