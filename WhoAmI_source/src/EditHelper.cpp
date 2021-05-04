/**
\file        EditHelper.cpp
\author      jinseob.park
\par         email: 0814owl@gmail.com
\par         course: GAM200
\date        12/15/2017
\brief       MapEdit stage.

*/
#include "EditHelper.h"
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
#include <map>

namespace FindersEngine
{
    EditInfo editdata;
    void InitPlayer(GameData& data)
    {
        data.Player = OBJECT_GEN->CreatePlayer(JSONREADER->getPlayerPos(), PlayerId);
    }
    void InitFinalDoor(GameData& data)
    {
    }
    void InitWall(GameData& data)
    {
        data.Wall_Count = JSONREADER->getWallCount();
        data.Wall.clear();
        for (unsigned int i = 0; i < data.Wall_Count; ++i)
        {
            data.Wall.push_back(OBJECT_GEN->CreateWall(JSONREADER->getWallPos(i), JSONREADER->getWallScale(i), WallId + i));
        }
    }
    void InitDoor(GameData& data)
    {
        data.Door_Count = JSONREADER->getDoorCount();
        data.Door.clear();
        for (unsigned int i = 0; i < data.Door_Count; ++i)
        {
            int type_offset = 8;

            std::map<int, std::string> door_tex_name =
            {
                { type_offset, "PIN_HDOOR.png" },
            { type_offset + 1, "PIN_VDOOR.png" }
            };

            data.Door.push_back(OBJECT_GEN->CreateObject(door_tex_name[JSONREADER->getDoorType(i)], JSONREADER->getDoorPos(i), JSONREADER->getDoorScale(i), ObjectType(JSONREADER->getDoorType(i)), ST_RECTANGLE, DoorId + i));
        }
    }
    void InitAmmo(GameData& data)
    {
        data.Ammo_Count = JSONREADER->getAmmoCount();
        data.Ammo.clear();

        for (unsigned int i = 0; i < data.Ammo_Count; ++i)
        {
            data.Ammo.push_back(OBJECT_GEN->CreateObject("PIN_AMMO.png", JSONREADER->getAmmoPos(i), JSONREADER->getAmmoScale(i), OT_AMMO, ST_CIRCLE, AmmoId + i));
        }
    }
    void InitZombie(GameData& data)
    {
        data.Zombie_Count = JSONREADER->getZombieCount();
        data.Zombie.clear();
        for (unsigned int i = 0; i < data.Zombie_Count; ++i)
        {
            data.Zombie.push_back(OBJECT_GEN->CreateZombie(JSONREADER->getZombiePos(i), ZombieId + i));
        }
    }
    void InitPistol(GameData& data)
    {
        data.Pistol = OBJECT_GEN->CreateObject("PIN_PISTOL.png", JSONREADER->getPistolPos(), glm::vec3(90, 90, 0), OT_PISTOL, ST_CIRCLE, 2000);
    }
    void InitArmor(GameData& data)
    {
    }


    void EditZombie(GameData& data)
    {
        float Camera_Z = GRAPHICS->camera_system->m_position.z;
        //Mouse
        glm::vec2 scale = editdata.Location;
        int mouse_x;
        int mouse_y;
        float world_x, world_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);

        world_x = Camera_Z * (((float)mouse_x - 640.f) / 840.f) + data.Player->GetPosition().x;
        world_y = Camera_Z * (-(float)mouse_y + 360.f) / 840.f + data.Player->GetPosition().y;

