#ifndef SCENE_TEXT_H
#define SCENE_TEXT_H

#include "Scene.h"
#include "Mtx44.h"
#include "PlayerInfo/PlayerInfo.h"
#include "GroundEntity.h"
#include "FPSCamera.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "GenericEntity.h"
#include "SceneGraph/UpdateTransformation.h"
#include "Enemy\Enemy.h"
#include "../Lua/LuaInterface.h"

class ShaderProgram;
class SceneManager;
class TextEntity;
class Light;
class SceneText : public Scene
{
public:
	SceneText();
	~SceneText();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	static int luaPrintWaypoint(lua_State* L)
	{
		// get number of parameters passed in
		int n = lua_gettop(L);
		// if less than 4 then stop
		if (n < 4)
		{
			cout << "Error: PrintWaypoints(number, number, number, number)" << endl;
			lua_error(L);
			return 0;
		}

		// 1st - x position
		double x = lua_tonumber(L, 1);
		// 2nd - y position
		double y = lua_tonumber(L, 2);
		// 3rd - z position
		double z = lua_tonumber(L, 3);
		// 4th - size of cube
		double waypointNo = lua_tonumber(L, 4);
		// set the position

		cout << "Waypoint " << waypointNo << ": (" << x << ", " << y << ", " << z << ")" << endl;

		return 1;
	}
private:
	//SceneText(SceneManager* _sceneMgr); // This is used to register to SceneManager

	ShaderProgram* currProg;
	CPlayerInfo* playerInfo;
	GroundEntity* groundEntity;
	FPSCamera camera;
	TextEntity* textObj[3];
	Light* lights[2];

	GenericEntity* theCube;
	CEnemy* theEnemy;

//	static SceneText* sInstance; // The pointer to the object that gets registered
};

#endif