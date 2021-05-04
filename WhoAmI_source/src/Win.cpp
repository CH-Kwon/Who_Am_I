/**
\file        Win.cpp
\author      Chiho Kwon
\par         email: erpo0811@gmail.com
\par         course: GAM200
\date        12/15/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "Win.h"
#include "Application.h"
#include "Engine.h"
#include "GameStateManager.h"
#include "Graphics.h"
#include "Input.h"
#include "ObjectFactory.h"
#include "ObjectGenerator.h"
#include "SoundManager.h"
#include <glm/glm.hpp>
#include <iostream>

using namespace std;
using namespace glm;

namespace FindersEngine
{
    void WinStateLoad(void)
    {
    }
    void WinStateInit(void)
    {
        GRAPHICS->BackgroundColor(0.f, 0.f, 0.f, 1.0f);
		SOUNDMANAGER->play("WIN_SOUND.mp3");
        auto screen_width = 1280.f;
        auto screen_hegiht = 720.f;

        using namespace glm;

        OBJECT_GEN->CreateHud(vec3(screen_width / 2.f, screen_hegiht / 2.f, 0.f), vec3(screen_width, screen_hegiht, 1.f), 500, "PIN_WIN.png");
    }
    void WinStateUpdate(float dt)
    {
        if (Input::GetInstance().IsAnyTriggered())
        {
            GAME_STATE->SetNextState(SL_MENU);
            if (ENGINE->isPause)
                ENGINE->isPause = false;
        }
        if (Input::GetInstance().IsGamePadAnyTriggered())
        {
            GAME_STATE->SetNextState(SL_MENU);
            if (ENGINE->isPause)
                ENGINE->isPause = false;
        }
    }
    void WinStateExit(void)
    {
		SOUNDMANAGER->stop("WIN_SOUND.mp3");
        OBJECT_FACTORY->DestroyAllObjects();
    }
    void WinStateUnload(void)
    {
    }
}
