/**
\file        Collision.h
\author      jungdae.chur
\par         email: wmdhwmdh@gmail.com
\par         course: GAM200
\date        12/13/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once

#ifndef COLLISION_H_
#define COLLISION_H_

#include "Component.hpp"
#include "RigidBody.h"
#include <glm/glm.hpp>

namespace FindersEngine
{
    class Physics;
    class Transform;

    class Collision : public Component
    {
    public:
        Collision();
        ~Collision();
        void Init();

        //Chekc two AABB objects' collision
        //return true if collided, and false otherwise
        bool AABBAABBCollisionCheck(Object* pA, Object* pB);

        //Check two circle object's collision
        //return true if collided, and false otherwise
        bool CircleCircleCollisionCheck(Object* pA, Object* pB);

        //Check among circle and rectangle object's collision
        //return true if collided, and false otherwise
        bool CircleRectCollisionCheck(Object* pA, Object* pB);

        //Check raycasting bullet
        //return true if collided, and false otherwise
        bool RayCastCollisionCheck(Object* pA, float bullet_range);

        //Check raycasting bullet for gamepad
        //return true if collided, and false otherwise
        bool RayCastCollisionCheckForPad(Object* pA, float bullet_range);

        // Assign the distance between player and wall
        // To use for light logic
        void SaveWallDistance(Object* pA);

        // Assign the distance between player and wall
        // To use for light logic only for game pad
        void SaveWallDistanceForPad(Object* pA);

        //Check among circle and arc object's collision
        //It will be used the enemy's viewpoint
        //return true if collided, and false otherwise
        // It can collide with circle, ONLY
        bool FieldViewCollisionCheck(Object* pA, Object* pB, float view_range);

        //check among mouse position and rectangle
        //return false if it doesn't collide, and true otherwise
        static bool MouseRectCollisionCheck(Object* pA);

        //check among mouse position and rectangle
        //return false if it doesn't collide, and true otherwise
        //It will be used only in EDIT MODE.
        //It can click and drop the object.
        static bool MouseRectCollisionCheck_edit(Object* pA, glm::vec3 pos);

        float Max(float x, float y) { return x > y ? x : y; }
        float Min(float x, float y) { return x < y ? x : y; }

    private:
        friend class Physics;

        Transform* pm_transform = nullptr;

        glm::vec3 m_offset;
        glm::vec2 m_size;
    };
    extern Collision* COLLISION;
};

#endif // !COLLISION_H_
