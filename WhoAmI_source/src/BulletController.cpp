/**
\file        BulletController.cpp
\author      jungdae.chur
\par         email: wmdhwmdh@gmail.com
\par         course: GAM200
\date        12/13/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once
#include "BulletController.h"
#include "ObjectFactory.h"
#include "Transform.hpp"

namespace FindersEngine
{
    BulletController::BulletController()
    {
    }
    BulletController::~BulletController()
    {
    }
    void BulletController::Init()
    {
        lifeTime = 0.05f;
    }
    void BulletController::Update(float deltaTime)
    {
        lifeTime -= deltaTime;
        if (lifeTime < 0.0f)
        {
            OBJECT_FACTORY->Destroy(GetOwner());
        }
    }
}