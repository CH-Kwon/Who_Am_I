/**
\file        Level3.cpp
\author      Changuk Lee
\par         email: leechanguk0510@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "Level3.h"
#include "Application.h"
#include "ButtonController.h"
#include "Collision.h"
#include "GameList.h"
#include "GameStateManager.h"
#include "Graphics.h"
#include "Hud.h"
#include "HudController.h"
#include "Input.h"
#include "Menu.h"
#include "ObjectFactory.h"
#include "SoundManager.h"
#include "Sprite.h"
#include "jsonReader.h"
#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include "Physics.h"
#include "EditHelper.h"

#define WIDTH 1280
#define HEIGHT 640

using namespace std;
using namespace glm;

namespace FindersEngine
{
    namespace
    {
        GameData EditObject;
    }
    namespace Level3
    {
    };

    void Level3StateLoad(void)
    {
        cout << "-----------------Level3 -------------------\n";
        cout << "Level1StateLoad\n";

        using namespace Level3;
    }

    void Level3StateInit(void)
    {
        GRAPHICS->BackgroundColor(0.f, 0.f, 0.f, 0.2f);
        JSONREADER->ReadJsonEdit();
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


    void Level3StateUpdate(float dt)
    {
        if (Input::GetInstance().IsTriggered(SDL_SCANCODE_ESCAPE))
            GAME_STATE->SetNextState(SL_MENU);
    }

    void Level3StateExit(void)
    {
        PHYSICS->walls_and_zombies.clear();
        PHYSICS->walls.clear();
        cout << "Level3StateExit" << endl;
        OBJECT_FACTORY->DestroyAllObjects();
    }

    void Level3StateUnload(void)
    {
        cout << "Level3StateUnload\n"
            << endl;
    }
}
