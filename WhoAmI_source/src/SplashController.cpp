/**
\file        SplashController.cpp
\author      jungdae.chur
\par         email: wmdhwmdh@gmail.com
\par         course: GAM200
\date        12/13/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/


#include "SplashController.h"
#include "../../WhoAmI/Include/GameStateManager.h"
#include "Object.h"
#include "Sprite.h"

namespace FindersEngine
{
    SplashController::SplashController()
    {
    }
    SplashController::~SplashController()
    {
    }
    void SplashController::Init()
    {
        sprite = dynamic_cast<Sprite*>(GetOwner()->GetComponent(CT_SPRITE));
    }
    void SplashController::Update(float deltaTime)
    {

        if (sprite->getBlendAlphaElapsedTime() <= 0.0f)
        {
            GAME_STATE->SetNextState(SL_LEVEL1);
        }
    }
};