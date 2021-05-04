/**
\file        ButtonLogicController.h
\author      Sehyun Kim
\par         email: kim4969\@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/


#pragma once

#ifndef BUTTON_LOGIC_CONTROLLER_H_
#define BUTTON_LOGIC_CONTROLLER_H_

#include "ComponentType.h"
#include "Controller.hpp"
#include <glm/glm.hpp>

namespace FindersEngine
{
    class ButtonLogicController : public Controller
    {
    public:
        ButtonLogicController();
        ~ButtonLogicController();

        void Init() override;
        void Update(float deltaTime) override;

    private:
        Transform* transform; // position, scale, rotation
        Collision* collision;
        Hud* hud;
    };
}

#endif // !PLAYER_CONTROLLER_H_
