/**
\file        HowToPlay.h
\author      Chiho Kwon
\par         email: erpo0811@gmail.com
\par         course: GAM200
\date        12/15/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once

#ifndef HOWTOPLAY_H
#define HOWTOPLAY_H
namespace FindersEngine
{
    void HowToPlayStateLoad(void);
    void HowToPlayStateInit(void);
    void HowToPlayStateUpdate(float dt);
    void HowToPlayStateExit(void);
    void HowToPlayStateUnload(void);
}
#endif