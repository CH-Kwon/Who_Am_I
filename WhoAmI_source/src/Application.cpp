/**
\file        Application.cpp
\author      jungdae.chur
\par         email: wmdhwmdh@gmail.com
\par         course: GAM200
\date        12/13/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "Application.h"
#include "ObjectFactory.h"
#include <cassert>
#include <iostream>

#include "Engine.h"
#include "Input.h"
#include "Timer.hpp"

#include "CameraSystem.h"
#include "GameStateManager.h"
#include "Graphics.h"
#include "Object.h"
#include "ObjectFactory.h"
#include "imgui.h"
#include "imgui_impl_sdl_gl3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "DataPipeline.hpp"

namespace FindersEngine
{
    Application* APPLICATION = nullptr;

    const GLuint DEFAULT_SCREEN_WIDTH = 1280;
    const GLuint DEFAULT_SCREEN_HEIGHT = 720;
    const char* GAME_TITLE = "Who Am I";

    Application::Application()
        : SCREEN_WIDTH(DEFAULT_SCREEN_WIDTH), SCREEN_HEIGHT(DEFAULT_SCREEN_HEIGHT)
    {
        assert(APPLICATION == nullptr && "No more than one instance of Application system!");
        APPLICATION = this;
        init_success = false;

        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC | SDL_INIT_JOYSTICK | SDL_INIT_TIMER) < 0)
        {
            std::cerr << "SDL could not initialized! SDL_ERROR: "
                      << SDL_GetError() << std::endl;
            init_success = false;
        }

        else
        {
            //Use OpenGL 3.3 core
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
            SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
          
            //Create a window with OpenGL
            pWindow = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                       SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

            if (pWindow == nullptr)
            {
                std::cerr << "Window could not be created! SDL_ERROR: "
                          << SDL_GetError() << std::endl;
                init_success = false;
            }
            else
            {
                //Create context
                glContext = SDL_GL_CreateContext(pWindow);
                if (glContext == NULL)
                {
                    std::cerr << "OpenGL context could not be created! SDL_ERROR: "
                              << SDL_GetError() << std::endl;
                    init_success = false;
                }
            }
        }

        char* base_path = SDL_GetBasePath();
        std::string bp = base_path;
        IMAGE_DIR = bp + IMAGE_DIR_R;
        SOUND_DIR = bp + SOUND_DIR_R;
        ENGINE->LoadAssetLog();
        ENGINE->IMAGES = init_data_pipeline(IMAGE_DIR, PNG_REGEX);
        ENGINE->SOUNDS = init_data_pipeline(SOUND_DIR, SOUND_REGEX);
    }
    Application::~Application()
    {
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(pWindow);
        pWindow = nullptr;

        SDL_Quit();
    }
    void Application::Init()
    {
        padstatus = -1;
        pad_howtoplay_status = 0;
        pad = SDL_GameControllerOpen(0);
        joy = SDL_GameControllerGetJoystick(pad);
        gControllerHaptic = SDL_HapticOpenFromJoystick(joy);
        instanceID = SDL_JoystickInstanceID(joy);
        SDL_HapticRumbleInit(gControllerHaptic);
        left_padpos = glm::vec2(0, 0);
        right_padpos = glm::vec2(0, 0);
        enterthecode = false;
        pausePadStatus = 0;
        pad_final_status = 0;
        isHowToPlayer = false;

    }
    void Application::Update(float deltaTime)
    {
        Input::GetInstance().Reset();
        deltaTime = Timer::GetInstance().GetDeltaTime();

        PollEvents();
        UpdatePadStatus();
    }
    void Application::SwapWindow()
    {
        SDL_GL_SwapWindow(pWindow);
    }
    bool Application::VSync(bool on)
    {
        if (on)
        {
            if (SDL_GL_SetSwapInterval(on) < 0)
            {
                std::cerr << "Warning: Unable to set VSync! SDL_ERROR: "
                          << SDL_GetError() << std::endl;
                return false;
            }
            return true;
        }
        else
        {
            SDL_GL_SetSwapInterval(on);
            return false;
        }
    }
    glm::vec2 Application::screen_to_world(const glm::vec2& screen_coordinate)
    {

        glm::vec2 world(0.0);
        world.x = screen_coordinate.x;
        world.y = SCREEN_HEIGHT - screen_coordinate.y;

        float camera_width = 1280.f;
        float camera_height = 720.f;


        world.x = screen_coordinate.x * (camera_width / (float)SCREEN_WIDTH);
        world.x -= camera_width / 2.f;
        world.x /= GRAPHICS->FAR_Z_AXIS;

        world.y = -screen_coordinate.y * (camera_height / (float)SCREEN_HEIGHT);
        world.y += camera_height / 2.f;
        world.y /= GRAPHICS->FAR_Z_AXIS;

        return world;
    }

    void Application::PollEvents()
    {
        while (SDL_PollEvent(&SDL_event) != 0)
        {
            PollWindowEvent(SDL_event);
            if (isUsingGamepad && isGamePad())
            {
            	PollGamePadEvent(SDL_event);
            }
            else
            {
            	PollKeyboardEvent(SDL_event);
            }
            
            PollMouseEvent(SDL_event);
            ImGui_ImplSdlGL3_ProcessEvent(&SDL_event);
            
            if (SDL_event.type == SDL_WINDOWEVENT)
            {
                if (SDL_event.window.event == SDL_WINDOWEVENT_MINIMIZED)
                {
                	ENGINE->isPause = true;
                }
                if (SDL_event.window.event == SDL_WINDOWEVENT_RESTORED)
                {
                	ENGINE->isPause = false;
                }
            }
        }
    }
    void Application::PollWindowEvent(SDL_Event& currentEvent)
    {
        // Get the value of joystick
        if (currentEvent.jaxis.value < -800 || currentEvent.jaxis.value > 800)
        {
            if (currentEvent.jaxis.axis == 2)
            {
                right_padpos.x = currentEvent.jaxis.value;
            }
            else if (currentEvent.jaxis.axis == 4)
            {
                right_padpos.y = currentEvent.jaxis.value;
            }
            if (currentEvent.jaxis.value < -800 || currentEvent.jaxis.value > 800)
            {
                if (currentEvent.jaxis.axis == 0)
                {
                    left_padpos.x = currentEvent.jaxis.value;
                }
                else if (currentEvent.jaxis.axis == 1)
                {
                    left_padpos.y = currentEvent.jaxis.value;
                }
            }
        }
        if (currentEvent.type == SDL_WINDOWEVENT)
        {
            SDL_GetWindowSize(pWindow, &SCREEN_WIDTH, &SCREEN_HEIGHT);
        }
        else if (currentEvent.type == SDL_QUIT)
        {
            ENGINE->Quit();
        }
    }
    void Application::PollKeyboardEvent(SDL_Event& currentEvent)
    {
        switch (currentEvent.type)
        {
            case SDL_KEYDOWN:
                Input::GetInstance().SetKeyPressed(currentEvent.key.keysym.scancode, SDL_KEYDOWN);
                break;
            case SDL_KEYUP:
                Input::GetInstance().SetKeyPressed(currentEvent.key.keysym.scancode, SDL_KEYUP);
                break;
            default:
                break;
        }
    }
    void Application::PollMouseEvent(SDL_Event& currentEvent)
    {
        switch (currentEvent.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                Input::GetInstance().SetMousePressed(currentEvent.button.button, SDL_MOUSEBUTTONDOWN);
                break;
            case SDL_MOUSEBUTTONUP:
                Input::GetInstance().SetMousePressed(currentEvent.button.button, SDL_MOUSEBUTTONUP);
                break;
            default:
                break;
        }
    }
    void Application::PollGamePadEvent(SDL_Event& currentEvent)
    {
        switch (currentEvent.cbutton.type)
        {
            case SDL_CONTROLLERBUTTONDOWN:
                Input::GetInstance().SetGamepadPressed(currentEvent.cbutton.button, SDL_CONTROLLERBUTTONDOWN);
                break;
            case SDL_CONTROLLERBUTTONUP:
                Input::GetInstance().SetGamepadPressed(currentEvent.cbutton.button, SDL_CONTROLLERBUTTONUP);
                break;
            case SDL_CONTROLLERAXISMOTION:
                Input::GetInstance().SetGamepadPressed(currentEvent.cbutton.button, SDL_CONTROLLERAXISMOTION);
                break;
            default:
                break;
        }
    }
    bool Application::isGamePad()
    {
        for (int i = 0; i < SDL_NumJoysticks(); ++i)
        {
            if (SDL_IsGameController(i))
            {
                return true;
            }
        }
        return false;
    }

    void Application::UpdatePadStatus()
    {
        if (isUsingGamepad)
        {
            switch (GAME_STATE->current)
            {
                // To select lots of things in game. Check the status of pad
                case SL_MENU:
                    if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
                        padstatus++;
                    if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_DPAD_LEFT))
                        padstatus--;

                    if (padstatus < 1)
                    {
                        padstatus = 6;
                    }
                    if (padstatus > 6)
                    {
                        padstatus = 1;
                    }
                    break;
                case SL_LEVEL1:
                    if (OBJECT_FACTORY->GetObjectID(100)->is_in_Final == true)
                    {
                        enterthecode = true;
                    }
                    if (enterthecode)
                    {
                        pausePadStatus = -1;
                        if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
                            pad_final_status++;
                        if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_DPAD_LEFT))
                            pad_final_status--;
                        if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_DPAD_UP))
                            pad_final_status -= 3;
                        if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_DPAD_DOWN))
                            pad_final_status += 3;
                        if (pad_final_status < 0)
                        {
                            pad_final_status = 11;
                        }
                        if (pad_final_status > 11)
                        {
                            pad_final_status = 0;
                        }
                    }
                    if (ENGINE->isPause)
                    {
                        if (!enterthecode)
                        {
                            if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_DPAD_DOWN))
                                ++pausePadStatus;
                            if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_DPAD_UP))
                                --pausePadStatus;
                            if (pausePadStatus > 3)
                                pausePadStatus = 0;
                            if (pausePadStatus < 0)
                                pausePadStatus = 3;
                        }
                    }
                    break;
                case SL_OPTION:
                    if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_DPAD_DOWN))
                        padstatus++;
                    if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_DPAD_UP))
                        padstatus--;

                    if (padstatus < 18)
                    {
                        padstatus = 20;
                    }
                    if (padstatus > 20)
                    {
                        padstatus = 18;
                    }
                    break;
            }
        }
    }
}
