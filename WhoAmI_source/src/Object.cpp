/**
\file        Object.cpp
\author      SeongHyun Hong
\par         email: tjdgus3174@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "Object.h"
#include "Headers_Components.h"
#include "ObjectFactory.h"

namespace FindersEngine
{
    Object::Object()
    {
        //Todo : add more components
        //Set all components' pointers to null
        ct_transform = nullptr;
        objectID = 0;
        objtype = OT_NONE;
        shapetype = ST_NONE;
        ct_sprite = nullptr;
        ct_camera = nullptr;
        ct_rigidbody = nullptr;
        ct_hud = nullptr;
        ct_collision = nullptr;
        ct_controller = nullptr;
        ct_spritetext = nullptr;
        room_number = 1;
        is_getdamage = false;
    }

    Object::~Object()
    {
        //Todo : delete all components
        if (ct_transform)
            delete ct_transform;
        if (ct_hud)
            delete ct_hud;
        if (ct_sprite)
            delete ct_sprite;
        if (ct_camera)
            delete ct_camera;

        if (ct_rigidbody)
            delete ct_rigidbody;
        if (ct_collision)
            delete ct_collision;
        if (ct_controller)
            delete ct_controller;
        if (ct_spritetext)
            delete ct_spritetext;
    }

    void Object::Init()
    {
        //Todo: Initialize all components
        if (ct_transform)
            ct_transform->Init();
        if (ct_hud)
            ct_hud->Init();
        if (ct_sprite)
            ct_sprite->Init();
        if (ct_spritetext)
            ct_spritetext->Init();
        if (ct_camera)
            ct_camera->Init();

        if (ct_rigidbody)
            ct_rigidbody->Init();
        if (ct_collision)
            ct_collision->Init();
        if (ct_controller)
            ct_controller->Init();
    }

    void Object::Destroy(Object* obj)
    {
        //Signal the object factory for delay destruction...
        OBJECT_FACTORY->Destroy(obj);
    }

    bool Object::AddComponent(Component* pComponent)
    {
        //All component and return true if success
        if (pComponent->GetType() > CT_INVALID && pComponent->GetType() < CT_COUNT)
            pComponent->SetOwner(this);
        switch (pComponent->GetType())
        {
            case CT_TRANSFORM:
                ct_transform = dynamic_cast<Transform*>(pComponent);
                return true;
            case CT_SPRITE:
                ct_sprite = dynamic_cast<Sprite*>(pComponent);
                return true;
            case CT_SPRITE_TEXT:
                ct_spritetext = dynamic_cast<SpriteText*>(pComponent);
                return true;
            case CT_CAMERA:
                ct_camera = dynamic_cast<Camera*>(pComponent);
                return true;
            case CT_RIGID_BODY:
                ct_rigidbody = dynamic_cast<RigidBody*>(pComponent);
                return true;
            case CT_COLLISION:
                ct_collision = dynamic_cast<Collision*>(pComponent);
                return true;
            case CT_HUD:
                ct_hud = dynamic_cast<Hud*>(pComponent);
                return true;
            case CT_CONTROLLER:
                ct_controller = dynamic_cast<Controller*>(pComponent);
                return true;

            default: // Only working in debug mode
                assert(!"Allocating an unknown component in AddComponent!");
                break;
        }

        return false; //if failed
    }

    Component* Object::GetComponent(ComponentType cType)
    {
        switch (cType)
        {
            case CT_TRANSFORM:
                return ct_transform;
            case CT_SPRITE_TEXT:
                return ct_spritetext;
            case CT_SPRITE:
                return ct_controller;
            case CT_CAMERA:
                return ct_camera;
            case CT_RIGID_BODY:
                return ct_rigidbody;
            case CT_COLLISION:
                return ct_collision;
            case CT_CONTROLLER:
                return ct_controller;
            case CT_HUD:
                return ct_hud;
            default:
                assert(!"Getting an unknown component in GetComponent!");
                break;
        }
        return nullptr; //For release mode...
    }
};
