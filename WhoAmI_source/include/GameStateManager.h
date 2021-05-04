/**
\file        GameStateManager.h
\author      Chiho Kwon
\par         email: erpo0811@gmail.com
\par         course: GAM200
\date        12/15/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once
#include "GameList.h"
#include "System.h"

namespace FindersEngine
{

    //class Stage;

    class GameState : public System
    {
    public:
        void (*State_Load)(void);
        void (*State_Init)(void);
        void (*State_Update)(float dt);
        void (*State_Exit)(void);
        void (*State_Unload)(void);

        GameState();

        //Initialize the system
        void Init() override;

        //All systems are updated every frame
        void Update(float dt) override;

        void Clean();
        void SetNextState(StatesList state);
        ~GameState();

        StatesList previous;
        StatesList current;
        StatesList next;
    };
    extern GameState* GAME_STATE;
}
