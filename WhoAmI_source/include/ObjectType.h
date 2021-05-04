/**
\file        ObjectType.h
\author      SeongHyun Hong
\par         email: tjdgus3174@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#ifndef OBJECT_TYPE_H_
#define OBJECT_TYPE_H_

namespace FindersEngine
{
    // Object Type
    /* YOU MUST INIT THE TYPE OF OBJECT TYPE */
    enum ObjectType : short
    {
        OT_NONE = 0,

        OT_PLAYER,
        OT_ZOMBIE,
        OT_WALL,
        OT_BULLET,
        OT_PISTOL,
        OT_AMMO,
        OT_ARMOR,
        OT_HDOOR,
        OT_VDOOR,
        OT_FDOOR, // Final door
        OT_KEY,
        OT_NUMPAD,
        OT_BUTTON,
        OT_MESSAGE,
        OT_COUNT,
        OT_HINT
    };

    // Collision Shape
    /* YOU MUST INIT THE TYPE OF COLLISION SHAPE */
    enum ShapeType : short
    {
        ST_NONE = 0,

        ST_CIRCLE,
        ST_RECTANGLE,
        ST_HUD,
        ST_LINE
    };
};

#endif // !OBJECT_TYPE_H_
