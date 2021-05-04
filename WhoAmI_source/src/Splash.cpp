/**
\file        Splash.cpp
\author      Daechur Jeong
\par         email: wmdhwmdh@gmail.com
\par         course: GAM200
\date        12/15/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "Splash.h"
#include "Application.h"
#include "Camera.h"
#include "GameList.h"
#include "GameStateManager.h"
#include "Graphics.h"
#include "Input.h"
#include "ObjectFactory.h"
#include "SoundManager.h"
#include "Sprite.h"
#include "System.h"
#include "Timer.hpp"
#include "Transform.hpp"
#include <glm/glm.hpp>
#include <iostream>

using namespace std;
using namespace glm;

namespace FindersEngine
{
    Timer t_timer;
    bool is_fmod = false;
    bool is_finders = false;
    Transform* finders_star_transform;
    Sprite* finders_sprite;
    Sprite* finders_star_sprite;
    Sprite* fmod_sprite;
    float rot = 0.f;
    bool ready_to_go = false;
    void SplashStateLoad(void)
    {
    }

    void SplashStateInit(void)
    {
        GRAPHICS->BackgroundColor(glm::vec4(0.f, 0.f, 0.f, 1.f), true);
        Object* splash = OBJECT_FACTORY->CreateEmptyObject(0);
        splash->SetShapeType(ST_RECTANGLE);

        Transform* transform = new Transform();
        transform->setPosition(vec3(0, 0, 0));
        transform->setScale(glm::vec3(800.f * 2.f * 1.5f, 800.f / 2.f * 1.5f, 1.f));
        splash->AddComponent(transform);

        Sprite* sprite = new Sprite();
        sprite->LoadTexture("PIN_LOGO.png");
        sprite->setBlendAlpha(2.f);
        glm::vec4 color(1.0f, 1.0f, 1.0f, 1.0f); // RGBA
        sprite->RGBA_Color(color);
        splash->AddComponent(sprite);
        splash->Init();
        SOUNDMANAGER->play("SPLASH_SOUND.wav");
        t_timer.Init();
    }
    void FmodSplashInit(void)
    {
        SOUNDMANAGER->play("SPLASH_SOUND.wav");
        Object* Fmod_splash = OBJECT_FACTORY->CreateEmptyObject(3);
        Fmod_splash->SetShapeType(ST_RECTANGLE);

        Transform* fmod_transform = new Transform();
        fmod_transform->setPosition(vec3(0, 0, 0));
        fmod_transform->setScale(glm::vec3(2800.f, 2000.f, 1.f));
        Fmod_splash->AddComponent(fmod_transform);

        fmod_sprite = new Sprite();
        fmod_sprite->LoadTexture("PIN_FMOD.png");
        fmod_sprite->setBlendAlpha(3.f);
        glm::vec4 color(1.0f, 1.0f, 1.0f, 1.0f); // RGBA
        fmod_sprite->RGBA_Color(color);
        Fmod_splash->AddComponent(fmod_sprite);
        Fmod_splash->Init();
    }
    void FindersSplashInit(void)
    {
        SOUNDMANAGER->play("SPLASH_SOUND.wav");
        GRAPHICS->BackgroundColor(glm::vec4(0.f, 0.f, 0.f, 1.f), true);
        Object* finders_splash = OBJECT_FACTORY->CreateEmptyObject(1);
        finders_splash->SetShapeType(ST_RECTANGLE);

        Transform* finders_transform = new Transform();
        finders_transform->setPosition(vec3(0.f, -0.1f, 0));
        finders_transform->setScale(glm::vec3(2000.f, 1200.f, 1.f));
        finders_splash->AddComponent(finders_transform);

        finders_sprite = new Sprite();
        finders_sprite->LoadTexture("PIN_FINDERS_SPLASH.png");
        finders_sprite->setBlendAlpha(3.5f);
        glm::vec4 finders_splash_color(1.f, 1.f, 1.f, 1.0f); // RGBA
        finders_sprite->RGBA_Color(finders_splash_color);
        finders_splash->AddComponent(finders_sprite);
        finders_splash->Init();
        ///////////////////////////////////////////////
        Object* finders_star_splash = OBJECT_FACTORY->CreateEmptyObject(2);
        finders_star_splash->SetShapeType(ST_RECTANGLE);

        finders_star_transform = new Transform();
        finders_star_transform->setPosition(vec3(-1.2f, 0.5f, 0));
        finders_star_transform->setScale(glm::vec3(200.f, 200.f, 1.f));
        finders_star_splash->AddComponent(finders_star_transform);

        finders_star_sprite = new Sprite();
        finders_star_sprite->LoadTexture("PIN_FINDERS_SPLASH_STAR.png");
        finders_star_sprite->setBlendAlpha(3.5f);
        glm::vec4 finders_splash_star_color(1.0f, 1.0f, 1.0f, 1.0f); // RGBA
        finders_star_sprite->RGBA_Color(finders_splash_star_color);
        finders_star_splash->AddComponent(finders_star_sprite);
        finders_star_splash->Init();
    }
    void SplashStateUpdate(float dt)
    {
        // Three splashes of our game
        if (t_timer.GetTime() > 2.f)
        {
            is_fmod = true;
        }

        if ((is_fmod == true) && (is_finders == false) && (!fmod_sprite))
        {
            FmodSplashInit();
            is_fmod = false;
        }
            
        if((t_timer.GetTime() > 4.5f) && (!finders_star_transform) && (!finders_sprite))
        {
            FindersSplashInit();
            is_finders = true;
        }
        if ((t_timer.GetTime() > 4.6f) && (ready_to_go == false))
        {
            finders_star_transform->setRotation(glm::vec3(0.f, 0.f, rot));
            if (rot < 3.14f)
                rot += 0.05f;
            else
            {
                rot = rot;
                ready_to_go = true;
            }
        }
        if (t_timer.GetTime() > 7.5f)
        {
            GAME_STATE->SetNextState(SL_MENU);
            ready_to_go = false;
        }
        if (Input::IsAnyTriggered())
            GAME_STATE->SetNextState(SL_MENU);

    }

    void SplashStateExit(void)
    {
        OBJECT_FACTORY->DestroyAllObjects();
    }

    void SplashStateUnload(void)
    {
    }
}