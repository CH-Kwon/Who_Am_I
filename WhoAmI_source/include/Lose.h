/**
\file        Lose.h
\author      SeongHyun Hong
\par         email: tjdgus3174@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once
#ifndef LOSE_H
#define LOSE_H
namespace FindersEngine
{
    void LoseStateLoad(void);
    void LoseStateInit(void);
    void LoseStateUpdate(float dt);
    void LoseStateExit(void);
    void LoseStateUnload(void);
}
#endif