/**
\file        ObjectFactory.cpp
\author      SeongHyun Hong
\par         email: tjdgus3174@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "ObjectFactory.h"
#include <cassert>

#include "ButtonController.h"
#include "Graphics.h"
#include "Headers_Components.h"
#include "Headers_Controllers.h" //PlayerController, ZombieController
#include "HudController.h"
#include "Object.h"
#include "Texture.h"
#include "Transform.hpp"
#include <glm/glm.hpp>

#include <algorithm>
#include <time.h>

#define WIDTH 1280
#define HEIGHT 640

namespace FindersEngine
{
    ObjectFactory* OBJECT_FACTORY = nullptr;

    ObjectFactory::ObjectFactory()
    {

        assert(OBJECT_FACTORY == nullptr && "Factory already created! Only can create one.");
        OBJECT_FACTORY = this;
        last_objectID = 1; // There is over 4 billion numbers
        AICount = 0;
        check = 0;
    }

    ObjectFactory::~ObjectFactory()
    {
        DestroyAllObjects();
    }

    void ObjectFactory::Update(float deltaTime)
    {
        //Delete all objects in the ObjectToBeDeleted list
        for (auto object : ObjectsToBeDeleted)
        {
            if (object == nullptr)
                continue;

            auto delete_objID = ObjectIDMap.find(object->objectID);

            //assert(delete_objID != ObjectIDMap.end() && "Object is bad memory.");
            if (delete_objID != ObjectIDMap.end())
            {
                //delete and remove from the map
                delete object;
                ObjectIDMap.erase(delete_objID);
            }
        }
        ObjectsToBeDeleted.clear();
    }

    void ObjectFactory::Destroy(Object* gameObject)
    {
        ObjectsToBeDeleted.push_back(gameObject);
    }

    void ObjectFactory::IDGameObject(Object* gameObject, ObjectID id)
    {
        //Just increment the last_objectID used. Does not handle overflow
        //but it would take over 4 billion objects to break
        //++last_objectID;
        gameObject->objectID = id;

        //Store the game object in the ObjectIDMap
        ObjectIDMap[id] = gameObject;
    }

    Object* ObjectFactory::GetObjectID(ObjectID id)
    {
        std::map<ObjectID, Object*>::iterator iter = ObjectIDMap.find(id);
        if (iter != ObjectIDMap.end())
            return iter->second;

        return nullptr;
    }
    ObjectID ObjectFactory::FindObjectID(Object* gameObject)
    {
        unsigned objectID = 0;
        std::find_if(ObjectIDMap.begin(), ObjectIDMap.end(), [&](const std::pair<ObjectID, Object*>& it) -> bool {
            if (it.second->GetObjType() == OT_BULLET)
            {
                //Object* obj = it.second;
                objectID = it.first;

                ++objectID;
            }
            return false;
        });
        return objectID;
    }

    Object* ObjectFactory::CreateEmptyObject(ObjectID id)
    {
        Object* gameObject = new Object();
        IDGameObject(gameObject, id);

        return gameObject;
    }

    int ObjectFactory::CountObjectType(ObjectType objType)
    {
        int count = 0;

        for (auto iter = ObjectIDMap.begin(); iter != ObjectIDMap.end(); ++iter)
        {
            if ((*iter).second->GetObjType() == objType)
            {
                count++;
            }
        }
        return count;
    }
    void ObjectFactory::DestroyAllObjects()
    {
        for (auto iter : ObjectIDMap)
            delete iter.second;

        ObjectIDMap.clear();
        last_objectID = 1;
    }
}