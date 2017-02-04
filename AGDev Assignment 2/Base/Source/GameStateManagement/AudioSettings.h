#pragma once

#include "Scene.h"
#include "Mtx44.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "../FPSCamera.h"
#include "../SpriteEntity.h"

class SceneManager;
//class TextEntity;
class AudioSettings : public Scene
{
public:
	AudioSettings();
	~AudioSettings();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	FPSCamera camera;
	SpriteEntity* AudioBackground;

	bool sceneActive;
	float halfWindowWidth;
	float halfWindowHeight;

	int SFX, Music;
	string SFX_text, Music_text;

	unsigned int MenuOption;
	//	TextEntity* textObj[3];
};
