/**
 \file
 \author
 \par         email:
 \par         course: GAM200
 \date        ?/?/2017
 \brief
 
 */

#pragma once

#ifndef PLAYER_INFO_H_
#define PLAYER_INFO_H_

#include "System.h"
#include <list>
namespace FindersEngine
{

    class PlayerInfo
    {
        char* name;
        int age;
        bool sex;
    };
    extern PlayerInfo* GAMELOGIC;
};

#endif // !GAME_LOGIC_H_
