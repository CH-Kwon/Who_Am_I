/**
\file        ZombieController.h
\author      Changuk Lee
\par         email: leechanguk0510@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#ifndef ZOMBIE_CONTROLLER_H_
#define ZOMBIE_CONTROLLER_H_

#include "Controller.hpp"
#include "RigidBody.h"
#include "Timer.hpp"
#include "Transform.hpp"
namespace FindersEngine
{
    class ZombieController : public Controller
    {
    public:
        ZombieController();
        ZombieController(float rotate, int direction);
        ~ZombieController();

        void Init() override;
        void Update(float dt) override;

        void Movement(float dt);

    private:
        int health;
        int Direction;
        unsigned int experience;
        float expTimer;
		bool isdetect;
        glm::vec3 pos;
        glm::vec3 rot;
        glm::vec3 oldrot;
        Transform* transform;
        Transform* playertransform;
        RigidBody* rigidbody;
        RigidBody* playerrigidbody;
        Collision* collision;

        Object* Zombiedetect;
        Transform* Zombiedetecttrans;
        Sprite* Zombiedetectsprite;

        Object* ZombieHealth1;
        Transform* ZombieHealth1trans;
        Sprite* ZombieHealth1sprite;

        Object* ZombieHealth2;
        Transform* ZombieHealth2trans;
        Sprite* ZombieHealth2sprite;

        Object* ZombieHealth3;
        Transform* ZombieHealth3trans;
        Sprite* ZombieHealth3sprite;

        Timer timer;
        bool aa;
    };
    extern ZombieController* ZOMBIE_CONT;
}
#endif
