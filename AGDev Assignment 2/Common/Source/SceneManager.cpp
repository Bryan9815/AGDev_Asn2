#include "SceneManager.h"
#include "Scene.h"
#include <iostream>
using std::cout;
using std::endl;

SceneManager::SceneManager() : activeScene(nullptr), activeCascadingScene(nullptr), nextScene(nullptr)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Update(double dt)
{
	if (activeCascadingScene == nextScene)
		activeCascadingScene->Update(dt);
	else if (activeScene == nextScene)
		activeScene->Update(dt);
}

void SceneManager::Render()
{
	if (activeScene)
		activeScene->Render();
	if (activeCascadingScene)
		activeCascadingScene->Render();
}

void SceneManager::Exit()
{
	// Delete all scenes stored and empty the entire map
	activeScene->Exit();
	activeScene = nullptr;
	std::map<std::string, Scene*>::iterator it, end;
	end = sceneMap.end();
	for (it = sceneMap.begin(); it != end; ++it)
	{
		delete it->second;
	}
	sceneMap.clear();
}

void SceneManager::AddScene(const std::string& name, Scene* scene)
{
	if (CheckSceneExist(name))
	{
		// Scene Exist, unable to proceed
		throw std::exception("Duplicate scene name provided");
	}

	if (scene == nullptr)
	{
		throw std::invalid_argument("Invalid scene pointer");
	}

	// Nothing wrong, add the scene to our map
	sceneMap[name] = scene;
}

void SceneManager::RemoveScene(const std::string& name)
{
	// Does nothing if it does not exist
	if (!CheckSceneExist(name))
		return;

	Scene* target = sceneMap[name];
	if (target == activeScene || target == nextScene)
	{
		throw std::exception("Unable to remove active/next scene");
	}

	// Delete and remove from our map
	delete target;
	sceneMap.erase(name);
}

void SceneManager::SetActiveScene(const std::string& name)
{
	if (!CheckSceneExist(name))
	{
		// Scene does not exist
		throw std::exception("Scene does not exist");
	}

	// Scene exist, set the next scene pointer to that scene
	nextScene = sceneMap[name];

	if (activeScene) // Check if a scene is already active
	{
		// Scene is valid, need to call appropriate function to exit
		activeScene->Exit();
	}

	activeScene = nextScene;
	activeScene->Init();
}

void SceneManager::SetActiveCascadingScene(const std::string& name)
{
	if (!CheckSceneExist(name))
	{
		// Scene does not exist
		throw std::exception("Scene does not exist");
	}

	// Scene exist, set the next scene pointer to that scene
	nextScene = sceneMap[name];

	if (activeCascadingScene) // Check if a cascading scene is already active
	{
		// Scene is valid, need to call appropriate function to exit
		activeCascadingScene->Exit();
	}

	activeCascadingScene = nextScene;
	activeCascadingScene->Init();
}

void SceneManager::DeactivateCascadingScene(const std::string& name)
{
	if (!CheckSceneExist(name))
	{
		// Scene does not exist
		throw std::exception("Scene does not exist");
	}

	if (activeCascadingScene) // Check if a cascading scene is already active
	{
		if (activeCascadingScene == sceneMap[name])  // Check if scene to be deactivated is actually the active cascading scene
		{
			// Scene is valid, need to call appropriate function to exit
			activeCascadingScene->Exit();
		}
	}
	nextScene = activeScene;
}

bool SceneManager::CheckSceneExist(const std::string& name)
{
	return sceneMap.count(name) != 0;
}