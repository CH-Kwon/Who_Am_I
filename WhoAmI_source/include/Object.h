/**
\file        Object.h
\author      SeongHyun Hong
\par         email: tjdgus3174@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once

#ifndef OBJECT_H_
#define OBJECT_H_

#include "ComponentType.h"
#include "ObjectFactory.h"
#include "ObjectType.h"
#include "Transform.hpp"
#include <unordered_map>
/*
Notice:

We will change Object and Component how to manage
is using Mask/Fragment-bits

ex)order: None, None, transform, sprite ,, camera, rigidbody, boxcollision, controller
			0011 0101
	None(empty)
	None(empty)
	transform(exist)
	sprite(exist)		:	transform(dependency)
	
	camera(empty)		:	transform(dependency)
	rigidbody(exist)	:	transform(dependency)
	boxcollision(empty)	:	transform(dependency)
	controller(exist)	

Or, Hash-Map(key-value)
*/

namespace FindersEngine
{
    using ObjectID = unsigned;

    class ObjectFactory;
    class Component;

    class Object
    {
    public:
        friend class ObjectFactory;

        Object();
        ~Object();

        void Init();

        //Properly destroy the object by delay destruction
        void Destroy(Object* obj);

        bool AddComponent(Component* pComponent);
        Component* GetComponent(ComponentType cType);

        ObjectID GetObjectID()
        {
            return objectID;
        }
        void SetObjID(ObjectID m_objID)
        {
            objectID = m_objID;
        }
        ShapeType GetShapeType()
        {
            return shapetype;
        }

        void SetShapeType(ShapeType shapetype_)
        {
            shapetype = shapetype_;
        }

        ObjectType GetObjType() const
        {
            return objtype;
        }

        void SetObjType(ObjectType objtype_)
        {
            objtype = objtype_;
        }
        bool is_get_pistol;
        unsigned curr_ammo;
        bool destroyF;
        unsigned curr_Health;
        unsigned curr_Armor;
        bool is_in_Final;
        int player_health;
        bool is_collide;
        int room_number;
        bool is_attack;
        bool is_getdamage;
        glm::vec3 GetPosition(void)
        {
            return ct_transform->getPosition();
        }
        glm::vec3 GetScale(void)
        {
            return ct_transform->getScale();
        }
        void SetPosition(float x, float y)
        {
            return ct_transform->setPosition(glm::vec3(x, y, 0));
        }
        void SetScale_x(float x)
        {
            glm::vec3 scale = ct_transform->getScale();
            return ct_transform->setScale(glm::vec3(x, scale.y, 0));
        }
        void SetScale_y(float y)
        {
            glm::vec3 scale = ct_transform->getScale();
            return ct_transform->setScale(glm::vec3(scale.x, y, 0));
        }
        void SetRotation(float r)
        {
            glm::vec3 rot = ct_transform->getRotation();
            return ct_transform->setRotation(glm::vec3(rot.x, rot.y, r));
        }

    private:
        Transform* ct_transform;

        Sprite* ct_sprite;
        Camera* ct_camera;

        RigidBody* ct_rigidbody;
        Collision* ct_collision;

        Controller* ct_controller;
        Hud* ct_hud;
        SpriteText* ct_spritetext;

        ObjectID objectID;
        ObjectType objtype;
        ShapeType shapetype;
    };
}


#endif // !OBJECT_H_
