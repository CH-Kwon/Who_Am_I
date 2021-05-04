/**
\file        RigidBody.cpp
\author      jungdae.chur
\par         email: wmdhwmdh@gmail.com
\par         course: GAM200
\date        12/13/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "RigidBody.h"
#include "Application.h"
#include "ButtonController.h"
#include "Engine.h"
#include "Graphics.h"
#include "Input.h"
#include "Object.h"
#include "ObjectGenerator.h"
#include "Physics.h"
#include "SoundManager.h"
#include "Transform.hpp"
#include <iostream>
#define AMMO 6;
#define ARMOR 50;

namespace FindersEngine
{
    const float width = 800.f;
    const float height = 800.f;
    Object* PressF_Hint = nullptr;
    bool already_exist = false;

    RigidBody::RigidBody(glm::vec3 vel, float invmass)
        : Component(CT_RIGID_BODY), pm_vel(vel), pm_invMass(invmass)
    {
        PHYSICS->m_vecprb.push_back(this);
    }

    RigidBody::~RigidBody()
    {
        PHYSICS->m_vecprb.erase(std::find(PHYSICS->m_vecprb.begin(), PHYSICS->m_vecprb.end(), this));
    }

    void RigidBody::Init()
    {
        already_exist = false;
        PressF_Hint = nullptr;
        pm_force = glm::vec3(0.f, 0.f, 0.f);
        m_pTransform = dynamic_cast<Transform*>(GetOwner()->GetComponent(CT_TRANSFORM));
    }
    // Resolving intersection when collision occured (Circle-Circle)
    void RigidBody::ResolveIntersection(RigidBody* pA, RigidBody* pB)
    {
        if ((pA->GetOwner()->GetObjType() != OT_AMMO && pB->GetOwner()->GetObjType() != OT_AMMO) && (pA->GetOwner()->GetObjType() != OT_PISTOL && pB->GetOwner()->GetObjType() != OT_PISTOL))
        {
            Transform* a_pTransform = static_cast<Transform*>(pA->GetOwner()->GetComponent(CT_TRANSFORM));
            Transform* b_pTransform = static_cast<Transform*>(pB->GetOwner()->GetComponent(CT_TRANSFORM));

            glm::vec2 asize = a_pTransform->getScale();
            glm::vec2 bsize = b_pTransform->getScale();

            glm::vec3 apos = glm::vec3(a_pTransform->getPosition().x * width, a_pTransform->getPosition().y * height, 0.f);
            glm::vec3 bpos = glm::vec3(b_pTransform->getPosition().x * width, b_pTransform->getPosition().y * height, 0.f);

            glm::vec2 minimumVec = ((asize / 2.f) + (bsize / 2.f)); // Collide position
            float minimumLength = glm::length(minimumVec);

            float dist = glm::length(apos - bpos);
            glm::vec3 normalVec = glm::normalize(apos - bpos);

            float penetration = minimumLength - dist;
            // Resolve intersection
            const float perecent = 0.2f;
            const float slope = 0.01f;
            glm::vec3 correction = Max(penetration - slope, 0.f) * perecent * normalVec;
            a_pTransform->position += correction / 100.f;
            b_pTransform->position -= correction / 100.f;
        }
    }
    // General response of collision
    void RigidBody::CollisionResponseGeneral(RigidBody* pA, RigidBody* pB)
    {
        // only if Both of RigidBody is Circle
        if (pA->GetOwner()->GetObjType() == OT_PLAYER)
        {
            glm::vec3 aVel_direction = glm::normalize(pA->pm_vel);
            glm::vec3 bVel_direction = glm::normalize(pB->pm_vel);
            pA->pm_vel = glm::vec3(0.f, 0.f, 0.f);

            if ((pB->GetOwner()->GetObjType() == OT_ZOMBIE) && (pB->GetOwner()->is_attack == false))
            {
                if (pB->pm_vel == glm::vec3(0.f, 0.f, 0.f))
                {
                    pA->pm_vel = glm::vec3(0.f, 0.f, 0.f);
                    pA->pm_vel = -(aVel_direction * 2.5f);
                    pB->GetOwner()->is_attack = true;
                }
                else if (pA->pm_vel == glm::vec3(0.f, 0.f, 0.f))
                {
                    pA->pm_vel = glm::vec3(0.f, 0.f, 0.f);
                    pA->pm_vel = (bVel_direction * 2.5f);
                    pB->GetOwner()->is_attack = true;
                }
                else if ((pA->pm_vel != glm::vec3(0.f, 0.f, 0.f)) && (pB->pm_vel != glm::vec3(0.f, 0.f, 0.f)))
                {
                    pA->pm_vel = glm::vec3(0.f, 0.f, 0.f);
                    pA->pm_vel = -(bVel_direction * 2.5f);
                    pB->GetOwner()->is_attack = true;
                }
            }
            // Pistol Item
            if (pB->GetOwner()->GetObjType() == OT_PISTOL)
            {
                SOUNDMANAGER->play("GETITEM_SOUND.wav");
                pA->GetOwner()->is_get_pistol = true;
                if (pA->GetOwner()->is_get_pistol)
                    pB->GetOwner()->Destroy(pB->GetOwner());
            }
            // Ammo Item
            if (pB->GetOwner()->GetObjType() == OT_AMMO)
            {
                SOUNDMANAGER->play("GETITEM_SOUND.wav");
                pA->GetOwner()->curr_ammo += AMMO;
                if (pA->GetOwner()->curr_ammo >= 30)
                    pA->GetOwner()->curr_ammo = 30;
                pB->GetOwner()->Destroy(pB->GetOwner());
            }
            // Armor Item. It will be used next semester
            if (pB->GetOwner()->GetObjType() == OT_ARMOR)
            {
                pA->GetOwner()->curr_Armor += ARMOR;
                pB->GetOwner()->Destroy(pB->GetOwner());
            }
        }
    }
    // Response when Zombies hit by bullet
    void RigidBody::CollisionResponseWithBullet(RigidBody* pA, RigidBody* pB)
    {
        glm::vec3 direction = pA->m_pTransform->getPosition() * width - pB->m_pTransform->getPosition() * height;
        glm::vec3 unit_direction = glm::normalize(direction);

        pB->pm_vel = -(unit_direction * 2.5f);
    }
    // When player get to the last door
    void RigidBody::CollisionResponseWithFinal(RigidBody* pA)
    {
        if (Input::GetInstance().IsPressed(SDL_SCANCODE_F) || Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_X))
        {
            pA->GetOwner()->is_in_Final = true;
        }
    }
    // Collision response with wall
    void RigidBody::CollisionResponseWithWall(RigidBody* pA, RigidBody* pB)
    {
        // A is Circle
        glm::vec2 a_radius = pA->m_pTransform->getScale();
        glm::vec2 b_rect_size = pB->m_pTransform->getScale();

        glm::vec3 a_circle_pos = glm::vec3(pA->m_pTransform->getPosition().x * width, pA->m_pTransform->getPosition().y * height, 0.f);
        glm::vec3 b_rect_pos = glm::vec3(pB->m_pTransform->getPosition().x * width, pB->m_pTransform->getPosition().y * height, 0.f);

        glm::vec3 a_distance = glm::vec3(0.f, 0.f, 0.f);
        a_distance.x = fabs(b_rect_pos.x - a_circle_pos.x);
        a_distance.y = fabs(b_rect_pos.y - a_circle_pos.y);
        glm::vec3 normalVec = glm::normalize(a_distance);

        glm::vec3 btr, bbl, btl, bbr;
        btl = glm::vec3(b_rect_pos.x - b_rect_size.x * 0.5f, b_rect_pos.y + b_rect_size.y * 0.5f, 0.f);
        bbr = glm::vec3(b_rect_pos.x + b_rect_size.x * 0.5f, b_rect_pos.y - b_rect_size.y * 0.5f, 0.f);
        bbl = glm::vec3(b_rect_pos.x - b_rect_size.x * 0.5f, b_rect_pos.y - b_rect_size.y * 0.5f, 0.f);
        btr = glm::vec3(b_rect_pos.x + b_rect_size.x * 0.5f, b_rect_pos.y + b_rect_size.y * 0.5f, 0.f);

        // Resolve intersection with rectangle
        float offset_x = (a_distance.x - ((b_rect_size.x * 0.5f) + (a_radius.x * 0.5f)));
        float offset_y = (a_distance.y - ((b_rect_size.y * 0.5f) + (a_radius.y * 0.5f)));

        const float perecent = 0.3f;

        if ((a_circle_pos.x < btl.x) && (a_circle_pos.y < btl.y) && (a_circle_pos.y > bbl.y)) // left case
        {
            glm::vec3 a_pos = pA->m_pTransform->getPosition();
            a_pos.x += (offset_x * perecent * normalVec.x * 0.1f);
            pA->m_pTransform->setPosition(a_pos);
        }

        if ((a_circle_pos.x > btr.x) && (a_circle_pos.y < btl.y) && (a_circle_pos.y > bbl.y)) // right case
        {
            glm::vec3 a_pos = pA->m_pTransform->getPosition();
            a_pos.x -= (offset_x * perecent * normalVec.x * 0.1f);
            pA->m_pTransform->setPosition(a_pos);
        }

        if ((a_circle_pos.y < bbl.y) && (a_circle_pos.x > btl.x) && (a_circle_pos.x < bbr.x)) // Down case
        {
            glm::vec3 a_pos = pA->m_pTransform->getPosition();
            a_pos.y += (offset_y * perecent * normalVec.y * 0.1f);
            pA->m_pTransform->setPosition(a_pos);
        }

        if ((a_circle_pos.y > btr.y) && (a_circle_pos.x > btl.x) && (a_circle_pos.x < bbr.x)) // Up case
        {
            glm::vec3 a_pos = pA->m_pTransform->getPosition();
            a_pos.y -= (offset_y * perecent * normalVec.y * 0.1f);
            pA->m_pTransform->setPosition(a_pos);
        }
        /*if ((a_circle_pos.x < btl.x) && (a_circle_pos.y < btl.y) && (a_circle_pos.y > bbl.y)) // left case
        {
            glm::vec3 a_pos = pA->m_pTransform->getPosition();
            a_pos.x += (offset_x * perecent * normalVec.x * 0.1f);
            pA->m_pTransform->setPosition(a_pos);
        }

        if ((a_circle_pos.x > btr.x) && (a_circle_pos.y < btl.y) && (a_circle_pos.y > bbl.y)) // right case
        {
            glm::vec3 a_pos = pA->m_pTransform->getPosition();
            a_pos.x -= (offset_x * perecent * normalVec.x * 0.1f);
            pA->m_pTransform->setPosition(a_pos);
        }

        if ((a_circle_pos.y < bbl.y) && (a_circle_pos.x > btl.x) && (a_circle_pos.x < bbr.x)) // Down case
        {
            glm::vec3 a_pos = pA->m_pTransform->getPosition();
            a_pos.y += (offset_y * perecent * normalVec.y * 0.1f);
            pA->m_pTransform->setPosition(a_pos);
        }

        if ((a_circle_pos.y > btr.y) && (a_circle_pos.x > btl.x) && (a_circle_pos.x < bbr.x)) // Up case
        {
            glm::vec3 a_pos = pA->m_pTransform->getPosition();
            a_pos.y -= (offset_y * perecent * normalVec.y * 0.1f);
            pA->m_pTransform->setPosition(a_pos);
        }*/
    }
    // Response when player get to the normal door
    void RigidBody::CollisionResponseWithDoor(RigidBody* pA, RigidBody* pB)
    {
        glm::vec3 player_pos = pA->m_pTransform->getPosition();
        glm::vec3 door_pos = pB->m_pTransform->getPosition();

        if (Input::GetInstance().IsPressed(SDL_SCANCODE_F) || Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_X))
        {
            //Two types of door
            if (pB->GetOwner()->GetObjType() == OT_VDOOR && pA->GetOwner()->GetObjType() == OT_PLAYER)
            {
                SOUNDMANAGER->play("DOOR_OPEN_SOUND.mp3");
                if (player_pos.x > door_pos.x)
                {
                    glm::vec3 a_pos = pA->m_pTransform->getPosition();
                    a_pos.x = door_pos.x - 0.22f;
                    pA->m_pTransform->setPosition(a_pos);
                }
                else if (player_pos.x < door_pos.x)
                {
                    glm::vec3 a_pos = pA->m_pTransform->getPosition();
                    a_pos.x = door_pos.x + 0.22f;
                    pA->m_pTransform->setPosition(a_pos);
                }
            }
            else if (pB->GetOwner()->GetObjType() == OT_HDOOR && pA->GetOwner()->GetObjType() == OT_PLAYER)
            {
                SOUNDMANAGER->play("DOOR_OPEN_SOUND.mp3");
                if (player_pos.y > door_pos.y)
                {
                    glm::vec3 a_pos = pA->m_pTransform->getPosition();
                    a_pos.y = door_pos.y - 0.22f;
                    pA->m_pTransform->setPosition(a_pos);
                }
                else if (player_pos.y < door_pos.y)
                {
                    glm::vec3 a_pos = pA->m_pTransform->getPosition();
                    a_pos.y = door_pos.y + 0.22f;
                    pA->m_pTransform->setPosition(a_pos);
                }
            }
        }
    }
    // Generate Font 'Press (Action key)'
    void RigidBody::GenerateActionHint()
    {
        if (already_exist == false)
        {
            if (!APPLICATION->isUsingGamepad)
                PressF_Hint = OBJECT_GEN->CreateAFont(glm::vec3(width / 2.f + 200.f, height / 2.f - 100.f, 0.f), 0.45f, "Press F", glm::vec3(0.9f, 0.7f, 0.0f), 2222, 0.f);
            else if (APPLICATION->isUsingGamepad)
                PressF_Hint = OBJECT_GEN->CreateAFont(glm::vec3(width / 2.f + 200.f, height / 2.f - 100.f, 0.f), 0.45f, "Press X", glm::vec3(0.9f, 0.7f, 0.0f), 2222, 0.f);
            already_exist = true;
        }
    }
    // Remove Font 'Press (Action key)'
    void RigidBody::RemoveActionHint()
    {
        if (already_exist)
        {
            OBJECT_FACTORY->Destroy(PressF_Hint);
            already_exist = false;
        }
    }
}
