/**
\file        PhysicsLogic.cpp
\author      jungdae.chur
\par         email: wmdhwmdh@gmail.com
\par         course: GAM200
\date        12/13/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "PhysicsLogic.h"
#include "Object.h"
#include "Physics.h"
#include "RigidBody.h"
#include "Transform.hpp"
#include "jsonReader.h"

namespace FindersEngine
{
    PhysicsLogic* PHYSICS_LOGIC = nullptr;

    void PhysicsLogic::SeperateByRoom()
    {
        for (auto it = PHYSICS->m_vecprb.begin(); it != PHYSICS->m_vecprb.end(); ++it)
        {
            Transform* it_pos = static_cast<Transform*>((*it)->GetOwner()->GetComponent(CT_TRANSFORM));

            if (it_pos->getPosition().y < JSONREADER->getWall2Pos().y)
            {
                if (it_pos->getPosition().x <= JSONREADER->getWall6Pos().x)
                {
                    (*it)->GetOwner()->room_number = 1; // Room 1
                }
                else if ((it_pos->getPosition().x >= JSONREADER->getWall6Pos().x) && (it_pos->getPosition().x < JSONREADER->getWall5Pos().x))
                {
                    (*it)->GetOwner()->room_number = 6; // Room 6
                }
                else if ((it_pos->getPosition().x >= JSONREADER->getWall5Pos().x) && (it_pos->getPosition().x < JSONREADER->getWall7Pos().x))
                {
                    (*it)->GetOwner()->room_number = 7; // Room 7
                }
            }
            if ((it_pos->getPosition().y >= JSONREADER->getWall2Pos().y) && (it_pos->getPosition().y < JSONREADER->getWall1Pos().y))
            {
                if (it_pos->getPosition().x <= JSONREADER->getWall6Pos().x)
                {
                    (*it)->GetOwner()->room_number = 2; // Room 2
                }
                else if ((it_pos->getPosition().x >= JSONREADER->getWall6Pos().x) && (it_pos->getPosition().x < JSONREADER->getWall5Pos().x))
                {
                    (*it)->GetOwner()->room_number = 5; // Room 5
                }
                else if ((it_pos->getPosition().x >= JSONREADER->getWall5Pos().x) && (it_pos->getPosition().x < JSONREADER->getWall7Pos().x))
                {
                    (*it)->GetOwner()->room_number = 8; // Room 8
                }
            }
            if (it_pos->getPosition().y > JSONREADER->getWall1Pos().y)
            {
                if (it_pos->getPosition().x <= JSONREADER->getWall6Pos().x)
                {
                    (*it)->GetOwner()->room_number = 3; // Room 3
                }
                else if ((it_pos->getPosition().x >= JSONREADER->getWall6Pos().x) && (it_pos->getPosition().x < JSONREADER->getWall5Pos().x))
                {
                    (*it)->GetOwner()->room_number = 4; // Room 4
                }
                else if ((it_pos->getPosition().x >= JSONREADER->getWall5Pos().x) && (it_pos->getPosition().x < JSONREADER->getWall7Pos().x))
                {
                    (*it)->GetOwner()->room_number = 9; // Room 9
                }
            }
        }
    }
}