/**
\file        ButtonController.h
\author      Chiho Kwon
\par         email: erpo0811@gmail.com
\par         course: GAM200
\date        12/15/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once

#ifndef BUTTON_CONTROLLER_H_
#define BUTTON_CONTROLLER_H_

#include "Application.h"
#include "ComponentType.h"
#include "Controller.hpp"
#include "Input.h"
#include <glm/glm.hpp>

namespace FindersEngine
{
    class Transform;

    class ButtonController : public Controller
    {
    public:
        ButtonController();
        ~ButtonController();
        void CreateObj(void);

        void Init() override;
        void Update(float deltaTime) override;

        void setName(const std::string& str)
        {
            name = str;
        }
        const std::string& getName() const
        {
            return name;
        }

        Transform* transform; // position, scale, rotation

    private:
        std::string name;
        int index;
        Collision* collision;
        Hud* hud;

        enum CurrentStatus
        {
            NULLSTATUS,
            TutorialButton,
            OptionButton,
            HowToPlayButton,
            QuitButton,
            GoToMenu,
            BackToMenu,
            Back,
            Resume,
            H_Play,

        };
        int current;
        int past;
    };
}

#endif // !PLAYER_CONTROLLER_H_
