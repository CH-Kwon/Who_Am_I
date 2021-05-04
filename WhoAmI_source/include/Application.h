/**
\file        Application.h
\author      jungdae.chur
\par         email: wmdhwmdh@gmail.com
\par         course: GAM200
\date        12/13/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Headers_SDL.h"
#include <GL/glew.h>

#include "System.h"
#include <glm/glm.hpp>

namespace FindersEngine
{
    class Application : public System
    {
    public:
        Application();
        ~Application();

        void Init() override;
        void Update(float deltaTime) override;
        void SwapWindow();
        bool VSync(bool on = true); //return true: Vsync on, false: Vsync off
        void get_virtual_screen_size(int* width, int* height) const
        {
            *width = 1280;
            *height = 720;
        }
        void get_real_screen_size(int* width, int* height) const { SDL_GetWindowSize(pWindow, width, height); }
        SDL_Window* getWindow() { return pWindow; }
        SDL_Event& getEvent() { return SDL_event; }
        glm::vec2 get_right_pad() { return right_padpos; }
        glm::vec2 get_left_pad() { return left_padpos; }
        glm::vec2 screen_to_world(const glm::vec2& screen_coordinate);
        void TurnOffGamePad() { isUsingGamepad = false; }
        void TurnOnGamePad()
        {
            isUsingGamepad = true;
            SDL_ShowCursor(SDL_DISABLE);
        }
        bool isGamePad();
        void UpdatePadStatus();

    public:
        SDL_GameController* pad;
        SDL_Joystick* joy;
        SDL_Haptic* gControllerHaptic;
        bool isUsingGamepad = false; // automatically
        int padstatus;
        int pad_final_status;
        int pausePadStatus;
        int pad_howtoplay_status;
        bool isPause;
        bool isHowToPlayer;

    private:
        void PollEvents();
        void PollWindowEvent(SDL_Event& currentEvent);
        void PollKeyboardEvent(SDL_Event& currentEvent);
        void PollMouseEvent(SDL_Event& currentEvent);
        void PollGamePadEvent(SDL_Event& currentEvent);

    private:
        glm::vec2 right_padpos;
        glm::vec2 left_padpos;
        float degree;
        int SCREEN_WIDTH;
        int SCREEN_HEIGHT;
        int instanceID;
        bool init_success = false;
        SDL_Event SDL_event;
        SDL_Window* pWindow = nullptr;
        SDL_GLContext glContext = NULL;
        SDL_DisplayMode current_display;
        bool enterthecode;
    };
    extern Application* APPLICATION;
};


#endif // !APPLICATION_H_
