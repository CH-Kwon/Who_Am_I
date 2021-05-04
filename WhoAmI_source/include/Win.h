/**
\file        Win.h
\author      Chiho Kwon
\par         email: erpo0811@gmail.com
\par         course: GAM200
\date        12/15/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once
#ifndef WIN_H
#define WIN_H
namespace FindersEngine
{
    void WinStateLoad(void);
    void WinStateInit(void);
    void WinStateUpdate(float dt);
    void WinStateExit(void);
    void WinStateUnload(void);
}
#endif