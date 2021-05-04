/**
\file        SplashController.h
\author      jungdae.chur
\par         email: wmdhwmdh@gmail.com
\par         course: GAM200
\date        12/13/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/


#pragma once

#ifndef SPLASH_CONTROLLER_H_
#define SPLASH_CONTROLLER_H_

#include "Application.h"
#include "ComponentType.h"
#include "Controller.hpp"
#include "Input.h"
#include <glm/glm.hpp>

namespace FindersEngine
{

    class SplashController : public Controller
    {
    public:
        SplashController();
        ~SplashController();

        void Init() override;
        void Update(float deltaTime) override;

    private:
        friend class Sprite;
        Sprite* sprite;
    };
};

#endif