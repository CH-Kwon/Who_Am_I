/**
\file        PlayerController.h
\author      Chiho Kwon
\par         email: erpo0811@gmail.com
\par         course: GAM200
\date        12/15/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once

#ifndef PLAYER_CONTROLLER_H_
#define PLAYER_CONTROLLER_H_

#include "Application.h"
#include "ComponentType.h"
#include "Controller.hpp"
#include "Input.h"
#include "Timer.hpp"
#include <glm/glm.hpp>
namespace FindersEngine
{

    class PlayerController : public Controller
    {
    public:
        PlayerController();
        ~PlayerController();

        void Init() override;
        void Update(float deltaTime) override;

        void Movement(float deltaTime);

        glm::vec2 target_direction;
        static bool isDead();
        static void GetDamage();
        Transform* transform; // position, scale, rotation
        static float player_health;
        static float player_armor;
        static bool getdamage;
        static bool isReachedSaveZone;


    private:
        unsigned player_experience;
        float player_expTimer;
        float light_lifeTime;

        bool is_ammo_cheat_on;
        float shoot_elapsed_time;

        glm::vec3 player_pos;

        glm::vec2 padtarget_direction;
        glm::vec2 left_pad;

        RigidBody* rigidbody;
        Collision* collision;
        Sprite* sprite;

        Object* zombie_object_;

        Object* HPbar;
        Object* Armorbar;
        Transform* HPbartransform;
        Sprite* HPbarsprite;
        Transform* Armorbartransform;
        Sprite* Armorbarsprite;

        glm::vec3 Hpbarpos;
        glm::vec3 Armorbarpos;
        float Hpbarposx;
        float Armorbarposx;

        float ratio_HPbar;
        float ratio_Armorbar;

        float ORIGIN_PLAYER_HEALTH;
        float ORIGIN_PLAYER_ARMOR;


    private:
        bool isInitShootTime = false;
        static Timer timer;
    };
}

#endif // !PLAYER_CONTROLLER_H_
