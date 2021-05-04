/**
\file        GameList.h
\author      Chiho Kwon
\par         email: erpo0811@gmail.com
\par         course: GAM200
\date        12/15/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once
#ifndef GAME_LIST_H
#define GAME_LIST_H

enum StatesList
{
    SL_NULL,
    SL_SPLASH,
    SL_MENU,
    SL_LEVEL1,
    SL_LEVEL2,
    SL_LEVEL3,
    SL_LOSE,
    SL_WIN,
    SL_OPTION,
    SL_HOWTOPLAY,
    SL_CREDIT,

    SL_QUIT,
    SL_RESTART,
    SL_MAPEDIT
};

#endif // !GAME_LIST_H
