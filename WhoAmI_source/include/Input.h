/**
\file        Input.h
\author      Changuk Lee
\par         email: leechanguk0510@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once

#ifndef INPUT_H_
#define INPUT_H_

#include "Headers_SDL.h"

#include <bitset>
#include <cassert>

#include <glm/glm.hpp>

/*
SDL_NUM_MOUSE
#1 SDL_BUTTON_LEFT
#2 SDL_BUTTON_RIGHT
*/
#define SDL_NUM_MOUSE 4

namespace FindersEngine
{


    class Input
    {
    public:
        //Only interface is getInstace()
        //How to use? Input::getInstance().~
        static Input& GetInstance()
        {
            static Input input; //itself!
            return input;
        }

        void Init();
        void Reset();

        void SetKeyPressed(SDL_Scancode key, SDL_EventType keyStatus);
        void SetMousePressed(int MouseButton, SDL_EventType MouseStatus);
        void SetGamepadPressed(int GamepadButton, SDL_EventType GamepadStatus);
        static bool IsPressed(SDL_Scancode key);
        static bool IsTriggered(SDL_Scancode key);
        static bool IsReleased(SDL_Scancode key);

        static bool IsMousePressed(int mouse);
        static bool IsMouseTriggered(int mouse);
        static bool IsMouseReleased(int mouse);

        static bool IsGamePadPressed(SDL_GameControllerButton GamepadButton);
        static bool IsGamePadTriggered(SDL_GameControllerButton GamepadButton);
        static bool IsGamePadReleased(SDL_GameControllerButton GamepadButton);
        static bool IsGamePadAnyTriggered(void);

        static bool IsAnyPressed(void);
        static bool IsAnyTriggered(void);
        static bool IsAnyReleased(void);

        bool IsTriggerPrev;
    };
};

#endif // !INPUT_H_
