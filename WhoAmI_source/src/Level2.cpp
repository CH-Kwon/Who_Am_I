/**
\file        Level2.cpp
\author      Changuk Lee
\par         email: leechanguk0510@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
#include "EditHelper.h"
#include "Engine.h"
#include "GameList.h"
#include "GameStateManager.h"
#include "Graphics.h"
#include "Headers_Controllers.h"
#include "ObjectFactory.h"
#include "jsonReader.h"
#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include "Physics.h"
#include "Level2.h"


using namespace std;
using namespace glm;
namespace FindersEngine
{
    namespace
    {
        GameData EditObject;
    }
    void Level2StateLoad(void)
    {

    }

    void Level2StateInit(void)
    {
        GRAPHICS->BackgroundColor(0, 0, 0, 1);
        JSONREADER->ReadJsonLevel1();
        InitPlayer(EditObject);
        InitFinalDoor(EditObject);
        InitWall(EditObject);
        InitDoor(EditObject);
        InitAmmo(EditObject);
        InitZombie(EditObject);
        InitPistol(EditObject);
        InitArmor(EditObject);

        GRAPHICS->TurnOnSpotLight();

    }

    void Level2StateUpdate(float dt)
    {
        if (Input::GetInstance().IsTriggered(SDL_SCANCODE_ESCAPE))
            GAME_STATE->SetNextState(SL_MENU);
    }

    void Level2StateExit(void)
    {
        PHYSICS->walls_and_zombies.clear();
        PHYSICS->walls.clear();
        OBJECT_FACTORY->DestroyAllObjects();
    }

    void Level2StateUnload(void)
    {
    }
}
