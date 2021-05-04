/**
\file        ObjectFactory.h
\author      SeongHyun Hong
\par         email: tjdgus3174@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once

#ifndef OBJECT_FACTORY_H_
#define OBJECT_FACTORY_H_

#include "ObjectType.h"
#include "System.h"
#include <glm/glm.hpp>
#include <map>
#include <vector>

#include "Headers_Textures.h"
#include <memory>

namespace FindersEngine
{
    class Object;
    using ObjectID = unsigned;

    class ObjectFactory : public System
    {
    public:
        ObjectFactory();
        ~ObjectFactory();

        void Init() override {} //nothig...
        void Update(float deltaTime) override;

        //Add an object to the destroy list for delay destruction
        void Destroy(Object* gameObject);

        //ID the object and store it in the object list(map)
        void IDGameObject(Object* gameObject, ObjectID id);

        //Return an object with specific ID
        Object* GetObjectID(ObjectID id);

        ObjectID FindObjectID(Object* gameObject);

        Object* CreateEmptyObject(ObjectID id);

        int CountObjectType(ObjectType objType);

        //For the shutdown of the ObjectFactory
        void DestroyAllObjects();

    private:
        //Used to incrementally generate unique IDs
        ObjectID last_objectID;

        //Map of Object to their IDs used for safe referencing
        std::map<ObjectID, Object*> ObjectIDMap;
        //List of objects to be deleted
        //To prevent problems of early or multi call of Object's destruction
        std::vector<Object*> ObjectsToBeDeleted;

        int AICount;
        int check;
    };

    extern ObjectFactory* OBJECT_FACTORY;
};

#endif // !OBJECT_FACTORY_H_
