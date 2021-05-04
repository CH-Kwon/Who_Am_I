/**
\file        GameLogic.h
\author      Changuk Lee
\par         email: leechanguk0510@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once

#ifndef GAME_LOGIC_H_
#define GAME_LOGIC_H_

#include "System.h"
#include <list>
namespace FindersEngine
{
    class Controller;
    class GameLogic : public System
    {
    public:
        GameLogic();
        ~GameLogic() {}

        void Init() override {}
        void Update(float deltaTime) override;

        std::list<Controller*>::iterator Insert(Controller* item);
        void Erase(std::list<Controller*>::iterator iterpContoller);
        void GetSecretNumber(char number, int index);
        bool CheckSecretNumber();
        void ClearGetSecretNumber();
        char GetSercretNumber[4];
        int INDEX;

    private:
        // List of Controller components
        std::list<Controller*> gameControllers;

        char SercretNumber[4];
    };

    extern GameLogic* GAMELOGIC;
};

#endif // !GAME_LOGIC_H_
