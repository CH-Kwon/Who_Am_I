/**
\file        HowToPlay.cpp
\author      Chiho Kwon
\par         email: erpo0811@gmail.com
\par         course: GAM200
\date        12/15/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
#include "HowToPlay.h"
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
    void HowToPlayStateLoad(void)
    {
    }
    void HowToPlayStateInit(void)
    {
        GRAPHICS->BackgroundColor(0.f, 0.f, 0.f, 1.0f);

        float screen_width = 1280.f;
        float screen_height = 720.f;

        using namespace glm;

        if (!APPLICATION->isUsingGamepad)
        {
            OBJECT_GEN->CreateCollisionHud(vec3(screen_width / 2.0f - 50, screen_height / 2.0f - 50, 0), glm::vec3(screen_width / 2.0f, screen_height / 2.0f - 50, 0.f), 7004, "PIN_KEYBOARDMOUSE.png");
            OBJECT_GEN->CreateButton(vec3(screen_width / 8.0f - 50, screen_height / 1.2f, 0), glm::vec3(screen_width / 12, screen_height / 12, 0.f), 7005, "PIN_GOMENU.png", "GoToMenu", LO_BASE);
            OBJECT_GEN->CreateCollisionHud(vec3(screen_width / 1.1f - 40, screen_height / 2.f, 0), glm::vec3(screen_width / 5, screen_height / 4, 0.f), 7006, "PIN_KEYINFO.png");
        }
        if (APPLICATION->isUsingGamepad)
        {
            OBJECT_GEN->CreateHud(vec3(screen_width, screen_height, 0), glm::vec3(screen_width * 3, screen_height * 3, 0.f), 3678, "PIN_H_BACKGROUND.png", LO_2);
            OBJECT_GEN->CreateHud(vec3(screen_width / 2 + 100, screen_height / 2, 0), glm::vec3(screen_width, screen_height, 0.f), 3679, "PIN_GAMEPAD.png", LO_2);
            OBJECT_GEN->CreateButton(vec3(screen_width / 8.0f - 50, screen_height / 2.f, 0), glm::vec3(screen_width / 11, screen_height / 11, 0.f), 1018, "PIN_H_BACK.png", "h_back", LO_2);
        }
        
    }

    void HowToPlayStateUpdate(float dt)
    {
        if (Input::GetInstance().IsTriggered(SDL_SCANCODE_ESCAPE) || Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_B))
        {
            GAME_STATE->SetNextState(SL_MENU);
        }
    }

    void HowToPlayStateExit(void)
    {
        OBJECT_FACTORY->DestroyAllObjects();
    }

    void HowToPlayStateUnload(void)
    {
    }
}
