/**
\file        EyeController.cpp
\author      Chiho Kwon
\par         email: erpo0811@gmail.com
\par         course: GAM200
\date        12/15/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "EyeController.h"
#include "CameraSystem.h"
#include "Collision.h"
#include "Graphics.h"
#include "Hud.h"
#include "Input.h"
#include "Object.h"
#include "ObjectFactory.h"
#include "RigidBody.h"
#include "Transform.hpp"
#include "imgui.h"
#include "imgui_impl_sdl_gl3.h"
#include <iostream>

#include <iostream>
#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

namespace FindersEngine
{
    namespace
    {
        glm::vec4 COLOR_WHITE(1.0f, 1.0f, 1.0f, 1.0f);
        glm::vec4 red(1.0f, 0.0f, 0.0f, 1.0f);
        glm::vec4 blue(0.0f, 0.0f, 1.0f, 1.0f);
    };


    EyeController::EyeController()
    {
    }

    EyeController::~EyeController()
    {
    }

    void EyeController::Init()
    {
        transform = dynamic_cast<Transform*>(GetOwner()->GetComponent(CT_TRANSFORM));
        hud = dynamic_cast<Hud*>(GetOwner()->GetComponent(CT_HUD));

        hud->RGBA_Color(red);
    }

    void EyeController::Update(float deltaTime)
    {
        mouse_rotation(transform);
        if (Input::GetInstance().IsTriggered(SDL_SCANCODE_C))
        {
            hud->RGBA_Color(blue);
        }
        else if (Input::GetInstance().IsTriggered(SDL_SCANCODE_V))
        {
            hud->RGBA_Color(red);
        }
    }

    void EyeController::mouse_rotation(Transform* eye)
    {
        int mouse_x;
        int mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        glm::vec2 mouse_pos(mouse_x, mouse_y);
        target_direction = glm::normalize(mouse_pos - glm::vec2(eye->getPosition()));


        float radian = glm::atan(target_direction.y, target_direction.x);
        glm::vec3 rot(0.f, 0.f, radian);
        eye->setRotation(rot);
    }
}
