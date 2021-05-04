/**
\file        ButtonLogicController.cpp
\author      Sehyun Kim
\par         email: kim4969\@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "ButtonLogicController.h"
#include "Headers_Components.h"
#include "Input.h"
#include "Object.h"


namespace FindersEngine
{
    namespace
    {
        using namespace glm;
        vec4 COLOR_WHITE(1.0f, 1.0f, 1.0f, 1.0f);
        vec4 COLOR_PESU_RED(0.5f, 0.0f, 0.0f, 1.0f);
        vec4 COLOR_RED(1.0f, 0.0f, 0.0f, 1.0f);
    }

    ButtonLogicController::ButtonLogicController()
    {
    }
    ButtonLogicController::~ButtonLogicController()
    {
    }
    void ButtonLogicController::Init()
    {
        transform = dynamic_cast<Transform*>(GetOwner()->GetComponent(CT_TRANSFORM));
        hud = dynamic_cast<Hud*>(GetOwner()->GetComponent(CT_HUD));
        collision = dynamic_cast<Collision*>(GetOwner()->GetComponent(CT_COLLISION));
    }

    void ButtonLogicController::Update(float deltaTime)
    {
        if (collision->MouseRectCollisionCheck(GetOwner()))
        {
            hud->RGBA_Color(COLOR_RED);
            if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
            {
                hud->RGBA_Color(COLOR_PESU_RED);
            }
        }
        else
        {
            hud->RGBA_Color(COLOR_WHITE);
        }
    }
}
