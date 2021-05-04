/**
\file        PlayerLogic.cpp
\author      SeongHyun Hong
\par         email: tjdgus3174@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "PlayerLogic.h"
#include "Application.h"
#ifdef _WIN32
#include "SDL.h"
#else
#include <SDL2/SDL.h>
#endif
#include "Object.h"
#include "ObjectGenerator.h"
#include "RigidBody.h"
#include <algorithm>
#include <iostream>

glm::vec2 target_direction = glm::vec2(0.f, 0.f);
glm::vec2 padtarget_direction = glm::vec2(0.f, 0.f);
glm::vec2 right_pad = glm::vec2(0, 0);
namespace FindersEngine
{
    Object* bullet_obj_;
    Object* bullet_obj_pad;
    PlayerLogic* PLAYERLOGIC = new PlayerLogic;
    unsigned id = 10000;
    PlayerLogic::PlayerLogic()
    {
        PLAYERLOGIC = this;
    }
    PlayerLogic::~PlayerLogic()
    {
        delete PLAYERLOGIC;
    }
    void PlayerLogic::ShootBullet(Transform* player, float bullet_range)
    {
        bullet_obj_ = nullptr;
        glm::vec3 bullet_position = player->getPosition();
        glm::vec3 bullet_rot = player->getRotation();

        //Mouse
        int mouse_x;
        int mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        glm::vec2 world_mouse_two(mouse_x, mouse_y);
        world_mouse_two = APPLICATION->screen_to_world(world_mouse_two);

        glm::vec3 bullet_size = glm::vec3(bullet_range, 50.f, 0.f);

        bullet_position.x += target_direction.x * 1.3f;
        bullet_position.y += target_direction.y * 1.3f;
        bullet_obj_ = OBJECT_GEN->CreateBullet(bullet_position, bullet_rot, bullet_size, id);
        ++id;
        --player->GetOwner()->curr_ammo;
    }
    void PlayerLogic::ShootBulletWithPad(Transform* player, float bullet_range)
    {
        bullet_obj_pad = nullptr;

        glm::vec3 bullet_position = player->getPosition();
        glm::vec3 bullet_rot = player->getRotation();

        glm::vec3 bullet_size = glm::vec3(bullet_range, 50.f, 0.f);

        bullet_position.x += padtarget_direction.x * 1.3f;
        bullet_position.y += padtarget_direction.y * 1.3f;

        bullet_obj_pad = OBJECT_GEN->CreateBullet(bullet_position, bullet_rot, bullet_size, id);
        ++id;
        --player->GetOwner()->curr_ammo;
    }
    void PlayerLogic::mouse_rotation(Transform* player)
    {
        int mouse_x;
        int mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        glm::vec2 world_mouse(mouse_x, mouse_y);
        world_mouse = APPLICATION->screen_to_world(world_mouse);
        target_direction = glm::normalize(world_mouse - glm::vec2(player->getPosition()));

        float radian = glm::atan(target_direction.y, target_direction.x);
        glm::vec3 rot(0.f, 0.f, radian);
        player->setRotation(rot);
    }
    void PlayerLogic::pad_rotation(Transform* player)
    {
        right_pad = APPLICATION->get_right_pad();
        right_pad = APPLICATION->screen_to_world(right_pad);
        padtarget_direction = glm::normalize(right_pad - glm::vec2(player->getPosition()));

        float radian = glm::atan(padtarget_direction.y, padtarget_direction.x);
        glm::vec3 rot(0.f, 0.f, radian);
        player->setRotation(rot);
    }
}
