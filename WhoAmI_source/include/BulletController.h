/**
\file        BulletController.h
\author      jungdae.chur
\par         email: wmdhwmdh@gmail.com
\par         course: GAM200
\date        12/13/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/


#pragma once

#ifndef BULLET_CONTROLLER_H_
#define BULLET_CONTROLLER_H_

#include "ComponentType.h"
#include "Controller.hpp"


namespace FindersEngine
{

    class BulletController : public Controller
    {
    public:
        BulletController();
        ~BulletController();

        void Init() override;
        void Update(float deltaTime) override;

    private:
        float lifeTime;
    };
}

#endif // !BULLET_CONTROLLER_H_
