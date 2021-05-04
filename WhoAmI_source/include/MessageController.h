/**
\file        MessageController.h
\author      Chiho Kwon
\par         email: erpo0811@gmail.com
\par         course: GAM200
\date        12/15/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/


#pragma once

#ifndef MESSAGE_CONTROLLER_H_
#define MESSAGE_CONTROLLER_H_

#include "Application.h"
#include "ComponentType.h"
#include "Controller.hpp"
#include "Input.h"
#include "LTimer.hpp"
#include "Timer.hpp"
#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace FindersEngine
{
    class Transform;

    class MessageController : public Controller
    {
    public:
        MessageController();
        ~MessageController();

        void Init() override;
        void Update(float deltaTime) override;

        void ControllAlpha(Object* object, float distance);

        Transform* transform; // position, scale, rotation

    private:
        Collision* collision;
        Hud* hud;
    };
}

#endif // !PLAYER_CONTROLLER_H_
