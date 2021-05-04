/**
\file        Menu.cpp
\author      Chiho Kwon
\par         email: erpo0811@gmail.com
\par         course: GAM200
\date        12/15/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "Menu.h"
//#include "Level1.h"
//#include "Level2.h"
#include "ButtonController.h"
#include "Camera.h"
#include "DebugUtil.h" // debugassert
#include "Graphics.h"
#include "Hud.h"
#include "RigidBody.h"
#include "Texture.h"

#include "Application.h" //swap window


#include "ObjectFactory.h"
#include "SoundManager.h"
#include <glm/glm.hpp>
#include "GameStateManager.h"

#include "ObjectGenerator.h"
#include <iostream>

#define WIDTH 1280
#define HEIGHT 640

using namespace std;
using namespace glm;

namespace FindersEngine
{
    namespace
    {
    }

    void MenuStateLoad(void)
    {
    }

	void MenuStateInit(void)
	{
            const float interval = (WIDTH / 6 + 30);
                OBJECT_GEN->CreateHud(vec3(WIDTH / 2, HEIGHT / 3.5f, 0), glm::vec3(WIDTH / 1.5f, HEIGHT / 3, 0.f), 3100, "PIN_TITLE.png");
                OBJECT_GEN->CreateButton(vec3(WIDTH / 4.5f, HEIGHT / 1.2f, 0), vec3(WIDTH / 5, HEIGHT / 8, 0.f), 3500, "PIN_START.png", "StartButton");
                OBJECT_GEN->CreateButton(vec3(WIDTH / 2, HEIGHT / 1.2f, 0), vec3(WIDTH / 5, HEIGHT / 8, 0.f), 3501, "PIN_OPTION.png", "OptionButton");
                OBJECT_GEN->CreateButton(vec3(WIDTH / 4.5f + interval * 3, HEIGHT / 1.2f, 0), vec3(WIDTH / 5, HEIGHT / 8, 0.f), 3502, "PIN_CREDIT.png", "CreditButton");
                OBJECT_GEN->CreateEye(vec3(WIDTH / 2.6f, HEIGHT / 2.1f, 0), glm::vec3(120, 120, 0.f), 1007, "PIN_EYE1.png");
                OBJECT_GEN->CreateEye(vec3(WIDTH / 1.7f, HEIGHT / 2.1f, 0), glm::vec3(120, 120, 0.f), 1008, "PIN_EYE2.png");
                OBJECT_GEN->CreateButton(vec3(WIDTH / 4.5f + interval / 2, HEIGHT / 1.2f + interval / 2 - 10, 0), vec3(WIDTH / 6, HEIGHT / 8, 0.f), 3503, "PIN_HOWTOPLAY.png", "HowToPlayButton");
                OBJECT_GEN->CreateButton(vec3(WIDTH / 4.5f + interval * 5 / 2, HEIGHT / 1.2f + interval / 2 - 10, 0), vec3(WIDTH / 6, HEIGHT / 8, 0.f), 3504, "PIN_QUIT.png", "QuitButton");
				bool checksound = true;
				SOUNDMANAGER->musics["MENU_SOUND.mp3"].ch->isPlaying(&checksound);
				if(!checksound)
				SOUNDMANAGER->play("MENU_SOUND.mp3");
		GRAPHICS->BackgroundColor(0, 0, 0, 1);
	}

    void MenuStateUpdate(float dt)
    {
        if (Input::GetInstance().IsTriggered(SDL_SCANCODE_2))
            GAME_STATE->SetNextState(SL_LEVEL2);
        if (Input::GetInstance().IsTriggered(SDL_SCANCODE_1))
            GAME_STATE->SetNextState(SL_LEVEL3);
    }

    void MenuStateExit(void)
    {
        OBJECT_FACTORY->DestroyAllObjects();
    }

    void MenuStateUnload(void)
    {
    }
}