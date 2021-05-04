/**
\file        MapEditor.h
\author      jinseob.park
\par         email: 0814owl@gmail.com
\par         course: GAM200
\date        12/15/2017
\brief       MapEdit stage.
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once
#ifndef MAPEDITOR_H
#define MAPEDITOR_H
#include <vector>

namespace FindersEngine
{
    void MapEditStateLoad(void);
    void MapEditStateInit(void);
    void MapEditStateUpdate(float dt);
    void MapEditStateExit(void);
    void MapEditStateUnload(void);

}

#endif
