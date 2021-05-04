/**
\file        GameStateManager.cpp
\author      Chiho Kwon
\par         email: erpo0811@gmail.com
\par         course: GAM200
\date        12/15/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "GameList.h"

#include "Credit.h"
#include "HowToPlay.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "MapEditor.h"
#include "Menu.h"
#include "OptionState.h"
#include "Splash.h"
#include "Win.h"

#include "Application.h" //swap window
#include "Graphics.h"
#include "Input.h"
#include "ObjectFactory.h"
#include "PlayerController.h"

#include "DebugUtil.h" // debugassert
#include "GameStateManager.h"
#include "Lose.h"
#include <cassert>
#include <iostream>

using namespace std;

namespace FindersEngine
{
    GameState* GAME_STATE = nullptr;
    GameState::GameState()
    {
        assert(GAME_STATE == nullptr && "No more than one instance of Game State system!");
        GAME_STATE = this;
    }

    void GameState::Init()
    {
        next = SL_SPLASH;
    }

    void GameState::Update(float dt)
    {
        if (next == SL_SPLASH)
        {
            State_Load = &SplashStateLoad;
            State_Load();

            State_Init = &SplashStateInit;
            State_Init();

            State_Update = &SplashStateUpdate;

            State_Exit = &SplashStateExit;
            State_Unload = &SplashStateUnload;

            current = SL_SPLASH;
            next = SL_NULL;
        }

        if (next == SL_MENU)
        {
            State_Exit();
            State_Unload();

            State_Load = &MenuStateLoad;
            State_Load();

            State_Init = &MenuStateInit;
            State_Init();

            State_Update = &MenuStateUpdate;

            State_Exit = &MenuStateExit;
            State_Unload = &MenuStateUnload;

            current = SL_MENU;
            next = SL_NULL;
        }

        else if (next == SL_LEVEL1)
        {
            State_Exit();
            State_Unload();

            State_Load = &Level1StateLoad;
            State_Load();

            State_Init = &Level1StateInit;
            State_Init();

            State_Update = &Level1StateUpdate;

            State_Exit = &Level1StateExit;
            State_Unload = &Level1StateUnload;

            current = SL_LEVEL1;
            next = SL_NULL;
        }
        else if (next == SL_LEVEL2)
        {
            State_Exit();
            State_Unload();

            State_Load = &Level2StateLoad;
            State_Load();

            State_Init = &Level2StateInit;
            State_Init();

            State_Update = &Level2StateUpdate;

            State_Exit = &Level2StateExit;
            State_Unload = &Level2StateUnload;

            current = SL_LEVEL2;
            next = SL_NULL;
        }
        else if (next == SL_LEVEL3)
        {
            State_Exit();
            State_Unload();

            State_Load = &Level3StateLoad;
            State_Load();

            State_Init = &Level3StateInit;
            State_Init();

            State_Update = &Level3StateUpdate;

            State_Exit = &Level3StateExit;
            State_Unload = &Level3StateUnload;

            current = SL_LEVEL3;
            next = SL_NULL;
        }
        else if (next == SL_OPTION)
        {
            State_Exit();
            State_Unload();

            State_Load = &OptionStateLoad;
            State_Init = &OptionStateInit;
            State_Update = &OptionStateUpdate;
            State_Exit = &OptionStateExit;
            State_Unload = &OptionStateUnload;

            State_Load();
            State_Init();
            current = SL_OPTION;
            next = SL_NULL;
        }
        else if (Input::GetInstance().IsTriggered(SDL_SCANCODE_K))
        {
            State_Exit();
            State_Unload();

            State_Load = &MapEditStateLoad;
            State_Init = &MapEditStateInit;
            State_Update = &MapEditStateUpdate;
            State_Exit = &MapEditStateExit;
            State_Unload = &MapEditStateUnload;

            State_Load();
            State_Init();
            next = SL_NULL;
        }
        else if (next == SL_WIN)
        {
            State_Exit();
            State_Unload();

            State_Load = &WinStateLoad;
            State_Init = &WinStateInit;

            State_Update = &WinStateUpdate;

            State_Exit = &WinStateExit;
            State_Unload = &WinStateUnload;

            State_Load();
            State_Init();
            current = SL_WIN;
            next = SL_NULL;
        }
        else if (next == SL_LOSE)
        {
            State_Exit();
            State_Unload();

            State_Load = &LoseStateLoad;
            State_Init = &LoseStateInit;

            State_Update = &LoseStateUpdate;

            State_Exit = &LoseStateExit;
            State_Unload = &LoseStateUnload;

            State_Load();
            State_Init();
            current = SL_LOSE;
            next = SL_NULL;
        }
        else if (next == SL_HOWTOPLAY)
        {
            State_Exit();
            State_Unload();

            State_Load = &HowToPlayStateLoad;
            State_Init = &HowToPlayStateInit;

            State_Update = &HowToPlayStateUpdate;

            State_Exit = &HowToPlayStateExit;
            State_Unload = &HowToPlayStateUnload;

            State_Load();
            State_Init();

            current = SL_HOWTOPLAY;
            next = SL_NULL;
        }
        else if (next == SL_CREDIT)
        {
            State_Exit();
            State_Unload();

            State_Load = &CreditStateLoad;
            State_Init = &CreditStateInit;

            State_Update = &CreditStateUpdate;

            State_Exit = &CreditStateExit;
            State_Unload = &CreditStateUnload;

            State_Load();
            State_Init();

            current = SL_CREDIT;
            next = SL_NULL;
        }
        else if (next == SL_RESTART)
        {
            switch (previous)
            {
                case SL_LEVEL1:
                    State_Exit();
                    State_Unload();
                    State_Update = &Level1StateUpdate;
                    State_Exit = &Level1StateExit;
                    State_Unload = &Level1StateUnload;
                    State_Load();
                    State_Init();
                    next = SL_NULL;
                    break;
                default:
                    break;
            }
        }
        //Keep updating state
        State_Update(dt);
    }

    void GameState::SetNextState(StatesList state)
    {
        next = state;
    }

    void GameState::Clean()
    {
        OBJECT_FACTORY->DestroyAllObjects();
    }

    GameState::~GameState()
    {
    }
}
