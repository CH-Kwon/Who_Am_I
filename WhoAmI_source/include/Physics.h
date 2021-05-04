/**
\file        Physics.h
\author      jungdae.chur
\par         email: wmdhwmdh@gmail.com
\par         course: GAM200
\date        12/13/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once

#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "System.h"
#include <vector>

namespace FindersEngine
{
    class RigidBody;
    class Collision;
    class Pair;

    class Physics : public System
    {
    public:
        Physics();
        ~Physics();

        //initialize systems
        void Init() override;

        void Update(float deltaTime) override;

        void push_back_RigidBody(RigidBody* rigidbody);

        std::vector<Collision*> m_vecpcollision;
        std::vector<RigidBody*> m_vecprb;

        std::vector<RigidBody*> walls_and_zombies;
        std::vector<RigidBody*> walls;

        Collision* m_collision;
        RigidBody* m_rigidbody;

    private:
        void ExplicitEuler(float deltaTime);
        void AbleToCollide();

        std::vector<Pair> m_vecpair;
    };
    extern Physics* PHYSICS;
};

#endif // !PHYSICS_H_
