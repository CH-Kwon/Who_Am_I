/**
\file        ButtonController.cpp
\author      Chiho Kwon
\par         email: erpo0811@gmail.com
\par         course: GAM200
\date        12/15/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "ButtonController.h"
#include "Collision.h"
#include "Engine.h"
#include "GameStateManager.h"
#include "Hud.h"
#include "Input.h"
#include "Object.h"
#include "ObjectFactory.h"
#include "ObjectGenerator.h"
#include "RigidBody.h"
#include "SoundManager.h"
#include "Transform.hpp"
#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

namespace FindersEngine
{
    namespace
    {
        //bool isHowToPlayer = false;
        glm::vec4 white(1.0f, 1.0f, 1.0f, 1.0f);
        glm::vec4 red(1.0f, 0.0f, 0.0f, 1.0f);
        glm::vec4 blue(0.0f, 0.0f, 1.0f, 1.0f);
    };
    using namespace glm;

    Object* keyboardmouse;
    Object* back;
    Object* keyinfo;
    Object* h_playbg;

    ButtonController::ButtonController()
    {
    }

    ButtonController::~ButtonController()
    {
    }

    void ButtonController::Init()
    {
        keyboardmouse = nullptr;
        back = nullptr;
        keyinfo = nullptr;
        h_playbg = nullptr;
        transform = dynamic_cast<Transform*>(GetOwner()->GetComponent(CT_TRANSFORM));
        hud = dynamic_cast<Hud*>(GetOwner()->GetComponent(CT_HUD));
        hud->RGBA_Color(red);
        collision = dynamic_cast<Collision*>(GetOwner()->GetComponent(CT_COLLISION));
        index = 0;
    }

    void ButtonController::Update(float deltaTime)
    {
        float screen_width = 1280.f;
        float screen_height = 720.f;

        if (collision->MouseRectCollisionCheck(collision->GetOwner()))
        {

           // hud->RGBA_Color(blue);
            if (getName() == "StartButton")
            {
                hud->RGBA_Color(blue);
                if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    GAME_STATE->SetNextState(SL_LEVEL1);
                }
            }
            if (getName() == "OptionButton")
            {
                hud->RGBA_Color(blue);
                if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    GAME_STATE->SetNextState(SL_OPTION);
                }
            }
            if (getName() == "HowToPlayButton")
            {
                hud->RGBA_Color(blue);
                if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    GAME_STATE->SetNextState(SL_HOWTOPLAY);
                }
            }

            if (getName() == "QuitButton")
            {
                hud->RGBA_Color(blue);
                if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    ENGINE->Quit();
                }
            }
            if (getName() == "GoToMenu")
            {
                hud->RGBA_Color(blue);
                if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    GAME_STATE->SetNextState(SL_MENU);
                }
            }
            if (getName() == "BackToMenu" && !APPLICATION->isHowToPlayer)
            {
                hud->RGBA_Color(blue);
                if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    if (ENGINE->isPause == true)
                    {
                        ENGINE->isPause = false;
                    }
                    GAME_STATE->SetNextState(SL_MENU);
                }
            }
            if (getName() == "Back")
            {
                hud->RGBA_Color(blue);
                if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    OBJECT_FACTORY->Destroy(OBJECT_FACTORY->GetObjectID(7002));
                    OBJECT_FACTORY->Destroy(OBJECT_FACTORY->GetObjectID(7000));
                    OBJECT_FACTORY->Destroy(OBJECT_FACTORY->GetObjectID(7001));
                    OBJECT_FACTORY->Destroy(OBJECT_FACTORY->GetObjectID(3677));
                    APPLICATION->isHowToPlayer = false;
                    OBJECT_FACTORY->Destroy(OBJECT_FACTORY->GetObjectID(7901));
                }
            }
            if (getName() == "Resume" && !APPLICATION->isHowToPlayer)
            {
                hud->RGBA_Color(blue);
                if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    if (ENGINE->isPause)
                    {
                        ENGINE->isPause = false;
                        ENGINE->isResume = true;
                    }
                }
            }
            if (getName() == "H_Play" && !APPLICATION->isHowToPlayer)
            {
                hud->RGBA_Color(blue);
                if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    OBJECT_GEN->CreateHud(vec3(screen_width / 2.f, screen_height / 2.f, 0.f), glm::vec3(screen_width * 1.2f, screen_height * 1.2f, 0.f), 3677, "PIN_HBG.png", LO_1);
                    OBJECT_GEN->CreateKeyinfo(vec3(screen_width / 2.0f, screen_height / 2.0f - 50, 0), glm::vec3(screen_width / 2, screen_height / 2, 0.f), 7000, "PIN_KEYBOARDMOUSE.png", LO_1);
                    OBJECT_GEN->CreateButton(vec3(screen_width / 8.0f - 50, screen_height / 1.2f, 0), glm::vec3(screen_width / 12, screen_height / 12, 0.f), 7001, "PIN_BACK.png", "Back", LO_1);
                    OBJECT_GEN->CreateButton(vec3(screen_width / 1.0f - 100, screen_height / 1.2f, 0), glm::vec3(screen_width / 12, screen_height / 12, 0.f), 7901, "PIN_GONEXT.png", "GoGamePad", LO_1);
                    keyboardmouse = OBJECT_GEN->CreateKeyboardMouse(vec3(screen_width / 1.1f - 40, screen_height / 2.f, 0), glm::vec3(screen_width / 5, screen_height / 4, 0.f), 7002, "PIN_KEYINFO.png", LO_1);
                    APPLICATION->isHowToPlayer= true;
                }
            }
            
            if (getName() == "CreditButton")
            {
                hud->RGBA_Color(blue);
                if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    GAME_STATE->SetNextState(SL_CREDIT);
                }
            }
            if (collision->GetOwner()->GetObjectID() == 3000)
            {
		if (hud->get_RGBA_Color() != blue)
		{
			SOUNDMANAGER->play("SELECT_SOUND.wav");
		}
                hud->RGBA_Color(blue);
                if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    GAMELOGIC->GetSecretNumber((char)'1', index);
                    hud->RGBA_Color(red);
                    index++;
                }
            }
            else if (collision->GetOwner()->GetObjectID() == 3001)
            {
				if (hud->get_RGBA_Color() != blue)
				{
					SOUNDMANAGER->play("SELECT_SOUND.wav");
				}
                hud->RGBA_Color(blue);
                if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    GAMELOGIC->GetSecretNumber((char)'2', index);
                    index++;
                    hud->RGBA_Color(red);
                }
            }
            else if (collision->GetOwner()->GetObjectID() == 3002)
            {
				if (hud->get_RGBA_Color() != blue)
				{
					SOUNDMANAGER->play("SELECT_SOUND.wav");
				}
                hud->RGBA_Color(blue);
                if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    GAMELOGIC->GetSecretNumber((char)'3', index);
                    index++;
                    hud->RGBA_Color(red);
                }
            }
            else if (collision->GetOwner()->GetObjectID() == 3003)
            {
				if (hud->get_RGBA_Color() != blue)
				{
					SOUNDMANAGER->play("SELECT_SOUND.wav");
				}
                hud->RGBA_Color(blue);
                if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    GAMELOGIC->GetSecretNumber((char)'4', index);
                    index++;
                    hud->RGBA_Color(red);
                }
            }
            else if (collision->GetOwner()->GetObjectID() == 3004)
            {
				if (hud->get_RGBA_Color() != blue)
				{
					SOUNDMANAGER->play("SELECT_SOUND.wav");
				}
                hud->RGBA_Color(blue);
                if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    GAMELOGIC->GetSecretNumber((char)'5', index);
                    index++;
                    hud->RGBA_Color(red);
                }
            }
            else if (collision->GetOwner()->GetObjectID() == 3005)
            {
				if (hud->get_RGBA_Color() != blue)
				{
					SOUNDMANAGER->play("SELECT_SOUND.wav");
				}
                hud->RGBA_Color(blue);
                if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    GAMELOGIC->GetSecretNumber((char)'6', index);
                    index++;
                    hud->RGBA_Color(red);
                }
            }
            else if (collision->GetOwner()->GetObjectID() == 3006)
            {
				if (hud->get_RGBA_Color() != blue)
				{
					SOUNDMANAGER->play("SELECT_SOUND.wav");
				}
                hud->RGBA_Color(blue);
                if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    GAMELOGIC->GetSecretNumber((char)'7', index);
                    index++;
                    hud->RGBA_Color(red);
                }
            }
            else if (collision->GetOwner()->GetObjectID() == 3007)
            {
				if (hud->get_RGBA_Color() != blue)
				{
					SOUNDMANAGER->play("SELECT_SOUND.wav");
				}
                hud->RGBA_Color(blue);
                if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    GAMELOGIC->GetSecretNumber((char)'8', index);
                    index++;
                    hud->RGBA_Color(red);
                }
            }
            else if (collision->GetOwner()->GetObjectID() == 3008)
            {
				if (hud->get_RGBA_Color() != blue)
				{
					SOUNDMANAGER->play("SELECT_SOUND.wav");
				}
                hud->RGBA_Color(blue);
                if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    GAMELOGIC->GetSecretNumber((char)'9', index);
                    index++;
                    hud->RGBA_Color(red);
                }
            }
            else if (collision->GetOwner()->GetObjectID() == 3009)
            {
				if (hud->get_RGBA_Color() != blue)
				{
					SOUNDMANAGER->play("SELECT_SOUND.wav");
				}
                hud->RGBA_Color(blue);
                if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    GAMELOGIC->GetSecretNumber((char)'*', index);
                    index++;
                    hud->RGBA_Color(red);
                }
            }
            else if (collision->GetOwner()->GetObjectID() == 3010)
            {
				if (hud->get_RGBA_Color() != blue)
				{
					SOUNDMANAGER->play("SELECT_SOUND.wav");
				}
                hud->RGBA_Color(blue);
                if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    GAMELOGIC->GetSecretNumber((char)'0', index);
                    index++;
                    hud->RGBA_Color(red);
                }
            }
            else if (collision->GetOwner()->GetObjectID() == 3011)
            {
				if (hud->get_RGBA_Color() != blue)
				{
					SOUNDMANAGER->play("SELECT_SOUND.wav");
				}
                hud->RGBA_Color(blue);
                if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
                {
                    GAMELOGIC->GetSecretNumber((char)'#', index);
                    index++;
                    hud->RGBA_Color(red);
                }
            }
        }
        else
        {
            hud->RGBA_Color(white);
        }

        if (GetOwner()->GetObjectID() == APPLICATION->pad_final_status + 3000)
        {
            APPLICATION->padstatus = -1;
            if (hud->get_RGBA_Color() != blue)
            {
                SOUNDMANAGER->play("SELECT_SOUND.wav");
            }
            hud->RGBA_Color(blue);
            if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_A))
            {
                if (APPLICATION->pad_final_status == 0)
                {
                    GAMELOGIC->GetSecretNumber((char)'1', index);
                    hud->RGBA_Color(red);
                    index++;
                }
                if (APPLICATION->pad_final_status == 1)
                {
                    GAMELOGIC->GetSecretNumber((char)'2', index);
                    index++;
                    hud->RGBA_Color(red);
                }
                if (APPLICATION->pad_final_status == 2)
                {
                    GAMELOGIC->GetSecretNumber((char)'3', index);
                    index++;
                    hud->RGBA_Color(red);
                }
                if (APPLICATION->pad_final_status == 3)
                {
                    GAMELOGIC->GetSecretNumber((char)'4', index);
                    index++;
                    hud->RGBA_Color(red);
                }
                if (APPLICATION->pad_final_status == 4)
                {
                    GAMELOGIC->GetSecretNumber((char)'5', index);
                    index++;
                    hud->RGBA_Color(red);
                }
                if (APPLICATION->pad_final_status == 5)
                {
                    GAMELOGIC->GetSecretNumber((char)'6', index);
                    index++;
                    hud->RGBA_Color(red);
                }
                if (APPLICATION->pad_final_status == 6)
                {
                    GAMELOGIC->GetSecretNumber((char)'7', index);
                    index++;
                    hud->RGBA_Color(red);
                }
                if (APPLICATION->pad_final_status == 7)
                {
                    GAMELOGIC->GetSecretNumber((char)'8', index);
                    index++;
                    hud->RGBA_Color(red);
                }
                if (APPLICATION->pad_final_status == 8)
                {
                    GAMELOGIC->GetSecretNumber((char)'9', index);
                    index++;
                    hud->RGBA_Color(red);
                }
                if (APPLICATION->pad_final_status == 9)
                {
                    GAMELOGIC->GetSecretNumber((char)'*', index);
                    index++;
                    hud->RGBA_Color(red);
                }
                if (APPLICATION->pad_final_status == 10)
                {
                    GAMELOGIC->GetSecretNumber((char)'0', index);
                    index++;
                    hud->RGBA_Color(red);
                }
                if (APPLICATION->pad_final_status == 11)
                {
                    GAMELOGIC->GetSecretNumber((char)'#', index);
                    index++;
                    hud->RGBA_Color(red);
                }
            }
        }

        if (index > 3)
        {
            index = 0;
        }

        ///////////////////// GAME PAD VERSION /////////////////////
        if (APPLICATION->isUsingGamepad)
        {
                if (APPLICATION->padstatus == 1)
                {
                    if (getName() == "StartButton")
                    {
                        hud->RGBA_Color(blue);
                        if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_A))
                        {
                            GAME_STATE->SetNextState(SL_LEVEL1);
                        }
                    }
                }
                if (APPLICATION->padstatus == 2)
                {
                    if (getName() == "OptionButton")
                    {
                        hud->RGBA_Color(blue);
                        if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_A))
                        {
                            GAME_STATE->SetNextState(SL_OPTION);
                        }
                    }
                }
                if (APPLICATION->padstatus == 3)
                {
                    if (getName() == "CreditButton")
                    {
                        hud->RGBA_Color(blue);
                        if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_A))
                        {
                            GAME_STATE->SetNextState(SL_CREDIT);
                        }
                    }
                }
                if (APPLICATION->padstatus == 4)
                {
                    if (getName() == "HowToPlayButton")
                    {
                        hud->RGBA_Color(blue);
                        if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_A))
                        {
                            GAME_STATE->SetNextState(SL_HOWTOPLAY);
                        }
                    }
                }

                if (APPLICATION->padstatus == 5)
                {
                    if (getName() == "QuitButton")
                    {
                        hud->RGBA_Color(blue);
                        if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_A))
                        {
                            ENGINE->Quit();
                        }
                    }
                }
                if (APPLICATION->padstatus == 6)
                {
                    if (getName() == "Back")
                    {
                        hud->RGBA_Color(blue);
                        if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_A))
                        {
                            OBJECT_FACTORY->Destroy(keyinfo);
                            OBJECT_FACTORY->Destroy(keyboardmouse);
                            OBJECT_FACTORY->Destroy(back);
                            OBJECT_FACTORY->Destroy(h_playbg);
                        }
                    }
                }
                if (APPLICATION->pausePadStatus == 0)
                {
                    if (getName() == "Resume")
                    {
                        hud->RGBA_Color(blue);
                        if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_A))
                        {
                            ENGINE->isPause = false;
                            ENGINE->isResume = true;
                            APPLICATION->pausePadStatus = 0;
                        }
                    }
                }
                if (APPLICATION->pausePadStatus == 1)
                {
                    if (getName() == "BackToMenu")
                    {
                        hud->RGBA_Color(blue);
                        if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_A))
                        {
                            if (ENGINE->isPause == true)
                            {
                                ENGINE->isPause = false;
                                APPLICATION->pausePadStatus = 0;
                            }
                            GAME_STATE->SetNextState(SL_MENU);
                        }
                    }
                }
                if (APPLICATION->pausePadStatus == 2)
                {
                    if ((getName() == "H_Play") && (!APPLICATION->isHowToPlayer))
                    {
                        hud->RGBA_Color(blue);
                        if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_A))
                        {
                            OBJECT_GEN->CreateHud(vec3(screen_width, screen_height, 0), glm::vec3(screen_width * 3, screen_height * 3, 0.f), 3678, "PIN_H_BACKGROUND.png", LO_2);
                            OBJECT_GEN->CreateHud(vec3(screen_width / 2 + 100, screen_height / 2, 0), glm::vec3(screen_width, screen_height, 0.f), 3679, "PIN_GAMEPAD.png", LO_2);
                            OBJECT_GEN->CreateButton(vec3(screen_width / 8.0f - 50, screen_height / 2.f, 0), glm::vec3(screen_width / 11, screen_height / 11, 0.f), 1018, "PIN_H_BACK.png", "h_back", LO_2);
                            APPLICATION->isHowToPlayer = true;
                        }
                    }
                }
                if (APPLICATION->pausePadStatus == 3)
                {
                    if (getName() == "QuitButton")
                    {
                        hud->RGBA_Color(blue);
                        if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_A))
                        {
                            ENGINE->Quit();
                        }
                    }
                }
                if (APPLICATION->isHowToPlayer)
                {
                    if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_B))
                    {
                        OBJECT_FACTORY->Destroy(OBJECT_FACTORY->GetObjectID(3678));
                        OBJECT_FACTORY->Destroy(OBJECT_FACTORY->GetObjectID(3679));
                        OBJECT_FACTORY->Destroy(OBJECT_FACTORY->GetObjectID(1018));
                        APPLICATION->isHowToPlayer = false;
                    }
                }

                if (h_playbg != nullptr)
                {
                    if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_B))
                    {
                        h_playbg->Destroy(h_playbg);
                        keyinfo->Destroy(keyinfo);
                        back->Destroy(back);
                        keyboardmouse->Destroy(keyboardmouse);
                    }
                }
        }
    }
}
