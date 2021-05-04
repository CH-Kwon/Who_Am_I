/**
\file        Physics.cpp
\author      jungdae.chur
\par         email: wmdhwmdh@gmail.com
\par         course: GAM200
\date        12/13/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "Physics.h"

//include RigidBody, Transform, BoxCollision and so on...
#include "Headers_Components.h"

//for debugging
#include "DebugUtil.h"
#include "PhysicsLogic.h"
#include <cassert>
#include <iostream>

//using glm::vec3/glm::mat44 instead of before Vector3/Matrix44 class
#include "Object.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
//
#include "Input.h"
#include "PlayerController.h"
#include "PlayerLogic.h"
#include "Transform.hpp"

//
#ifdef _WIN32
#include "../../WhoAmI/Include/PlayerLogic.h"
#else //apple
#include "PlayerLogic.h"
#endif
namespace FindersEngine
{
    class Pair
    {
    public:
        Pair(RigidBody* lhs, RigidBody* rhs)
            : m_lhs(lhs), m_rhs(rhs)
        {
        }

        RigidBody* m_lhs;
        RigidBody* m_rhs;

    private:
    };

    Physics* PHYSICS = nullptr;
    Physics::Physics()
    {
        assert(PHYSICS == nullptr && "PHYSICS system is already existing!");
        PHYSICS = this;
        m_collision = new Collision();
    }

    Physics::~Physics()
    {
        delete m_collision;
        m_collision = 0;
    }

    void Physics::Init()
    {
    }

    void Physics::Update(float deltaTime)
    {
        PHYSICS_LOGIC->SeperateByRoom();
        ExplicitEuler(deltaTime);
        AbleToCollide();
    }

    void Physics::push_back_RigidBody(RigidBody* rigidbody)
    {
        PHYSICS->m_vecprb.push_back(rigidbody);
    }

    void Physics::ExplicitEuler(float deltaTime)
    {
        Transform* pTr = nullptr;
        //current frame position, next frame position
        glm::vec3 curfp;
        for (std::vector<RigidBody*>::iterator iter = m_vecprb.begin(); iter != m_vecprb.end(); ++iter)
        {
            //Explicit Euler method
            //f(t + dt) = f(t) + f'(t)dt
            //next frame's position = current frame's posotion + (vector * dt)
            pTr = dynamic_cast<Transform*>((*iter)->GetOwner()->GetComponent(CT_TRANSFORM));
            curfp = pTr->getPosition();

            //p' = p + vt
            pTr->setPosition(curfp + (*iter)->pm_vel * deltaTime);

            if ((*iter)->GetOwner()->GetObjType() == OT_BULLET)
            {
                (*iter)->pm_vel = (*iter)->pm_vel * 0.97f + ((*iter)->pm_force * (*iter)->pm_invMass) * deltaTime;
            }
            else
                (*iter)->pm_vel = (*iter)->pm_vel * 0.8f + ((*iter)->pm_force * (*iter)->pm_invMass) * deltaTime;
            //v' = v + at = v + F/m * at

            (*iter)->pm_force = glm::vec3(0.f); //Set Zero
        }
    }

    void Physics::AbleToCollide()
    {
        //k; number of objects
        //Big O Notation(n^2 / 2)
        //(*i) = RigidBody*
        //i = RigidBody**
        for (std::vector<RigidBody*>::iterator i = m_vecprb.begin();
             i != m_vecprb.end(); ++i)
        {
            for (std::vector<RigidBody*>::iterator j = i + 1;
                 j != m_vecprb.end(); ++j)
            {
                ShapeType i_shape = (*i)->m_pTransform->GetOwner()->GetShapeType();
                ShapeType j_shape = (*j)->m_pTransform->GetOwner()->GetShapeType();

                if (i_shape == ST_CIRCLE && j_shape == ST_CIRCLE)
                {
                    if (m_collision->CircleCircleCollisionCheck((*i)->GetOwner(), (*j)->GetOwner()))
                    {
                        m_rigidbody->ResolveIntersection((*i), (*j));
                        m_rigidbody->CollisionResponseGeneral((*i), (*j));
                    }
                }
                else if (i_shape == ST_CIRCLE && j_shape == ST_RECTANGLE)
                {
                    if (m_collision->CircleRectCollisionCheck((*i)->GetOwner(), (*j)->GetOwner()))
                    {
                        if ((*j)->GetOwner()->GetObjType() == OT_HDOOR || (*j)->GetOwner()->GetObjType() == OT_VDOOR)
                        {
                            m_rigidbody->CollisionResponseWithDoor((*i), (*j));
                            if ((*i)->GetOwner()->GetObjType() == OT_PLAYER)
                                m_rigidbody->GenerateActionHint();
                        }
                        else if ((*j)->GetOwner()->GetObjType() == OT_FDOOR)
                        {
                            m_rigidbody->CollisionResponseWithFinal((*i));
                            if ((*i)->GetOwner()->GetObjType() == OT_PLAYER)
                            {
                                m_rigidbody->GenerateActionHint();
                            }
                        }
                        else
                            m_rigidbody->CollisionResponseWithWall((*i), (*j));
                    }
                    m_rigidbody->RemoveActionHint();
                }
                else if (j_shape == ST_CIRCLE && i_shape == ST_RECTANGLE)
                {
                    if (m_collision->CircleRectCollisionCheck((*i)->GetOwner(), (*j)->GetOwner()))
                    {
                        if ((*i)->GetOwner()->GetObjType() == OT_HDOOR || (*i)->GetOwner()->GetObjType() == OT_VDOOR)
                        {
                            m_rigidbody->CollisionResponseWithDoor((*i), (*j));
                            if ((*j)->GetOwner()->GetObjType() == OT_PLAYER)
                                m_rigidbody->GenerateActionHint();
                        }
                        else if ((*i)->GetOwner()->GetObjType() == OT_FDOOR)
                        {
                            m_rigidbody->CollisionResponseWithFinal((*j));
                            if ((*j)->GetOwner()->GetObjType() == OT_PLAYER)
                                m_rigidbody->GenerateActionHint();
                        }
                        else
                            m_rigidbody->CollisionResponseWithWall((*j), (*i));
                    }
                    m_rigidbody->RemoveActionHint();
                }
                //put the pair into the container
                m_vecpair.push_back(Pair(*i, *j));
            }
        }
    }
};
