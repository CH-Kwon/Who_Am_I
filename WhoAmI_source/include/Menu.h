/**
\file        Menu.h
\author      Chiho Kwon
\par         email: erpo0811@gmail.com
\par         course: GAM200
\date        12/15/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once

#ifndef MENU_H_
#define MENU_H_

#include "Object.h"
#include "Transform.hpp"

namespace FindersEngine
{
    void MenuStateLoad(void);
    void MenuStateInit(void);
    void MenuStateUpdate(float dt);
    void MenuStateExit(void);
    void MenuStateUnload(void);
}

#endif // !MENU_H_
