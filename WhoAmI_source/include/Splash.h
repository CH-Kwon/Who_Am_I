/**
\file        Splash.h
\author      Daechur Jeong
\par         email: wmdhwmdh@gmail.com
\par         course: GAM200
\date        12/15/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once
#include "Object.h"
#ifndef SPLASH_H
#define SPLASH_H

namespace FindersEngine
{
    void SplashStateLoad(void);
    void SplashStateInit(void);
    void SplashStateUpdate(float dt);
    void SplashStateExit(void);
    void SplashStateUnload(void);
}

#endif // !LEVEL_1_H
