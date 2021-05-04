/**
\file        HudController.h
\author      jungdae.chur
\par         email: wmdhwmdh@gmail.com
\par         course: GAM200
\date        12/13/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once

#ifndef HUD_CONTROLLER_H_
#define HUD_CONTROLLER_H_

#include "Application.h"
#include "ComponentType.h"
#include "Controller.hpp"
#include "Input.h"
#include "LTimer.hpp"
#include "Timer.hpp"
#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace FindersEngine
{
    class Transform;

    class HudController : public Controller
    {
    public:
        HudController();
        ~HudController();

        void Init() override;
        void Update(float deltaTime) override;

        void Set_LifeTime(float time)
        {
            lifeTime = time;
        }

        float get_LifeTime() const
        {
            return lifeTime;
        }

        // in init factory
        // this->setName("Message1");
        //
        void setName(const std::string& given)
        {
            myName = given;
        }
        const std::string& getName() const
        {
            return myName;
        }

        void suicide(float dt);

        Transform* transform; // position, scale, rotation
        static std::vector<std::string> killList;

    private:
        Collision* collision;
        Hud* hud;
        Timer timer;
        float lifeTime = 3.0f;
        std::string myName; //identity
    };
}

#endif
