/**
\file        PlayerController.cpp
\author      Chiho Kwon
\par         email: erpo0811@gmail.com
\par         course: GAM200
\date        12/15/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "PlayerController.h"
#include "Collision.h"
#include "GameStateManager.h"
#include "Graphics.h"
#include "JsonWriter.h"
#include "Object.h"
#include "ObjectFactory.h"
#include "PlayerLogic.h"
#include "RigidBody.h"
#include "SoundManager.h"
#include "Sprite.h"
#include "Transform.hpp"
#include "ZombieController.h"
#include "imgui.h"
#include "jsonReader.h"
#include <iostream>
#include "SoundManager.h"
#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#define STATUSBARSIZE 250.0f;
#define ARMORSTATUS 100.0f
namespace FindersEngine
{
    float PlayerController::player_health = 300;
    float PlayerController::player_armor = 100;
    Timer PlayerController::timer;
    bool PlayerController::isReachedSaveZone = false;

    PlayerController::PlayerController()
    {
    }

    PlayerController::~PlayerController()
    {
    }

    void PlayerController::Init()
    {
        ORIGIN_PLAYER_HEALTH = player_health;
        isReachedSaveZone = false;
        ORIGIN_PLAYER_ARMOR = 0;
        Hpbarpos = glm::vec3(0.0f, 0.0f, 0.0f);
        player_experience = 0;
        player_expTimer = 0.f;
        padtarget_direction = glm::vec2(0.f, 0.f);
        left_pad = glm::vec2(0.f, 0.f);
        transform = dynamic_cast<Transform*>(GetOwner()->GetComponent(CT_TRANSFORM));
        rigidbody = dynamic_cast<RigidBody*>(GetOwner()->GetComponent(CT_RIGID_BODY));
        collision = dynamic_cast<Collision*>(GetOwner()->GetComponent(CT_COLLISION));
        player_pos = transform->getPosition();
        light_lifeTime = 0.3f;

        HPbar = OBJECT_FACTORY->CreateEmptyObject(3500);
        Armorbar = OBJECT_FACTORY->CreateEmptyObject(3501);

        HPbartransform = new Transform();
        HPbartransform->setPosition(transform->getPosition());
        HPbartransform->setScale(glm::vec3(250.f, 30.f, 0.f));

        HPbarsprite = new Sprite();
        HPbarsprite->LoadTexture("PIN_HPBAR.png");
        HPbar->AddComponent(HPbartransform);
        HPbar->AddComponent(HPbarsprite);
        HPbar->Init();

        Armorbartransform = new Transform();
        Armorbartransform->setPosition(transform->getPosition());
        Armorbartransform->setScale(glm::vec3(250.f, 30.f, 0.f));

        Armorbarsprite = new Sprite();
        Armorbarsprite->LoadTexture("PIN_ARMORBAR.png");
        Armorbar->AddComponent(Armorbartransform);
        Armorbar->AddComponent(Armorbarsprite);

        Armorbar->Init();

        ratio_HPbar = player_health / STATUSBARSIZE;
        ratio_Armorbar = ARMORSTATUS / STATUSBARSIZE;

        timer.Init();
    }

	void PlayerController::Update(float deltaTime)
	{
		glm::vec3 rot = transform->getRotation();
		float radian = rot.z;

		if (Input::GetInstance().IsTriggered(SDL_SCANCODE_E) || Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_B))
		{
			GRAPHICS->HandLightSwitch();
		}
		if (GRAPHICS->IsHandLight())
		{
			GRAPHICS->set_light_angle(radian);
		}
		if (shoot_elapsed_time > 0.0f)
		{
			shoot_elapsed_time -= deltaTime;
		}
		else
		{
			shoot_elapsed_time = 0.0f;
		}
		if (transform->GetOwner()->room_number == 3 || transform->GetOwner()->room_number == 4)
		{
			SOUNDMANAGER->playwithtime("ZOMBIE_EXIST_SOUND.wav", 2);
		}
		if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
		{
			if (is_ammo_cheat_on)
			{
				SOUNDMANAGER->play("SHOOTING_SOUND.wav");
				PLAYERLOGIC->ShootBullet(transform, 2000.f);
				PLAYERLOGIC->isShoot = true;
				isInitShootTime = true;
				if (light_lifeTime > 0.f)
				{
					GRAPHICS->set_light_angle(radian);
				}
			}
			if (transform->GetOwner()->curr_ammo > 0 && transform->GetOwner()->is_get_pistol)
			{
				SOUNDMANAGER->play("SHOOTING_SOUND.wav");
				PLAYERLOGIC->ShootBullet(transform, 2000.f);
				PLAYERLOGIC->isShoot = true;
				isInitShootTime = true;
			}
			else
			{
				PLAYERLOGIC->isShoot = false;
				SOUNDMANAGER->play("DRY_GUN_SOUND.mp3");
			}
			if (light_lifeTime > 0.f)
			{
				GRAPHICS->set_light_angle(radian);
			}
		}
		if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER))
		{
			if (is_ammo_cheat_on)
			{
				SOUNDMANAGER->play("SHOOTING_SOUND.wav");
				PLAYERLOGIC->ShootBulletWithPad(transform, 2000.f);
				PLAYERLOGIC->isShoot = true;
				isInitShootTime = true;
				if (light_lifeTime > 0.f)
				{
					GRAPHICS->set_light_angle(radian);
				}
			}
			if (transform->GetOwner()->curr_ammo > 0 && transform->GetOwner()->is_get_pistol)
			{
				SOUNDMANAGER->play("SHOOTING_SOUND.wav");
				PLAYERLOGIC->ShootBulletWithPad(transform, 2000.f);
				PLAYERLOGIC->isShoot = true;
				isInitShootTime = true;
			}
			else
			{
				PLAYERLOGIC->isShoot = false;
				SOUNDMANAGER->play("DRY_GUN_SOUND.mp3");
			}
			if (light_lifeTime > 0.f)
			{
				GRAPHICS->set_light_angle(radian);
			}
		}
		if (deltaTime)
		{
			//800 consider the height and width
			HPbartransform->setScale(glm::vec3((1.0f / ratio_HPbar) * player_health, 30.f, 0.f));
			Hpbarpos.x = -((1.0f / ratio_HPbar) * (ORIGIN_PLAYER_HEALTH - player_health)) / 2.0f / 800.0f;
			Hpbarpos.y = 0.17f;


			Armorbartransform->setScale(glm::vec3((1.0f / ratio_Armorbar) * player_armor, 30.f, 0.f));
			Armorbarpos.x = -((1.0f / ratio_Armorbar) * (ARMORSTATUS - player_armor)) / 2.0f / 800.0f;
			Armorbarpos.y = 0.13f;

			if (!HPbartransform)
				HPbar->AddComponent(HPbartransform);
			if (!Armorbartransform)
				Armorbar->AddComponent(Armorbartransform);

			HPbartransform->setPosition(transform->getPosition() + Hpbarpos);
			Armorbartransform->setPosition(transform->getPosition() + Armorbarpos);

			glm::vec3 rot = transform->getRotation();

			Movement(deltaTime);
			if (isDead())
				GAME_STATE->SetNextState(SL_LOSE);

			if (APPLICATION->isUsingGamepad && APPLICATION->isGamePad())
			{
				PLAYERLOGIC->pad_rotation(transform);
			}
			else
			{
				PLAYERLOGIC->mouse_rotation(transform);
			}
		}

		if (transform->getPosition().x > -2 && transform->getPosition().x < 2 &&
			transform->getPosition().y < 2 && transform->getPosition().y > -2)
		{
			isReachedSaveZone = true;
			JSONWRITER->setPlayerData(transform);
			JSONWRITER->jsonWriterMain();
		}
	}

    void PlayerController::Movement(float deltaTime)
    {
        if (!APPLICATION->isUsingGamepad)
        {
            if (Input::GetInstance().IsPressed(SDL_SCANCODE_W))
            {
                SOUNDMANAGER->playwithtime("FOOT_STEP_SOUND.wav", 0.3f);
                rigidbody->pm_vel = glm::vec3(0.f, 1.f, 0.f);
                if (Input::GetInstance().IsPressed(SDL_SCANCODE_D))
                {
                    rigidbody->pm_vel = glm::vec3(0.7f, 0.7f, 0.f);
                    SOUNDMANAGER->playwithtime("FOOT_STEP_SOUND.wav", 0.3f);
                }
                else if (Input::GetInstance().IsPressed(SDL_SCANCODE_A))
                {
                    rigidbody->pm_vel = glm::vec3(-0.7f, 0.7f, 0.f);
                    SOUNDMANAGER->playwithtime("FOOT_STEP_SOUND.wav", 0.3f);
                }
            }
            else if (Input::GetInstance().IsPressed(SDL_SCANCODE_S))
            {
                SOUNDMANAGER->playwithtime("FOOT_STEP_SOUND.wav", 0.3f);
                rigidbody->pm_vel = glm::vec3(0.f, -1.f, 0.f);
                if (Input::GetInstance().IsPressed(SDL_SCANCODE_D))
                {
                    rigidbody->pm_vel = glm::vec3(0.7f, -0.7f, 0.f);
                    SOUNDMANAGER->playwithtime("FOOT_STEP_SOUND.wav", 0.3f);
                }
                else if (Input::GetInstance().IsPressed(SDL_SCANCODE_A))
                {
                    rigidbody->pm_vel = glm::vec3(-0.7f, -0.7f, 0.f);
                    SOUNDMANAGER->playwithtime("FOOT_STEP_SOUND.wav", 0.3f);
                }
            }

            if (Input::GetInstance().IsPressed(SDL_SCANCODE_D))
            {
                SOUNDMANAGER->playwithtime("FOOT_STEP_SOUND.wav", 0.3f);
                rigidbody->pm_vel = glm::vec3(1.f, 0.f, 0.f);
                if (Input::GetInstance().IsPressed(SDL_SCANCODE_W))
                {
                    rigidbody->pm_vel = glm::vec3(0.7f, 0.7f, 0.f);
                    SOUNDMANAGER->playwithtime("FOOT_STEP_SOUND.wav", 0.3f);
                }
                else if (Input::GetInstance().IsPressed(SDL_SCANCODE_S))
                {
                    rigidbody->pm_vel = glm::vec3(0.7f, -0.7f, 0.f);
                    SOUNDMANAGER->playwithtime("FOOT_STEP_SOUND.wav", 0.3f);
                }
            }
            else if (Input::GetInstance().IsPressed(SDL_SCANCODE_A))
            {
                SOUNDMANAGER->playwithtime("FOOT_STEP_SOUND.wav", 0.3f);
                rigidbody->pm_vel = glm::vec3(-1.f, 0.f, 0.f);
                if (Input::GetInstance().IsPressed(SDL_SCANCODE_W))
                {
                    rigidbody->pm_vel = glm::vec3(-0.7f, 0.7f, 0.f);
                    SOUNDMANAGER->playwithtime("FOOT_STEP_SOUND.wav", 0.3f);
                }
                else if (Input::GetInstance().IsPressed(SDL_SCANCODE_S))
                {
                    rigidbody->pm_vel = glm::vec3(-0.7f, -0.7f, 0.f);
                    SOUNDMANAGER->playwithtime("FOOT_STEP_SOUND.wav", 0.3f);
                }
            }
        }

        if (APPLICATION->isUsingGamepad)
        {
            left_pad = APPLICATION->get_left_pad();
            left_pad = APPLICATION->screen_to_world(left_pad);
            padtarget_direction = glm::normalize(left_pad);
            float length_pad = glm::length(left_pad);

            if (left_pad.x > 6500.f || left_pad.y > 6500.f)
            {
                rigidbody->pm_vel = glm::vec3(padtarget_direction.x * 1.15f, padtarget_direction.y * 1.15f, 0.f);
                SOUNDMANAGER->playwithtime("FOOT_STEP_SOUND.wav", 0.3f);
            }
            else if (left_pad.x < -6500.f || left_pad.y < -6500.f)
            {
                rigidbody->pm_vel = glm::vec3(padtarget_direction.x * 1.15f, padtarget_direction.y * 1.15f, 0.f);
                SOUNDMANAGER->playwithtime("FOOT_STEP_SOUND.wav", 0.3f);
            }
        }
    }
    bool PlayerController::isDead()
    {
        if (player_health <= 0.0f)
        {
			SOUNDMANAGER->play("PLAYER_DIED_SOUND.wav");
            SDL_HapticRumblePlay(APPLICATION->gControllerHaptic, 10.f, 500);
            if (!isReachedSaveZone)
                GAME_STATE->next = SL_LOSE;
            return true;
        }

        return false;
    }

	void PlayerController::GetDamage()
	{
		if (timer.GetTime() > 1)
		{
			SDL_HapticRumblePlay(APPLICATION->gControllerHaptic, 0.7f, 50);
			SOUNDMANAGER->play("PLAYER_HITTED_SOUND.mp3");
                        SDL_HapticRumblePlay(APPLICATION->gControllerHaptic, 1.f, 75);
			OBJECT_FACTORY->GetObjectID(100)->is_getdamage = true;
			player_health -= 40.0f;
			timer.Init();
		}
	}
}
