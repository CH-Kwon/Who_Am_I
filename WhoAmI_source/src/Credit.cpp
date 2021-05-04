/**
\file        Credit.cpp
\author      Chiho Kwon
\par         email: erpo0811@gmail.com
\par         course: GAM200
\date        12/15/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
#include "Credit.h"
#include "Application.h"
#include "Camera.h"
#include "GameList.h"
#include "GameStateManager.h"
#include "Graphics.h"
#include "Input.h"
#include "ObjectFactory.h"
#include "ObjectGenerator.h"
#include "System.h"
#include <glm/glm.hpp>
#include <iostream>

using namespace std;
using namespace glm;

namespace FindersEngine
{
    void CreditStateLoad(void)
    {
    }
    void CreditStateInit(void)
    {
        GRAPHICS->BackgroundColor(0.f, 0.f, 0.f, 1.0f);

        float screen_width = 1280.f;
        float screen_height = 720.f;

        using namespace glm;

        OBJECT_GEN->CreateHud(vec3(screen_width / 2.f, screen_height / 2.f, 0.f), vec3(screen_width, screen_height, 0.f), 5, "PIN_CREDIT_INFO.png");
    }

    void CreditStateUpdate(float dt)
    {

        if (Input::GetInstance().IsTriggered(SDL_SCANCODE_ESCAPE) || Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_B))
        {
            GAME_STATE->SetNextState(SL_MENU);
        }
    }

    void CreditStateExit(void)
    {
        OBJECT_FACTORY->DestroyAllObjects();
    }

    void CreditStateUnload(void)
    {
    }
}
