/**
\file        ComponentType.h
\author      SeongHyun Hong
\par         email: tjdgus3174@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once

namespace FindersEngine
{
    enum ComponentType
    {
        CT_INVALID = 0, //base zero
        CT_TRANSFORM,
        CT_SPRITE, //Graphics
        CT_SPRITE_TEXT,
        CT_CAMERA,
        CT_HUD,
        CT_RIGID_BODY, //Physics
        CT_COLLISION,
        CT_CONTROLLER,
        CT_COUNT
    };

    // Common
    class Transform;

    // Graphic
    class Sprite;
    class SpriteText;
    class Camera;
    class Hud;

    // Physics
    class RigidBody;
    class Collision;

    // GameLogic
    class Controller;
};
