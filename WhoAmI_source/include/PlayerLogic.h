/**
\file        PlayerLogic.h
\author      SeongHyun Hong
\par         email: tjdgus3174@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once
#ifndef PLAYER_LOGIC_H_
#define PLAYER_LOGIC_H_

#include "Collision.h"
#include "Transform.hpp"
#include <glm/glm.hpp>
#include <glm/vec2.hpp>

namespace FindersEngine
{
    class PlayerLogic
    {
    public:
        PlayerLogic();
        ~PlayerLogic();
        void ShootBullet(Transform* player, float bullet_size);
        void mouse_rotation(Transform* player);
        void pad_rotation(Transform* player);
        void ShootBulletWithPad(Transform* player, float bullet_size);
        bool isShoot;
    };
    extern PlayerLogic* PLAYERLOGIC;
}


#endif // !PLAYER_LOGIC_H_
