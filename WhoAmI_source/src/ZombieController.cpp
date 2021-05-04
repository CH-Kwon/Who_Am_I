/**
\file        ZombieController.cpp
\author      Changuk Lee
\par         email: leechanguk0510@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "ZombieController.h"
#include "Collision.h"
#include "Headers_Systems.h"
#include "Input.h"
#include "Object.h"
#include "ObjectFactory.h"
#include "Physics.h"
#include "PlayerLogic.h"
#include "SoundManager.h"
#include "Sprite.h"
#include <PlayerController.h>
#include <iostream>

#define PI 3.14159265358979323846
#define DEG_TO_RAD (PI / 180.0)

namespace FindersEngine
{

    ZombieController::ZombieController()
    {
    }

    FindersEngine::ZombieController::ZombieController(float rotate, int direction)
    {
        rot.z = rotate;
        Direction = direction;
    }

    ZombieController::~ZombieController()
    {
    }

    void ZombieController::Init()
    {
        health = 30;
        experience = 0;
        expTimer = 0.f;
		isdetect = false;
        transform = dynamic_cast<Transform*>(GetOwner()->GetComponent(CT_TRANSFORM));
        rigidbody = dynamic_cast<RigidBody*>(GetOwner()->GetComponent(CT_RIGID_BODY));
        collision = dynamic_cast<Collision*>(GetOwner()->GetComponent(CT_COLLISION));
        playertransform = dynamic_cast<Transform*>(OBJECT_FACTORY->GetObjectID(100)->GetComponent(CT_TRANSFORM));
        playerrigidbody = dynamic_cast<RigidBody*>(OBJECT_FACTORY->GetObjectID(100)->GetComponent(CT_RIGID_BODY));

        /////////////
        Zombiedetect = OBJECT_FACTORY->CreateEmptyObject(GetOwner()->GetObjectID() + 500);

        Zombiedetecttrans = new Transform();
        Zombiedetecttrans->setPosition(transform->getPosition());
        Zombiedetecttrans->setScale(glm::vec3(0, 0, 0));

        Zombiedetectsprite = new Sprite();
        Zombiedetectsprite->LoadTexture("PIN_WARNING.png");

        Zombiedetect->AddComponent(Zombiedetecttrans);
        Zombiedetect->AddComponent(Zombiedetectsprite);
        Zombiedetect->Init();

        ///////////////
        ZombieHealth1 = OBJECT_FACTORY->CreateEmptyObject(GetOwner()->GetObjectID() + 600);

        ZombieHealth1trans = new Transform();
        ZombieHealth1trans->setPosition(transform->getPosition());
        ZombieHealth1trans->setScale(glm::vec3(50, 30, 10));

        ZombieHealth1sprite = new Sprite();
        ZombieHealth1sprite->LoadTexture("PIN_HPBAR.png");

        ZombieHealth1->AddComponent(ZombieHealth1trans);
        ZombieHealth1->AddComponent(ZombieHealth1sprite);
        ZombieHealth1->Init();
        ///////////////

        ZombieHealth2 = OBJECT_FACTORY->CreateEmptyObject(GetOwner()->GetObjectID() + 700);

        ZombieHealth2trans = new Transform();
        ZombieHealth2trans->setPosition(transform->getPosition());
        ZombieHealth2trans->setScale(glm::vec3(50, 30, 10));

        ZombieHealth2sprite = new Sprite();
        ZombieHealth2sprite->LoadTexture("PIN_HPBAR.png");

        ZombieHealth2->AddComponent(ZombieHealth2trans);
        ZombieHealth2->AddComponent(ZombieHealth2sprite);
        ZombieHealth2->Init();

        ///////////////
        ZombieHealth3 = OBJECT_FACTORY->CreateEmptyObject(GetOwner()->GetObjectID() + 800);

        ZombieHealth3trans = new Transform();
        ZombieHealth3trans->setPosition(transform->getPosition());
        ZombieHealth3trans->setScale(glm::vec3(50, 30, 10));

        ZombieHealth3sprite = new Sprite();
        ZombieHealth3sprite->LoadTexture("PIN_HPBAR.png");

        ZombieHealth3->AddComponent(ZombieHealth3trans);
        ZombieHealth3->AddComponent(ZombieHealth3sprite);
        ZombieHealth3->Init();


        timer.Init();
    }

    void ZombieController::Update(float dt)
    {
        Movement(dt);
        Zombiedetecttrans->setPosition(transform->getPosition() + glm::vec3(0.07, 0.0, 0));
        ZombieHealth1trans->setPosition(transform->getPosition() + glm::vec3(-0.07, 0.1, 0));
        ZombieHealth2trans->setPosition(transform->getPosition() + glm::vec3(0, 0.1, 0));
        ZombieHealth3trans->setPosition(transform->getPosition() + glm::vec3(0.07, 0.1, 0));
        if (GetOwner()->is_attack == true)
        {
            PlayerController::GetDamage();
            GetOwner()->is_attack = false;

        }
        if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
        {
            if (PLAYERLOGIC->isShoot == true)
            {
                if (collision->RayCastCollisionCheck(playertransform->GetOwner(), 100.f))
                {
                    if (GetOwner()->is_collide == true)
                    {
                        health -= 10;
                        SOUNDMANAGER->play("ZOMBIE_HURT_SOUND.wav");
                        rigidbody->CollisionResponseWithBullet(playerrigidbody, rigidbody);

                        if (ZombieHealth3trans->getScale().x != 0 || ZombieHealth3trans->getScale().y != 0)
                        {
                            ZombieHealth3trans->setScale(glm::vec3(0, 0, 0));
                        }
                        else if ((ZombieHealth2trans->getScale().x != 0 || ZombieHealth2trans->getScale().y != 0))
                        {
                            ZombieHealth2trans->setScale(glm::vec3(0, 0, 0));
                        }
                        else if ((ZombieHealth1trans->getScale().x != 0 || ZombieHealth1trans->getScale().y != 0))
                        {
                            ZombieHealth1trans->setScale(glm::vec3(0, 0, 0));
                        }
                    }
                    GetOwner()->is_collide = false;
                }
            }
        }
        else if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER))
        {
            if (PLAYERLOGIC->isShoot == true)
            {
                if (collision->RayCastCollisionCheckForPad(playertransform->GetOwner(), 100.f))
                {
                    if (GetOwner()->is_collide == true)
                    {
                        health -= 10;
                        SOUNDMANAGER->play("ZOMBIE_HURT_SOUND.wav");
                        if (ZombieHealth3trans->getScale().x != 0 || ZombieHealth3trans->getScale().y != 0)
                        {
                            ZombieHealth3trans->setScale(glm::vec3(0, 0, 0));
                        }
                        else if ((ZombieHealth2trans->getScale().x != 0 || ZombieHealth2trans->getScale().y != 0))
                        {
                            ZombieHealth2trans->setScale(glm::vec3(0, 0, 0));
                        }
                        else if ((ZombieHealth1trans->getScale().x != 0 || ZombieHealth1trans->getScale().y != 0))
                        {
                            ZombieHealth1trans->setScale(glm::vec3(0, 0, 0));
                        }
                    }
                    GetOwner()->is_collide = false;
                }
            }
        }

        if (health <= 0)
        {
            SOUNDMANAGER->play("ZOMBIE_DIED_SOUND.wav");
            PHYSICS->walls_and_zombies.erase(std::find(PHYSICS->walls_and_zombies.begin(), PHYSICS->walls_and_zombies.end(), rigidbody));

            ZombieHealth1trans->setScale(glm::vec3(0, 0, 0));
            ZombieHealth2trans->setScale(glm::vec3(0, 0, 0));
            ZombieHealth3trans->setScale(glm::vec3(0, 0, 0));

            OBJECT_FACTORY->Destroy(Zombiedetect);
            OBJECT_FACTORY->Destroy(ZombieHealth1);
            OBJECT_FACTORY->Destroy(ZombieHealth2);
            OBJECT_FACTORY->Destroy(ZombieHealth3);
            OBJECT_FACTORY->Destroy(GetOwner());
        }
        if (!ZombieHealth1trans)
        {
            ZombieHealth1->AddComponent(ZombieHealth1trans);
        }
        if (!Zombiedetecttrans)
        {
            Zombiedetect->AddComponent(Zombiedetecttrans);
        }
        if (!ZombieHealth2trans)
        {
            ZombieHealth2->AddComponent(ZombieHealth2trans);
        }
        if (!ZombieHealth3trans)
        {
            ZombieHealth3->AddComponent(ZombieHealth3trans);
        }
    }

    void ZombieController::Movement(float dt)
    {
        oldrot = glm::vec3(0.0f, 0.0f, transform->getRotation().z);
        if (collision->FieldViewCollisionCheck(playertransform->GetOwner(), transform->GetOwner(), 3.2f) && (OBJECT_FACTORY->GetObjectID(100)->room_number == GetOwner()->room_number))
        {
			if (isdetect)
			{
				SOUNDMANAGER->play("ZOMBIE_DETECT_SOUND.wav");
				isdetect = false;
			}
			Zombiedetecttrans->setScale(glm::vec3(400, 100, 100));
            glm::vec3 newdirection = (playertransform->getPosition()) - (transform->getPosition());
            rigidbody->pm_force += newdirection * 15.f;

            float radian = glm::acos((glm::dot(glm::vec3(1.0f, 0.0f, 0.0f), newdirection)) / (glm::length(newdirection)));
            if ((playertransform->getPosition().y > transform->getPosition().y))
            {
                transform->setRotation(glm::vec3(0.f, 0.f, (radian - PI)));
            }
            else
            {
                transform->setRotation(glm::vec3(0.f, 0.f, (PI - radian)));
            }
            return;
        }
		isdetect = true;
        Zombiedetecttrans->setScale(glm::vec3(0, 0, 0));
        if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
        {
            if (OBJECT_FACTORY->GetObjectID(100)->room_number == GetOwner()->room_number)
            {
                glm::vec3 newdirection = (playertransform->getPosition()) - (transform->getPosition());

                float radian = glm::acos((glm::dot(glm::vec3(1.0f, 0.0f, 0.0f), newdirection)) / (glm::length(newdirection)));
                if ((playertransform->getPosition().y > transform->getPosition().y))
                {
                    transform->setRotation(glm::vec3(0.f, 0.f, (radian - PI)));
                }
                else
                {
                    transform->setRotation(glm::vec3(0.f, 0.f, (PI - radian)));
                }
                return;
            }
        }
        if (Direction)
        {
            if (timer.GetTime() > 3)
            {
                glm::vec3 direction = (glm::vec3(glm::cos(transform->getRotation().z), glm::sin(transform->getRotation().z), 0.f));
                rigidbody->pm_force += -direction * 4.5f;
                if (timer.GetTime() > 5)
                {

                    timer.Init();
                    Direction = rand() % 2;
                    return;
                }
            }
            else
            {
                oldrot.z += dt;
                transform->setRotation(oldrot);
            }
        }
        else
        {
            if (timer.GetTime() > 3)
            {
                glm::vec3 direction = (glm::vec3(glm::cos(transform->getRotation().z), glm::sin(transform->getRotation().z), 0.f));
                rigidbody->pm_force += -direction * 4.5f;
                if (timer.GetTime() > 7)
                {
					if ((OBJECT_FACTORY->GetObjectID(100)->room_number == GetOwner()->room_number))
						SOUNDMANAGER->play("ZOMBIE_NORMAL_SOUND.wav");
                    timer.Init();
                    Direction = rand() % 2;
                    return;
                }
            }
            else
            {
                oldrot.z -= dt;
                transform->setRotation(oldrot);
            }
        }
    }
}
