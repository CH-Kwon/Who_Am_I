/**
\file        OptionState.cpp
\author      Sehyun Kim
\par         email: kim4969\@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "OptionState.h"
#include "Application.h"
#include "Collision.h"
#include "GameStateManager.h"
#include "Graphics.h"
#include "Input.h"
#include "ObjectFactory.h"
#include "ObjectGenerator.h"
#include "Option.hpp"
#include "SoundManager.h"
#include <glm/glm.hpp>

namespace FindersEngine
{
    namespace
    {
    }

    void OptionStateLoad(void)
    {
    }

    void OptionStateInit(void)
    {
        GRAPHICS->BackgroundColor(0.f, 0.f, 0.f, 1.0f);

        int v_screen_width;
        int v_screen_height;
        APPLICATION->get_virtual_screen_size(&v_screen_width, &v_screen_height);

        using namespace glm;
        OBJECT_GEN->CreateHud(vec3((float)v_screen_width / 2.f, (float)v_screen_height / 2.f, 0.f), vec3((float)v_screen_width, (float)v_screen_height, 1.f), 1000, "PIN_OPTION_PHOTO.png");
    }

    void OptionStateUpdate(float dt)
    {
        if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_BACK))
        {
            SOUNDMANAGER->play("SWITCH_MODE_SOUND.wav");
            APPLICATION->isUsingGamepad = false;
        }
        if (Input::GetInstance().IsTriggered(SDL_SCANCODE_T))
        {
            SOUNDMANAGER->play("SWITCH_MODE_SOUND.wav");
            APPLICATION->isUsingGamepad = true;
        }
        if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_B))
        {
            GAME_STATE->SetNextState(SL_MENU);
        }
        if (Input::GetInstance().IsPressed(SDL_SCANCODE_ESCAPE))
        {
            GAME_STATE->SetNextState(SL_MENU);
        }
        if (Input::GetInstance().IsTriggered(SDL_SCANCODE_E))
        {
            Option::getInstance().FullScreenOn();
        }
        else if (Input::GetInstance().IsTriggered(SDL_SCANCODE_R))
        {
            Option::getInstance().FullScreenOff();
        }
        else if (Input::GetInstance().IsTriggered(SDL_SCANCODE_A))
        {
            Option::getInstance().VolumnUp();
            SOUNDMANAGER->play("ZOMBIE_SOUND1.wav");
        }
        else if (Input::GetInstance().IsTriggered(SDL_SCANCODE_S))
        {
            Option::getInstance().VolumnDown();
            SOUNDMANAGER->play("ZOMBIE_SOUND1.wav");
        }
        else if (Input::GetInstance().IsTriggered(SDL_SCANCODE_ESCAPE))
        {
            GAME_STATE->SetNextState(SL_MENU);
        }
        if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_BACK))
        {
			SOUNDMANAGER->play("SWITCH_MODE_SOUND.wav");
            Option::getInstance().OnlyUsingKeyboard();
        }
        if (Input::GetInstance().IsTriggered(SDL_SCANCODE_T))
        {
			SOUNDMANAGER->play("SWITCH_MODE_SOUND.wav");
            Option::getInstance().OnlyUsingGamepad();
        }
        if (APPLICATION->isUsingGamepad)
        {
            if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_BACK))
            {
                APPLICATION->isUsingGamepad = false;
            }
        }
    }

    void OptionStateExit(void)
    {
        OBJECT_FACTORY->DestroyAllObjects();
    }
    void OptionStateUnload(void)
    {
    }
}