        if (editdata.Mode == TRANS)
        {
            if (editdata.IsSelect == true && editdata.TargetType == 1)
            {
                data.Zombie[editdata.TargetObject]->SetPosition(world_x + editdata.Location.x, world_y + editdata.Location.y);
                if (Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    editdata.TargetObject = -1;
                    editdata.Location = {0, 0};
                    editdata.IsSelect = false;
                }
                if (Input::IsMouseTriggered(SDL_BUTTON_RIGHT) && data.Zombie_Count > 0)
                {

                    OBJECT_FACTORY->Destroy(data.Zombie[editdata.TargetObject]);
                    data.Zombie.erase(data.Zombie.begin() + editdata.TargetObject);
                    data.Zombie_Count--;
                    editdata.TargetObject = -1;
                    editdata.Location = {0, 0};
                    editdata.IsSelect = false;
                }
            }
            else
            {
                for (unsigned int i = 0; i < data.Zombie.size(); ++i)
                {
                    if (Collision::MouseRectCollisionCheck_edit(data.Zombie[i], data.Player->GetPosition()) && Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                    {
                        editdata.Location = glm::vec2(data.Zombie[i]->GetPosition().x - world_x, data.Zombie[i]->GetPosition().y - world_y);
                        editdata.IsSelect = true;
                        editdata.TargetObject = i;
                        editdata.TargetType = 1;
                    }
                }
            }
        } //trans

        if (editdata.Mode == SCALE_X)
        {
            if (editdata.IsSelect == true && editdata.TargetType == 1)
            {
                editdata.Location = glm::vec2(data.Zombie[editdata.TargetObject]->GetPosition().x - world_x, data.Zombie[editdata.TargetObject]->GetPosition().y - world_y);
                scale = editdata.Location;
                if (scale.x < 0)
                    scale.x *= -1;
                if (scale.y < 0)
                    scale.y *= -1;

                scale *= 2;

                data.Zombie[editdata.TargetObject]->SetScale_x(scale.x * 840);
                if (Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    editdata.TargetObject = -1;
                    editdata.Location = {0, 0};
                    editdata.IsSelect = false;
                }
            }

            else
            {
                for (unsigned int i = 0; i < data.Zombie.size(); ++i)
                {
                    if (Collision::MouseRectCollisionCheck_edit(data.Zombie[i], data.Player->GetPosition()) && Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                    {
                        editdata.Location = glm::vec2(data.Zombie[i]->GetPosition().x - world_x, data.Zombie[i]->GetPosition().y - world_y);
                        editdata.IsSelect = true;
                        editdata.TargetObject = i;
                        editdata.TargetType = 1;
                    }
                }
            }
        } //scalex
        if (editdata.Mode == SCALE_Y)
        {
            if (editdata.IsSelect == true && editdata.TargetType == 1)
            {
                editdata.Location = glm::vec2(data.Zombie[editdata.TargetObject]->GetPosition().x - world_x, data.Zombie[editdata.TargetObject]->GetPosition().y - world_y);
                scale = editdata.Location;
                if (scale.x < 0)
                    scale.x *= -1;
                if (scale.y < 0)
                    scale.y *= -1;

                scale *= 2;

                data.Zombie[editdata.TargetObject]->SetScale_y(scale.y * 840);
                if (Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    editdata.TargetObject = -1;
                    editdata.Location = {0, 0};
                    editdata.IsSelect = false;
                }
            }

            else
            {
                for (unsigned int i = 0; i < data.Zombie.size(); ++i)
                {
                    if (Collision::MouseRectCollisionCheck_edit(data.Zombie[i], data.Player->GetPosition()) && Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                    {
                        editdata.Location = glm::vec2(data.Zombie[i]->GetPosition().x - world_x, data.Zombie[i]->GetPosition().y - world_y);
                        editdata.IsSelect = true;
                        editdata.TargetObject = i;
                        editdata.TargetType = 1;
                    }
                }
            }
        } //scaley
        if (editdata.Mode == ROTATION)
        {
            glm::vec2 vec{0, 0};
            if (editdata.IsSelect == true && editdata.TargetType == 1)
            {
                //vec = editdata.Location;
                vec = glm::vec2(data.Zombie[editdata.TargetObject]->GetPosition().x - world_x, data.Zombie[editdata.TargetObject]->GetPosition().y - world_y);
                data.Zombie[editdata.TargetObject]->SetRotation(atan2(vec.y, vec.x));
                if (Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    editdata.TargetObject = -1;
                    editdata.Location = {0, 0};
                    editdata.IsSelect = false;
                }
            }
            else
            {
                for (unsigned int i = 0; i < data.Zombie.size(); ++i)
                {
                    if (Collision::MouseRectCollisionCheck_edit(data.Zombie[i], data.Player->GetPosition()) && Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                    {
                        editdata.IsSelect = true;
                        editdata.TargetObject = i;
                        editdata.TargetType = 1;
                    }
                }
            }
        } //rot
    }
    void EditDoor(GameData& data)
    {
        float Camera_Z = GRAPHICS->camera_system->m_position.z;
        //Mouse
        glm::vec2 scale = editdata.Location;
        int mouse_x;
        int mouse_y;
        float world_x, world_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);

        world_x = Camera_Z * (((float)mouse_x - 640.f) / 840.f) + data.Player->GetPosition().x;
        world_y = Camera_Z * (-(float)mouse_y + 360.f) / 840.f + data.Player->GetPosition().y;


        if (editdata.Mode == TRANS)
        {
            if (editdata.IsSelect == true && editdata.TargetType == 2)
            {
                data.Door[editdata.TargetObject]->SetPosition(world_x + editdata.Location.x, world_y + editdata.Location.y);
                if (Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    editdata.TargetObject = -1;
                    editdata.Location = {0, 0};
                    editdata.IsSelect = false;
                }
                if (Input::IsMouseTriggered(SDL_BUTTON_RIGHT) && data.Door_Count > 0)
                {
                    OBJECT_FACTORY->Destroy(data.Door[editdata.TargetObject]);
                    data.Door.erase(data.Door.begin() + editdata.TargetObject);
                    data.Door_Count--;
                    editdata.TargetObject = -1;
                    editdata.Location = {0, 0};
                    editdata.IsSelect = false;
                }
            }
            else
            {
                for (unsigned int i = 0; i < data.Door.size(); ++i)
                {
                    if (Collision::MouseRectCollisionCheck_edit(data.Door[i], data.Player->GetPosition()) && Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                    {
                        editdata.Location = glm::vec2(data.Door[i]->GetPosition().x - world_x, data.Door[i]->GetPosition().y - world_y);
                        editdata.IsSelect = true;
                        editdata.TargetObject = i;
                        editdata.TargetType = 2;
                    }
                }
            }
        } // mode trans
        if (editdata.Mode == SCALE_X)
        {
            if (editdata.IsSelect == true && editdata.TargetType == 2)
            {
                editdata.Location = glm::vec2(data.Door[editdata.TargetObject]->GetPosition().x - world_x, data.Door[editdata.TargetObject]->GetPosition().y - world_y);
                scale = editdata.Location;
                if (scale.x < 0)
                    scale.x *= -1;
                if (scale.y < 0)
                    scale.y *= -1;

                scale *= 2;

                data.Door[editdata.TargetObject]->SetScale_x(scale.x * 1000);
                if (Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    editdata.TargetObject = -1;
                    editdata.Location = {0, 0};
                    editdata.IsSelect = false;
                }
            }

            else
            {
                for (unsigned int i = 0; i < data.Door.size(); ++i)
                {
                    if (Collision::MouseRectCollisionCheck_edit(data.Door[i], data.Player->GetPosition()) && Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                    {
                        editdata.Location = glm::vec2(data.Door[i]->GetPosition().x - world_x, data.Door[i]->GetPosition().y - world_y);
                        editdata.IsSelect = true;
                        editdata.TargetObject = i;
                        editdata.TargetType = 2;
                    }
                }
            }
        } //scale x

        if (editdata.Mode == SCALE_Y)
        {
            if (editdata.IsSelect == true && editdata.TargetType == 2)
            {
                editdata.Location = glm::vec2(data.Door[editdata.TargetObject]->GetPosition().x - world_x, data.Door[editdata.TargetObject]->GetPosition().y - world_y);
                scale = editdata.Location;
                if (scale.x < 0)
                    scale.x *= -1;
                if (scale.y < 0)
                    scale.y *= -1;

                scale *= 2;

                data.Door[editdata.TargetObject]->SetScale_y(scale.y * 840);
                if (Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    editdata.TargetObject = -1;
                    editdata.Location = {0, 0};
                    editdata.IsSelect = false;
                }
            }

            else
            {
                for (unsigned int i = 0; i < data.Door.size(); ++i)
                {
                    if (Collision::MouseRectCollisionCheck_edit(data.Door[i], data.Player->GetPosition()) && Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                    {
                        editdata.Location = glm::vec2(data.Door[i]->GetPosition().x - world_x, data.Door[i]->GetPosition().y - world_y);
                        editdata.IsSelect = true;
                        editdata.TargetObject = i;
                        editdata.TargetType = 2;
                    }
                }
            }
        } //scaley
    }

    void EditWall(GameData& data)
    {
        float Camera_Z = GRAPHICS->camera_system->m_position.z;
        //Mouse
        glm::vec2 scale = editdata.Location;
        int mouse_x;
        int mouse_y;
        float world_x, world_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);

        world_x = Camera_Z * (((float)mouse_x - 640.f) / 840.f) + data.Player->GetPosition().x;
        world_y = Camera_Z * (-(float)mouse_y + 360.f) / 840.f + data.Player->GetPosition().y;

        if (editdata.Mode == TRANS)
        {
            if (editdata.IsSelect == true && editdata.TargetType == 3)
            {
                data.Wall[editdata.TargetObject]->SetPosition(world_x + editdata.Location.x, world_y + editdata.Location.y);
                if (Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    editdata.TargetObject = -1;
                    editdata.Location = {0, 0};
                    editdata.IsSelect = false;
                }
                if (Input::IsMouseTriggered(SDL_BUTTON_RIGHT) && data.Wall_Count > 0)
                {
                    OBJECT_FACTORY->Destroy(data.Wall[editdata.TargetObject]);
                    data.Wall.erase(data.Wall.begin() + editdata.TargetObject);
                    data.Wall_Count--;
                    editdata.TargetObject = -1;
                    editdata.Location = {0, 0};
                    editdata.IsSelect = false;
                }
            }
            else
            {
                for (unsigned int i = 0; i < data.Wall.size(); ++i)
                {
                    if (Collision::MouseRectCollisionCheck_edit(data.Wall[i], data.Player->GetPosition()) && Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                    {
                        editdata.Location = glm::vec2(data.Wall[i]->GetPosition().x - world_x, data.Wall[i]->GetPosition().y - world_y);
                        editdata.IsSelect = true;
                        editdata.TargetObject = i;
                        editdata.TargetType = 3;
                    }
                }
            }
        } //mode trans
        if (editdata.Mode == SCALE_X)
        {
            if (editdata.IsSelect == true && editdata.TargetType == 3)
            {
                editdata.Location = glm::vec2(data.Wall[editdata.TargetObject]->GetPosition().x - world_x, data.Wall[editdata.TargetObject]->GetPosition().y - world_y);
                scale = editdata.Location;
                if (scale.x < 0)
                    scale.x *= -1;
                if (scale.y < 0)
                    scale.y *= -1;

                scale *= 2;

                data.Wall[editdata.TargetObject]->SetScale_x(scale.x * 1000);
                if (Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    editdata.TargetObject = -1;
                    editdata.Location = {0, 0};
                    editdata.IsSelect = false;
                }
            }
            else
            {
                for (unsigned int i = 0; i < data.Wall.size(); ++i)
                {
                    if (Collision::MouseRectCollisionCheck_edit(data.Wall[i], data.Player->GetPosition()) && Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                    {
                        editdata.Location = glm::vec2(data.Wall[i]->GetPosition().x - world_x, data.Wall[i]->GetPosition().y - world_y);
                        editdata.IsSelect = true;
                        editdata.TargetObject = i;
                        editdata.TargetType = 3;
                    }
                }
            }
        } //scale x
        if (editdata.Mode == SCALE_Y)
        {
            if (editdata.IsSelect == true && editdata.TargetType == 3)
            {
                editdata.Location = glm::vec2(data.Wall[editdata.TargetObject]->GetPosition().x - world_x, data.Wall[editdata.TargetObject]->GetPosition().y - world_y);
                scale = editdata.Location;
                if (scale.x < 0)
                    scale.x *= -1;
                if (scale.y < 0)
                    scale.y *= -1;

                scale *= 2;

                data.Wall[editdata.TargetObject]->SetScale_y(scale.y * 840);
                if (Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    editdata.TargetObject = -1;
                    editdata.Location = {0, 0};
                    editdata.IsSelect = false;
                }
            }

            else
            {
                for (unsigned int i = 0; i < data.Wall.size(); ++i)
                {
                    if (Collision::MouseRectCollisionCheck_edit(data.Wall[i], data.Player->GetPosition()) && Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                    {
                        editdata.Location = glm::vec2(data.Wall[i]->GetPosition().x - world_x, data.Wall[i]->GetPosition().y - world_y);
                        editdata.IsSelect = true;
                        editdata.TargetObject = i;
                        editdata.TargetType = 3;
                    }
                }
            }
        } //scaley
        if (editdata.Mode == ROTATION)
        {
            glm::vec2 vec{0, 0};
            if (editdata.IsSelect == true && editdata.TargetType == 3)
            {
                //vec = editdata.Location;
                vec = glm::vec2(data.Wall[editdata.TargetObject]->GetPosition().x - world_x, data.Wall[editdata.TargetObject]->GetPosition().y - world_y);
                data.Wall[editdata.TargetObject]->SetRotation(atan2(vec.y, vec.x));
                if (Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    editdata.TargetObject = -1;
                    editdata.Location = {0, 0};
                    editdata.IsSelect = false;
                }
            }
            else
            {
                for (unsigned int i = 0; i < data.Wall.size(); ++i)
                {
                    if (Collision::MouseRectCollisionCheck_edit(data.Wall[i], data.Player->GetPosition()) && Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                    {
                        editdata.IsSelect = true;
                        editdata.TargetObject = i;
                        editdata.TargetType = 3;
                    }
                }
            }
        } //rot
    }

    void EditAmmo(GameData& data)
    {
        float Camera_Z = GRAPHICS->camera_system->m_position.z;
        //Mouse
        glm::vec2 scale = editdata.Location;
        int mouse_x;
        int mouse_y;
        float world_x, world_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);

        world_x = Camera_Z * (((float)mouse_x - 640.f) / 840.f) + data.Player->GetPosition().x;
        world_y = Camera_Z * (-(float)mouse_y + 360.f) / 840.f + data.Player->GetPosition().y;

        if (editdata.Mode == TRANS)
        {
            if (editdata.IsSelect == true && editdata.TargetType == 4)
            {
                data.Ammo[editdata.TargetObject]->SetPosition(world_x + editdata.Location.x, world_y + editdata.Location.y);
                if (Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    editdata.TargetObject = -1;
                    editdata.Location = {0, 0};
                    editdata.IsSelect = false;
                }
                if (Input::IsMouseTriggered(SDL_BUTTON_RIGHT) && data.Wall_Count > 0)
                {
                    OBJECT_FACTORY->Destroy(data.Ammo[editdata.TargetObject]);
                    data.Ammo.erase(data.Ammo.begin() + editdata.TargetObject);
                    data.Ammo_Count--;
                    editdata.TargetObject = -1;
                    editdata.Location = {0, 0};
                    editdata.IsSelect = false;
                }
            }
            else
            {
                for (unsigned int i = 0; i < data.Ammo.size(); ++i)
                {
                    if (Collision::MouseRectCollisionCheck_edit(data.Ammo[i], data.Player->GetPosition()) && Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                    {
                        editdata.Location = glm::vec2(data.Ammo[i]->GetPosition().x - world_x, data.Ammo[i]->GetPosition().y - world_y);
                        editdata.IsSelect = true;
                        editdata.TargetObject = i;
                        editdata.TargetType = 4;
                    }
                }
            }
        } //mode trans
        if (editdata.Mode == SCALE_X)
        {
            if (editdata.IsSelect == true && editdata.TargetType == 4)
            {
                editdata.Location = glm::vec2(data.Ammo[editdata.TargetObject]->GetPosition().x - world_x, data.Ammo[editdata.TargetObject]->GetPosition().y - world_y);
                scale = editdata.Location;
                if (scale.x < 0)
                    scale.x *= -1;
                if (scale.y < 0)
                    scale.y *= -1;

                scale *= 2;

                data.Ammo[editdata.TargetObject]->SetScale_x(scale.x * 840);
                if (Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    editdata.TargetObject = -1;
                    editdata.Location = {0, 0};
                    editdata.IsSelect = false;
                }
            }

            else
            {
                for (unsigned int i = 0; i < data.Ammo.size(); ++i)
                {
                    if (Collision::MouseRectCollisionCheck_edit(data.Ammo[i], data.Player->GetPosition()) && Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                    {
                        editdata.Location = glm::vec2(data.Ammo[i]->GetPosition().x - world_x, data.Ammo[i]->GetPosition().y - world_y);
                        editdata.IsSelect = true;
                        editdata.TargetObject = i;
                        editdata.TargetType = 4;
                    }
                }
            }
        } //scalex
        if (editdata.Mode == SCALE_Y)
        {
            if (editdata.IsSelect == true && editdata.TargetType == 4)
            {
                editdata.Location = glm::vec2(data.Ammo[editdata.TargetObject]->GetPosition().x - world_x, data.Ammo[editdata.TargetObject]->GetPosition().y - world_y);
                scale = editdata.Location;
                if (scale.x < 0)
                    scale.x *= -1;
                if (scale.y < 0)
                    scale.y *= -1;

                scale *= 2;

                data.Ammo[editdata.TargetObject]->SetScale_y(scale.y * 840);
                if (Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    editdata.TargetObject = -1;
                    editdata.Location = {0, 0};
                    editdata.IsSelect = false;
                }
            }

            else
            {
                for (unsigned int i = 0; i < data.Ammo.size(); ++i)
                {
                    if (Collision::MouseRectCollisionCheck_edit(data.Ammo[i], data.Player->GetPosition()) && Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                    {
                        editdata.Location = glm::vec2(data.Ammo[i]->GetPosition().x - world_x, data.Ammo[i]->GetPosition().y - world_y);
                        editdata.IsSelect = true;
                        editdata.TargetObject = i;
                        editdata.TargetType = 4;
                    }
                }
            }
        } //scaley
        if (editdata.Mode == ROTATION)
        {
            glm::vec2 vec{0, 0};
            if (editdata.IsSelect == true && editdata.TargetType == 4)
            {
                //vec = editdata.Location;
                vec = glm::vec2(data.Ammo[editdata.TargetObject]->GetPosition().x - world_x, data.Ammo[editdata.TargetObject]->GetPosition().y - world_y);
                data.Ammo[editdata.TargetObject]->SetRotation(atan2(vec.y, vec.x));
                if (Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    editdata.TargetObject = -1;
                    editdata.Location = {0, 0};
                    editdata.IsSelect = false;
                }
            }
            else
            {
                for (unsigned int i = 0; i < data.Ammo.size(); ++i)
                {
                    if (Collision::MouseRectCollisionCheck_edit(data.Ammo[i], data.Player->GetPosition()) && Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                    {
                        editdata.IsSelect = true;
                        editdata.TargetObject = i;
                        editdata.TargetType = 4;
                    }
                }
            }
        } //rot
    }


    void EditPistol(GameData& data)
    {
        float Camera_Z = GRAPHICS->camera_system->m_position.z;
        //Mouse
        int mouse_x;
        int mouse_y;
        float world_x, world_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);

        world_x = Camera_Z * (((float)mouse_x - 640.f) / 840.f) + data.Player->GetPosition().x;
        world_y = Camera_Z * (-(float)mouse_y + 360.f) / 840.f + data.Player->GetPosition().y;

        if (editdata.Mode == TRANS)
        {
            if (editdata.IsSelect == true && editdata.TargetType == 5)
            {
                data.Pistol->SetPosition(world_x + editdata.Location.x, world_y + editdata.Location.y);
                if (Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    editdata.TargetObject = -1;
                    editdata.Location = {0, 0};
                    editdata.IsSelect = false;
                }
            }
            else
            {
                if (Collision::MouseRectCollisionCheck_edit(data.Pistol, data.Player->GetPosition()) && Input::IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    editdata.Location = glm::vec2(data.Pistol->GetPosition().x - world_x, data.Pistol->GetPosition().y - world_y);
                    editdata.IsSelect = true;
                    editdata.TargetObject = 1;
                    editdata.TargetType = 5;
                }
            }
        } //mode trans
    }


    void NotPause(void)
    {
        editdata.IsSelect = false;
        editdata.Location = {0, 0};
        editdata.TargetObject = 0;
        editdata.TargetType = 0;
    }


    void ModeHelper(void)
    {
        if (Input::IsTriggered(SDL_SCANCODE_F1) && Input::IsPressed(SDL_SCANCODE_LCTRL))
        {
            editdata.Mode = TRANS;
        }
        if (Input::IsTriggered(SDL_SCANCODE_F2) && Input::IsPressed(SDL_SCANCODE_LCTRL))
        {
            editdata.Mode = SCALE_X;
        }
        if (Input::IsTriggered(SDL_SCANCODE_F3) && Input::IsPressed(SDL_SCANCODE_LCTRL))
        {
            editdata.Mode = SCALE_Y;
        }
        if (Input::IsTriggered(SDL_SCANCODE_F4) && Input::IsPressed(SDL_SCANCODE_LCTRL))
        {
            editdata.Mode = ROTATION;
        }
        if (Input::IsTriggered(SDL_SCANCODE_F5) && Input::IsPressed(SDL_SCANCODE_LCTRL))
        {
            editdata.Mode = NONE;
        }
    }
    void LevelHelper(GameData& data)
    {
        if (Input::IsTriggered(SDL_SCANCODE_F1) && Input::IsPressed(SDL_SCANCODE_LALT))
        {
            data.Currentlevel = EDLevel1;
        }
        if (Input::IsTriggered(SDL_SCANCODE_F2) && Input::IsPressed(SDL_SCANCODE_LALT))
        {
            data.Currentlevel = NONELEVEL;
        }
    }
    int RoundInt(float value)
    {
        return (int)(value + 0.25f);
    }
}