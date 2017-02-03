#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "SingletonTemplate.h"
#include <map>
#include <string>

class Scene;

class SceneManager : public Singleton<SceneManager>
{
	friend Singleton<SceneManager>;
public:
	// System Interface
	void Update(double dt);
	void Render();
	void Exit();

	// User Interface
	void AddScene(const std::string& name, Scene* scene);
	void RemoveScene(const std::string& name);
	void SetActiveScene(const std::string& name);
	void SetActiveCascadingScene(const std::string& name);
	void DeactivateCascadingScene(const std::string& name);
	bool CheckSceneExist(const std::string& name);

private:
	SceneManager();
	~SceneManager();

	std::map<std::string, Scene*> sceneMap;
	Scene* activeScene, *activeCascadingScene, *nextScene;
};

#endif // SCENE_MANAGER_H