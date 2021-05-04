/**
\file        MapEditor.cpp
\author      jinseob.park
\par         email: 0814owl@gmail.com
\par         course: GAM200
\date        12/15/2017
\brief       MapEdit stage.
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
#include "MapEditor.h"
#include "Application.h"
#include "CameraSystem.h"
#include "Collision.h"
#include "ComponentType.h"
#include "EditHelper.h"
#include "Engine.h"
#include "GameList.h"
#include "GameStateManager.h"
#include "Graphics.h"
#include "Headers_Components.h"
#include "Headers_Controllers.h"
#include "JsonWriter.h"
#include "LTimer.hpp"
#include "Object.h"
#include "ObjectFactory.h"
#include "ObjectGenerator.h"
#include "Texture.h"
#include "Timer.hpp"
#include "jsonReader.h"
#include <functional>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include "Physics.h"


using namespace std;
using namespace glm;
namespace FindersEngine
{
    namespace
    {
        GameData EditObject;
    }
    void MapEditStateLoad(void)
    {
    }

    void MapEditStateInit(void)
    {
        //EditObject.Currentlevel = NONELEVEL;
        GRAPHICS->BackgroundColor(0, 0, 0, 1);
        if (EditObject.Currentlevel == EDLevel1)
            JSONREADER->ReadJsonLevel1();
        else
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

        ENGINE->isPause = true;
    }

    void MapEditStateUpdate(float dt)
    {

        if (ENGINE->isPause)
        {
            float Camera_Z = GRAPHICS->camera_system->m_position.z;
            if (Input::IsTriggered(SDL_SCANCODE_L))
                GAME_STATE->SetNextState(SL_MAPEDIT);

            //Mouse
            int mouse_x;
            int mouse_y;
            SDL_GetMouseState(&mouse_x, &mouse_y);

            glm::vec2 world_mouse(mouse_x, mouse_y);

            if (Input::GetInstance().IsPressed(SDL_SCANCODE_PAGEUP))
                GRAPHICS->camera_system->m_position.z -= 0.1f;
            if (Input::GetInstance().IsPressed(SDL_SCANCODE_PAGEDOWN))
                GRAPHICS->camera_system->m_position.z += 0.1f;

            EditZombie(EditObject);
            EditWall(EditObject);
            EditDoor(EditObject);
            EditAmmo(EditObject);
            EditPistol(EditObject);
            ModeHelper();
            LevelHelper(EditObject);
            //add
            if (Input::GetInstance().IsTriggered(SDL_SCANCODE_Z))
            {
                EditObject.Zombie.push_back(OBJECT_GEN->CreateZombie(glm::vec3(Camera_Z * (((float)mouse_x - 640.f) / 840.f) + EditObject.Player->GetPosition().x, Camera_Z * (-(float)mouse_y + 360.f) / 840.f + EditObject.Player->GetPosition().y, 0), ZombieId + EditObject.Zombie_Count));
                EditObject.Zombie_Count++;
            }
            if (Input::GetInstance().IsTriggered(SDL_SCANCODE_D))
            {
                EditObject.Door.push_back(OBJECT_GEN->CreateObject("PIN_HDOOR.png", glm::vec3(Camera_Z * (((float)mouse_x - 640.f) / 840.f) + EditObject.Player->GetPosition().x, RoundInt(Camera_Z * (-(float)mouse_y + 360.f) / 840.f + EditObject.Player->GetPosition().y), 0), glm::vec3(400, 150, 0), ObjectType(8), ST_RECTANGLE, DoorId + EditObject.Door_Count));
                EditObject.Door_Count++;
            }
            if (Input::GetInstance().IsTriggered(SDL_SCANCODE_F))
            {
                EditObject.Door.push_back(OBJECT_GEN->CreateObject("PIN_VDOOR.png", glm::vec3(RoundInt(Camera_Z * (((float)mouse_x - 640.f) / 840.f) + EditObject.Player->GetPosition().x), Camera_Z * (-(float)mouse_y + 360.f) / 840.f + EditObject.Player->GetPosition().y, 0), glm::vec3(150, 400, 0), ObjectType(9), ST_RECTANGLE, DoorId + EditObject.Door_Count));
                EditObject.Door_Count++;
            }
            if (Input::GetInstance().IsTriggered(SDL_SCANCODE_C))
            {
                EditObject.Wall.push_back(OBJECT_GEN->CreateWall(glm::vec3(Camera_Z * (((float)mouse_x - 640.f) / 840.f) + EditObject.Player->GetPosition().x, RoundInt(Camera_Z * (-(float)mouse_y + 360.f) / 840.f + EditObject.Player->GetPosition().y), 0), glm::vec3(9500, 100, 0), WallId + EditObject.Wall_Count));
                EditObject.Wall_Count++;
            }
            if (Input::GetInstance().IsTriggered(SDL_SCANCODE_V))
            {
                EditObject.Wall.push_back(OBJECT_GEN->CreateWall(glm::vec3(RoundInt(Camera_Z * (((float)mouse_x - 640.f) / 840.f) + EditObject.Player->GetPosition().x), Camera_Z * (-(float)mouse_y + 360.f) / 840.f + EditObject.Player->GetPosition().y, 0), glm::vec3(100, 9500, 0), WallId + EditObject.Wall_Count));
                EditObject.Wall_Count++;
            }
            if (Input::GetInstance().IsTriggered(SDL_SCANCODE_B))
            {
                EditObject.Wall.push_back(OBJECT_GEN->CreateWall(glm::vec3(Camera_Z * (((float)mouse_x - 640.f) / 840.f) + EditObject.Player->GetPosition().x, Camera_Z * (-(float)mouse_y + 360.f) / 840.f + EditObject.Player->GetPosition().y, 0), glm::vec3(100, 100, 0), WallId + EditObject.Wall_Count));
                EditObject.Wall_Count++;
            }
            if (Input::GetInstance().IsTriggered(SDL_SCANCODE_A))
            {
                EditObject.Ammo.push_back(OBJECT_GEN->CreateObject("PIN_AMMO.png", glm::vec3(Camera_Z * (((float)mouse_x - 640.f) / 840.f) + EditObject.Player->GetPosition().x, Camera_Z * (-(float)mouse_y + 360.f) / 840.f + EditObject.Player->GetPosition().y, 0), glm::vec3(90, 90, 0), OT_AMMO, ST_CIRCLE, AmmoId + EditObject.Ammo_Count));
                EditObject.Ammo_Count++;
            }
            if (Input::GetInstance().IsTriggered(SDL_SCANCODE_X))
            {
                EditObject.Pistol->SetPosition(Camera_Z * (((float)mouse_x - 640.f) / 840.f) + EditObject.Player->GetPosition().x, Camera_Z * (-(float)mouse_y + 360.f) / 840.f + EditObject.Player->GetPosition().y);
            }
            //write
            if (Input::GetInstance().IsTriggered(SDL_SCANCODE_S))
            {
                JSONWRITER->jsonWriterEdit(EditObject);
            }
            //save
        }
        else
            NotPause();

        if (Input::GetInstance().IsTriggered(SDL_SCANCODE_ESCAPE))
            GAME_STATE->SetNextState(SL_MENU);
        //restart
        if (Input::GetInstance().IsTriggered(SDL_SCANCODE_R))
            GAME_STATE->SetNextState(SL_MAPEDIT);

        if (Input::GetInstance().IsTriggered(SDL_SCANCODE_HOME))
            //if (Input::GetInstance().IsTriggered(SDL_SCANCODE_F6))
            GRAPHICS->BackgroundColor(0, 0, 0, 1);

        if (Input::GetInstance().IsTriggered(SDL_SCANCODE_END))
            //if (Input::GetInstance().IsTriggered(SDL_SCANCODE_F7))
            GRAPHICS->BackgroundColor(150, 150, 150, 1);
    }

    void MapEditStateExit(void)
    {
        PHYSICS->walls_and_zombies.clear();
        PHYSICS->walls.clear();
        ENGINE->isPause = false;
        PHYSICS->walls_and_zombies.clear();
        PHYSICS->walls.clear();
        OBJECT_FACTORY->DestroyAllObjects();
    }

    void MapEditStateUnload(void)
    {
    }
}
