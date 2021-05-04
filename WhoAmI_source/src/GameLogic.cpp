/**
\file        GameLogic.cpp
\author      Changuk Lee
\par         email: leechanguk0510@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "GameLogic.h"
#include "Controller.hpp"
#include "SoundManager.h"
#include "Engine.h"
#include <cassert>

namespace FindersEngine
{
    GameLogic* GAMELOGIC = nullptr;

    GameLogic::GameLogic()
    {
        assert(GAMELOGIC == nullptr && "There can be only one in GameLogic System!");
        GAMELOGIC = this;
        SercretNumber[0] = '7';
        SercretNumber[1] = '2';
        SercretNumber[2] = '2';
        SercretNumber[3] = '3';

        INDEX = 0;
    }
    void GameLogic::Update(float deltaTime)
    {
		if (ENGINE->isPause == true)
		{
			SOUNDMANAGER->pause(true);
		}
		else
		{
			SOUNDMANAGER->pause(false);
		}
        for (auto element : gameControllers)
            element->Update(deltaTime);
    }
    std::list<Controller*>::iterator GameLogic::Insert(Controller* item)
    {
        std::list<Controller*>::iterator piterController;
        piterController = GAMELOGIC->gameControllers.insert(GAMELOGIC->gameControllers.end(), item);
        return piterController;
    }
    void GameLogic::Erase(std::list<Controller*>::iterator iterpContoller)
    {
        GAMELOGIC->gameControllers.erase(iterpContoller);
    }
    void GameLogic::GetSecretNumber(char number, int index)
    {
        index;
        GetSercretNumber[INDEX] = number;
        INDEX++;
        if (INDEX > 3)
        {
            INDEX = 0;
        }
    }
    bool GameLogic::CheckSecretNumber()
    {
        for (int i = 0; i < 4; ++i)
        {
            if (SercretNumber[i] != GetSercretNumber[i])
            {
                return false;
            }
        }
        return true;
    }
    void GameLogic::ClearGetSecretNumber()
    {
        for (int i = 0; i < 4; ++i)
        {
            GetSercretNumber[i] = 0;
        }
    }
}