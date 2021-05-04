/**
\file        RigidBody.h
\author      jungdae.chur
\par         email: wmdhwmdh@gmail.com
\par         course: GAM200
\date        12/13/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once

#ifndef REGID_BODY_H_
#define REGID_BODY_H_

#include "Collision.h"
#include "Component.hpp"
#include <glm/detail/type_vec3.hpp>

namespace FindersEngine
{
    class Transform; //dependency components
    class Collision;

    class RigidBody : public Component
    {
    public:
        RigidBody(glm::vec3 vel, float invmass);
        ~RigidBody();

        void Init() override;

        // default response of collision
        void CollisionResponseGeneral(RigidBody* pA, RigidBody* pB);

        // Collision response with ball
        void CollisionResponseWithWall(RigidBody* pA, RigidBody* pB);

        // Response when Zombies hit by bullet
        void CollisionResponseWithBullet(RigidBody* pA, RigidBody* pB);

        // Response when player get to the normal door
        void CollisionResponseWithDoor(RigidBody* pA, RigidBody* pB);

        // Resolving intersection when collision occured (Circle-Circle)
        void ResolveIntersection(RigidBody* pA, RigidBody* pB);

        // When player get to the last door
        void CollisionResponseWithFinal(RigidBody* pA);

        // Generate Font 'Press (Action key)'
        void GenerateActionHint();

        // Remove Font 'Press (Action key)'
        void RemoveActionHint();

        float Max(float x, float y) { return x > y ? x : y; }

        float wall_distance; // Be used for hand light system

    private:
        RigidBody() : Component(CT_RIGID_BODY){};
        friend class Physics;
        friend class Collision;
        friend class PlayerLogic;

        friend class ZombieController; // pm_force, pm_vel
        friend class PlayerController; // pm_force, pm_vel

        glm::vec3 pm_force;
        glm::vec3 pm_vel;
        //Using components
        Transform* m_pTransform = nullptr;
        Collision* m_pCollision = nullptr;

        float pm_invMass;
    };
}

#endif // !REGID_BODY_H
