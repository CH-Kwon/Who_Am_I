/**
\file        EyeController.h
\author      Chiho Kwon
\par         email: erpo0811@gmail.com
\par         course: GAM200
\date        12/15/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once

#ifndef EYE_CONTROLLER_H_
#define EYE_CONTROLLER_H_

#include "Application.h"
#include "ComponentType.h"
#include "Controller.hpp"
#include "Input.h"
#include <glm/glm.hpp>

namespace FindersEngine
{
    class Transform;

    class EyeController : public Controller
    {
    public:
        EyeController();
        ~EyeController();

        void Init() override;
        void Update(float deltaTime) override;

        glm::vec2 target_direction;

        Transform* transform; // position, scale, rotation
        void mouse_rotation(Transform* eye);

    private:
        Collision* collision;
        Hud* hud;
    };
}

#endif // !PLAYER_CONTROLLER_H_
