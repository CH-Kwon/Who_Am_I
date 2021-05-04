/**
\file        Lose.cpp
\author      SeongHyun Hong
\par         email: tjdgus3174@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "Lose.h"
#include <glm/glm.hpp>
#include <iostream>

#include "Engine.h"
#include "Graphics.h"
#include "Headers_Systems.h"
#include "Input.h"
#include "Headers_Systems.h"
#include "SoundManager.h"
#include "Engine.h"
#include "Application.h"
#include "..\include\ObjectGenerator.h"

using namespace std;
using namespace glm;

namespace FindersEngine
{
    void LoseStateLoad(void)
    {
    }
    void LoseStateInit(void)
    {
        GRAPHICS->BackgroundColor(0.f, 0.f, 0.f, 1.0f);
		SOUNDMANAGER->play("LOSE_SOUND.mp3");
        auto screen_width = 1280.f;
        auto screen_hegiht = 720.f;

        using namespace glm;

        OBJECT_GEN->CreateHud(vec3(screen_width / 2.f, screen_hegiht / 2.f, 0.f), vec3(screen_width, screen_hegiht, 1.f), 500, "PIN_LOSE.png");
    }
    void LoseStateUpdate(float dt)
    {
        if (!APPLICATION->isUsingGamepad)
        {
            if (Input::GetInstance().IsAnyTriggered())
            {
                GAME_STATE->SetNextState(SL_MENU);
                if (ENGINE->isPause)
                    ENGINE->isPause = false;
            }
        }
        else if (APPLICATION->isUsingGamepad)
        {
            if (Input::GetInstance().IsGamePadAnyTriggered())
            {
                GAME_STATE->SetNextState(SL_MENU);
                if (ENGINE->isPause)
                    ENGINE->isPause = false;
            }
        }
    }
    void LoseStateExit(void)
    {
		SOUNDMANAGER->stop("LOSE_SOUND.mp3");
        OBJECT_FACTORY->DestroyAllObjects();
    }
    void LoseStateUnload(void)
    {
    }
}