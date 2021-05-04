/**
\file        Component.hpp
\author      SeongHyun Hong
\par         email: tjdgus3174@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "ComponentType.h"

namespace FindersEngine
{
    class Object;

    class Component
    {
    public:
        Component(ComponentType type) : cType(type) {}
        virtual ~Component() {}
        virtual void Init(){};
        void SetOwner(Object* owner) { pOwner = owner; }
        Object* GetOwner() { return pOwner; }
        ComponentType GetType() { return cType; }

    private:
        friend class Object;
        Component() = delete;
        Object* pOwner = nullptr;
        ComponentType cType;
    };
};

#endif // !COMPONENT_H_
