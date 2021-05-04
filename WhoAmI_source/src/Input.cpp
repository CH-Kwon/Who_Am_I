/**
\file        Input.cpp
\author      Changuk Lee
\par         email: leechanguk0510@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include <bitset>

#include "DebugUtil.h"
#include "Input.h"

/*
SDL_NUM_MOUSE
#1 SDL_BUTTON_LEFT
#2 SDL_BUTTON_RIGHT
*/
#define SDL_NUM_MOUSE 4
#define SDL_NUM_GAMEPAD 16
/*changuklee*/
#define SDL_NUM_JOYSTIC 8
using namespace FindersEngine;
int Mouseconde = 0;

namespace
{

    std::bitset<SDL_NUM_SCANCODES> s_pressed;
    std::bitset<SDL_NUM_SCANCODES> s_triggered;
    std::bitset<SDL_NUM_SCANCODES> s_released;

    std::bitset<SDL_NUM_MOUSE> s_mousePressed;
    std::bitset<SDL_NUM_MOUSE> s_mouseTriggered;
    std::bitset<SDL_NUM_MOUSE> s_mouseReleased;

    std::bitset<SDL_NUM_GAMEPAD> s_gamepadPressed;
    std::bitset<SDL_NUM_GAMEPAD> s_gamepadTriggered;
    std::bitset<SDL_NUM_GAMEPAD> s_gamepadReleased;
}

void Input::Init()
{
    s_pressed.reset();
    s_triggered.reset();
    s_released.reset();

    s_mousePressed.reset();
    s_mouseTriggered.reset();
    s_mouseReleased.reset();

    s_gamepadPressed.reset();
    s_gamepadTriggered.reset();
    s_gamepadReleased.reset();

    IsTriggerPrev = false;
}

void Input::Reset()
{
    s_triggered.reset();
    s_released.reset();

    s_mouseTriggered.reset();
    s_mouseReleased.reset();

    s_gamepadTriggered.reset();
    s_gamepadReleased.reset();
}

void Input::SetKeyPressed(SDL_Scancode key, SDL_EventType keyStatus)
{
    assert(SDL_SCANCODE_UNKNOWN < key && key < SDL_NUM_SCANCODES && "Invalid input");

    if (keyStatus == SDL_KEYDOWN)
    {
        s_pressed.set(key);
        if (!IsTriggerPrev)
        {
            s_triggered[key] = true;
            IsTriggerPrev = true;
        }
    }
    else if (keyStatus == SDL_KEYUP)
    {
        s_released.set(key);
        s_pressed.reset(key);
        if (IsTriggerPrev)
        {
            IsTriggerPrev = false;
        }
    }
}

void Input::SetMousePressed(int MouseButton, SDL_EventType MouseStatus)
{
    if (MouseStatus == SDL_MOUSEBUTTONDOWN)
    {
        s_mousePressed.set(MouseButton);
        s_mouseTriggered[MouseButton] = true;
    }
    else if (MouseStatus == SDL_MOUSEBUTTONUP)
    {
        s_mouseReleased.set(MouseButton);
        s_mousePressed.reset(MouseButton);
    }
}

void Input::SetGamepadPressed(int GamepadButton, SDL_EventType GamepadStatus)
{
    if (GamepadStatus == SDL_CONTROLLERBUTTONDOWN)
    {
        s_gamepadPressed.set(GamepadButton);
        s_gamepadTriggered[GamepadButton] = true;
    }
    else if (GamepadStatus == SDL_CONTROLLERBUTTONUP)
    {
        s_gamepadReleased.set(GamepadButton);
        s_gamepadPressed.reset(GamepadButton);
    }
}

bool Input::IsPressed(SDL_Scancode key)
{
    return s_pressed[key];
}
bool Input::IsTriggered(SDL_Scancode key)
{
    return s_triggered[key];
}
bool Input::IsReleased(SDL_Scancode key)
{
    return s_released[key];
}
/**/
bool Input::IsAnyPressed()
{
    return s_pressed.any();
}
bool Input::IsAnyTriggered()
{
    return s_triggered.any();
}
bool Input::IsAnyReleased()
{
    return s_released.any();
}
/**/
bool Input::IsMousePressed(int mouse)
{
    return s_mousePressed[mouse];
}
bool Input::IsMouseTriggered(int mouse)
{
    return s_mouseTriggered[mouse];
}
bool Input::IsMouseReleased(int mouse)
{
    return s_mouseReleased[mouse];
}

bool Input::IsGamePadPressed(SDL_GameControllerButton GamepadButton)
{
    return s_gamepadPressed[GamepadButton];
}
bool Input::IsGamePadTriggered(SDL_GameControllerButton GamepadButton)
{
    return s_gamepadTriggered[GamepadButton];
}
bool Input::IsGamePadReleased(SDL_GameControllerButton GamepadButton)
{
    return s_gamepadReleased[GamepadButton];
}
bool Input::IsGamePadAnyTriggered(void)
{
    return s_gamepadTriggered.any();
}