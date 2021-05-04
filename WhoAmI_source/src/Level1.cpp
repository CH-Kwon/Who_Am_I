/**
\file        Level1.cpp
\author      Changuk Lee
\par         email: leechanguk0510@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "Level1.h"
#include "Application.h"
#include "ComponentType.h"
#include "Engine.h"
#include "GameList.h"
#include "GameStateManager.h"
#include "Graphics.h"
#include "Headers_Components.h"
#include "Headers_Controllers.h"
#include "Object.h"
#include "ObjectFactory.h"
#include "ObjectGenerator.h"
#include "Physics.h"
#include "SoundManager.h"
#include "Texture.h"
#include "Timer.hpp"
#include "jsonReader.h"
#include <functional>
#include <glm/glm.hpp>
#include <iostream>
#define WIDTH 1280
#define HEIGHT_TEMP 640 //720

using namespace std;
using namespace glm;


namespace FindersEngine
{
    bool isTextbox;
    bool isZombie;
    bool isAmmo;
    bool isPistol;

    bool isTrigger_W;
    bool isTrigger_A;
    bool isTrigger_S;
    bool isTrigger_D;
    bool isJoystickHint;
    bool isactionHint;

    namespace Level1
    {
        static bool on = true;
        unsigned message_flag;
    }

    void Level1StateLoad(void)
    {
        using namespace Level1;
    }
    /*TEST*/
    Object* to_delete;
    Object* flashlight_msg;
    Transform* flashlight_msg_transform;
    Object* speechbox1;
    Object* speechbox2;
    Object* speechbox3;
    Object* textbox3;
    Object* player;

    Object* pistolhud;
    Object* ammohud;
    Object* ammo1;
    Object* ammo2;
    Object* ammo3;
    Object* pistol;

    Object* movepaper;
    Object* textbox1;
    Object* textbox2;
    Object* hintbox1;
    Object* hintbox2;
    Object* hintbox3;
    Object* hintbox4;
    Object* m_savezone;
    Object* pausebox;
    Object* backtom;
    Object* resume;
    Object* h_play;
    Object* quitButton;

    Transform* movepaper_transform;
    Transform* textbox1_transform;
    Transform* textbox2_transform;
    Transform* hintbox1_transform;
    Transform* hintbox2_transform;
    Transform* hintbox3_transform;
    Transform* hintbox4_transform;
    Transform* m_savezone_transform;
    Transform* pausebox_transform;
    Transform* backtom_transform;
    Transform* resume_transform;
    Transform* h_play_transform;
    Transform* quitButtonTransform;

    Object* ammo_font;

    SpriteText* st;

    Object* DamageWarning;
    Transform* DamageWarningtransform;
    Hud* DamageWarningHud;

    Timer timer;
    static int ammo_count = 0;
    Collision* m_collision;

    std::string name;

    // For TEST
    RigidBody* player_rigidbody;

    void setName(const std::string& str)
    {
        name = str;
    }
    const std::string& getName()
    {
        return name;
    }

    void Level1StateInit(void)
    {
        JSONREADER->jsonReaderMain();
        to_delete = nullptr;
        flashlight_msg = nullptr;
        flashlight_msg_transform = nullptr;
        speechbox1 = nullptr;
        speechbox2 = nullptr;
        speechbox3 = nullptr;
        textbox3 = nullptr;
        player = nullptr;

        pistolhud = nullptr;
        ammohud = nullptr;
        ammo1 = nullptr;
        ammo2 = nullptr;
        ammo3 = nullptr;
        pistol = nullptr;

        movepaper = nullptr;
        textbox1 = nullptr;
        textbox2 = nullptr;
        hintbox1 = nullptr;
        hintbox2 = nullptr;
        hintbox3 = nullptr;
        hintbox4 = nullptr;
        m_savezone = nullptr;
        pausebox = nullptr;
        backtom = nullptr;
        resume = nullptr;
        h_play = nullptr;
        quitButton = nullptr;

        movepaper_transform = nullptr;
        textbox1_transform = nullptr;
        textbox2_transform = nullptr;
        hintbox1_transform = nullptr;
        hintbox2_transform = nullptr;
        hintbox3_transform = nullptr;
        hintbox4_transform = nullptr;
        m_savezone_transform = nullptr;
        pausebox_transform = nullptr;
        backtom_transform = nullptr;
        resume_transform = nullptr;
        h_play_transform = nullptr;
        quitButtonTransform = nullptr;

        st = nullptr;
        DamageWarning = nullptr;
        DamageWarningtransform = nullptr;
        DamageWarningHud = nullptr;
        m_collision = nullptr;
        player_rigidbody = nullptr;
        
        isTextbox = false;
        isZombie = false;
        isAmmo = false;
        isPistol = false;

        isTrigger_W = false;
        isTrigger_A = false;
        isTrigger_S = false;
        isTrigger_D = false;
        isJoystickHint = false;
        isactionHint = false;

        light_timer = 0;
        Font_timer = 0;
        timer.Init();
        using namespace Level1;

        SOUNDMANAGER->stop("MENU_SOUND.mp3");
        SOUNDMANAGER->play("BACKGROUND_SOUND.mp3");
        SOUNDMANAGER->play("THUNDER_SOUND.mp3");

        GRAPHICS->BackgroundColor(0, 0, 0, 1);

        ammo_font = OBJECT_GEN->CreateAFont(glm::vec3(WIDTH / 6 - 180, 550, 0), 0, "Ammo : " + std::to_string(ammo_count), glm::vec3(0.4f, 0.0f, 0.0f), 2010, 0.f);

        OBJECT_GEN->CreateBase(glm::vec3(-4, -4, 0), glm::vec3(3167, 3167, 0), 5001);
        OBJECT_GEN->CreateBase(glm::vec3(-4, 0, 0), glm::vec3(3167, 3167, 0), 5002);
        OBJECT_GEN->CreateBase(glm::vec3(-4, 4, 0), glm::vec3(3167, 3167, 0), 5003);
        OBJECT_GEN->CreateBase(glm::vec3(0, 4, 0), glm::vec3(3167, 3167, 0), 5004);
        OBJECT_GEN->CreateBase(glm::vec3(0, 0, 0), glm::vec3(3167, 3167, 0), 5005);
        OBJECT_GEN->CreateBase(glm::vec3(0, -4, 0), glm::vec3(3167, 3167, 0), 5006);
        OBJECT_GEN->CreateBase(glm::vec3(4, -4, 0), glm::vec3(3167, 3167, 0), 5007);
        OBJECT_GEN->CreateBase(glm::vec3(4, 0, 0), glm::vec3(3167, 3167, 0), 5008);
        OBJECT_GEN->CreateBase(glm::vec3(4, 4, 0), glm::vec3(3167, 3167, 0), 5009);

        player = OBJECT_GEN->CreatePlayer(JSONREADER->getPlayerPos(), 100);
        player->curr_ammo = JSONREADER->getPlayerAmmo();
        player_rigidbody = dynamic_cast<RigidBody*>(player->GetComponent(CT_RIGID_BODY));

        OBJECT_GEN->CreateZombie(JSONREADER->getZombie1Pos(), 1000);
        OBJECT_GEN->CreateZombie(JSONREADER->getZombie2Pos(), 1001);
        OBJECT_GEN->CreateZombie(JSONREADER->getZombie3Pos(), 1002);
        OBJECT_GEN->CreateZombie(glm::vec3(1, 2.5, 0), 1003);
        OBJECT_GEN->CreateZombie(glm::vec3(-1, 3.5, 0), 1004);
        OBJECT_GEN->CreateZombie(glm::vec3(-1, 2.5, 0), 1005);

        pistol = OBJECT_GEN->CreateObject("PIN_PISTOL.png", JSONREADER->getPistolPos(), glm::vec3(90, 90, 0), OT_PISTOL, ST_CIRCLE, 2000);

        ammo1 = OBJECT_GEN->CreateObject("PIN_AMMO.png", JSONREADER->getAmmo1Pos(), glm::vec3(90, 90, 0), OT_AMMO, ST_CIRCLE, 2100);
        ammo2 = OBJECT_GEN->CreateObject("PIN_AMMO.png", JSONREADER->getAmmo2Pos(), glm::vec3(90, 90, 0), OT_AMMO, ST_CIRCLE, 2101);
        ammo3 = OBJECT_GEN->CreateObject("PIN_AMMO.png", JSONREADER->getAmmo3Pos(), glm::vec3(90, 90, 0), OT_AMMO, ST_CIRCLE, 2102);

        OBJECT_GEN->CreateWall(JSONREADER->getWall1Pos(), JSONREADER->getHorizontalWallScale(), 4000);
        OBJECT_GEN->CreateWall(JSONREADER->getWall2Pos(), JSONREADER->getHorizontalWallScale(), 4001);
        OBJECT_GEN->CreateWall(JSONREADER->getWall3Pos(), JSONREADER->getHorizontalWallScale(), 4002);
        OBJECT_GEN->CreateWall(JSONREADER->getWall4Pos(), JSONREADER->getHorizontalWallScale(), 4003);
        OBJECT_GEN->CreateWall(JSONREADER->getWall5Pos(), JSONREADER->getVerticalWallScale(), 4004);
        OBJECT_GEN->CreateWall(JSONREADER->getWall6Pos(), JSONREADER->getVerticalWallScale(), 4005);
        OBJECT_GEN->CreateWall(JSONREADER->getWall7Pos(), JSONREADER->getVerticalWallScale(), 4006);
        OBJECT_GEN->CreateWall(JSONREADER->getWall8Pos(), JSONREADER->getVerticalWallScale(), 4007);
        OBJECT_GEN->CreateWall(JSONREADER->getCrossWallPos(), JSONREADER->getCrossWallScale(), 4008);

        OBJECT_GEN->CreateObject("PIN_VDOOR.png", JSONREADER->getDoor1Pos(), JSONREADER->getDoor1Scale(), OT_VDOOR, ST_RECTANGLE, 4100);
        OBJECT_GEN->CreateObject("PIN_HDOOR.png", JSONREADER->getDoor2Pos(), JSONREADER->getDoor2Scale(), OT_HDOOR, ST_RECTANGLE, 4101);
        OBJECT_GEN->CreateObject("PIN_HDOOR.png", JSONREADER->getDoor3Pos(), JSONREADER->getDoor3Scale(), OT_HDOOR, ST_RECTANGLE, 4102);
        OBJECT_GEN->CreateObject("PIN_HDOOR.png", JSONREADER->getDoor4Pos(), JSONREADER->getDoor4Scale(), OT_HDOOR, ST_RECTANGLE, 4103);
        OBJECT_GEN->CreateObject("PIN_HDOOR.png", JSONREADER->getDoor5Pos(), JSONREADER->getDoor5Scale(), OT_HDOOR, ST_RECTANGLE, 4104);
        OBJECT_GEN->CreateObject("PIN_VDOOR.png", JSONREADER->getDoor6Pos(), JSONREADER->getDoor6Scale(), OT_VDOOR, ST_RECTANGLE, 4105);
        OBJECT_GEN->CreateObject("PIN_HDOOR.png", JSONREADER->getDoor7Pos(), JSONREADER->getDoor7Scale(), OT_HDOOR, ST_RECTANGLE, 4106);
        OBJECT_GEN->CreateObject("PIN_VDOOR.png", JSONREADER->getDoor8Pos(), JSONREADER->getDoor8Scale(), OT_VDOOR, ST_RECTANGLE, 4107);
        OBJECT_GEN->CreateObject("PIN_VDOOR.png", glm::vec3(6, 5, 0), glm::vec3(150, 400, 0), OT_FDOOR, ST_RECTANGLE, 4200);

        OBJECT_GEN->CreateHint("PIN_NUM7.png", JSONREADER->getHint1Pos(), glm::vec3(90, 90, 1), OT_HINT, ST_CIRCLE, 6000);
        OBJECT_GEN->CreateHint("PIN_NUM2.png", JSONREADER->getHint2Pos(), glm::vec3(90, 90, 1), OT_HINT, ST_CIRCLE, 6001);
        OBJECT_GEN->CreateHint("PIN_NUM2.png", JSONREADER->getHint3Pos(), glm::vec3(90, 90, 1), OT_HINT, ST_CIRCLE, 6002);
        OBJECT_GEN->CreateHint("PIN_NUM3.png", JSONREADER->getHint4Pos(), glm::vec3(90, 90, 1), OT_HINT, ST_CIRCLE, 6003);

        if (!APPLICATION->isUsingGamepad)
        {
            OBJECT_GEN->CreateHud(glm::vec3(JSONREADER->getPlayerPos().x + (WIDTH / 2), JSONREADER->getPlayerPos().y + (HEIGHT_TEMP / 2.5f), 0), glm::vec3(90, 90, 0), 3650, "PIN_ARROWUP.png");
            OBJECT_GEN->CreateHud(glm::vec3(JSONREADER->getPlayerPos().x + (WIDTH / 2), JSONREADER->getPlayerPos().y + (HEIGHT_TEMP / 1.4f), 0), glm::vec3(90, 90, 0), 3651, "PIN_ARROWDOWN.png");
            OBJECT_GEN->CreateHud(glm::vec3(JSONREADER->getPlayerPos().x + (WIDTH / 2.45f), JSONREADER->getPlayerPos().y + (HEIGHT_TEMP / 1.8f), 0), glm::vec3(90, 90, 0), 3652, "PIN_ARROWLEFT.png");
            OBJECT_GEN->CreateHud(glm::vec3(JSONREADER->getPlayerPos().x + (WIDTH / 1.7f), JSONREADER->getPlayerPos().y + (HEIGHT_TEMP / 1.8f), 0), glm::vec3(90, 90, 0), 3653, "PIN_ARROWRIGHT.png");
        }
        if (APPLICATION->isUsingGamepad)
        {
            OBJECT_GEN->CreateHud(glm::vec3(JSONREADER->getPlayerPos().x + (WIDTH / 2), JSONREADER->getPlayerPos().y + (HEIGHT_TEMP / 2.8f), 0), glm::vec3(230, 120, 0), 3654, "PIN_JOYSTICKMOVE.png");
            isJoystickHint = true;
        }

        /*Making Object by using scale*/

        movepaper = OBJECT_GEN->CreateTextbox(vec3(WIDTH / 2, HEIGHT_TEMP / 1.15f, 0), glm::vec3(0, 0, 0), 3609, "PIN_MOVEPAPER.png");
        textbox1 = OBJECT_GEN->CreateTextbox(vec3(WIDTH / 2, HEIGHT_TEMP / 1.15f, 0), glm::vec3(0, 0, 0), 3600, "PIN_PAPER.png");
        hintbox1 = OBJECT_GEN->CreateHud(glm::vec3(50.f, HEIGHT_TEMP, 0), glm::vec3(0, 0, 1.f), 3055, "PIN_HINTBOX.png");
        textbox2 = OBJECT_GEN->CreateTextbox(glm::vec3(WIDTH / 2, HEIGHT_TEMP / 1.15f, 0), glm::vec3(0, 0, 0), 3611, "PIN_PAPER2.png");
        hintbox2 = OBJECT_GEN->CreateHud(glm::vec3(100.f, HEIGHT_TEMP, 0), vec3(0, 0, 1.f), 3056, "PIN_HINTBOX.png");
        hintbox3 = OBJECT_GEN->CreateHud(glm::vec3(150.f, HEIGHT_TEMP, 0), vec3(0, 0, 1.f), 3057, "PIN_HINTBOX.png");
        m_savezone = OBJECT_GEN->CreateHud(vec3(WIDTH / 2, HEIGHT_TEMP / 1.15f, 0), glm::vec3(0, 0, 0), 3059, "PIN_PAPER4.png");
        hintbox4 = OBJECT_GEN->CreateHud(glm::vec3(200.f, HEIGHT_TEMP, 0), vec3(0, 0, 1.f), 3058, "PIN_HINTBOX.png");
        pausebox = OBJECT_GEN->CreatePausebox(vec3(WIDTH / 2.0f, HEIGHT_TEMP / 1.7f, 0), glm::vec3(0, 0, 0.f), 3604, "PIN_PAUSEBOX.png");
        backtom = OBJECT_GEN->CreateButton(vec3(WIDTH / 2.0f, HEIGHT_TEMP / 2.0f, 0), glm::vec3(0, 0, 0.f), 3605, "PIN_GOTOM.png", "BackToMenu");
        resume = OBJECT_GEN->CreateButton(vec3(WIDTH / 2.0f, HEIGHT_TEMP / 3.f, 0), glm::vec3(0, 0, 0.f), 3606, "PIN_RESUME.png", "Resume");
        h_play = OBJECT_GEN->CreateButton(vec3(WIDTH / 2.0f, HEIGHT_TEMP / 1.5f, 0), glm::vec3(0, 0, 0.f), 3607, "PIN_HOWTOPLAY.png", "H_Play");
        quitButton = OBJECT_GEN->CreateButton(vec3(WIDTH / 2.0f, HEIGHT_TEMP / 1.2f, 0), glm::vec3(0, 0, 0.f), 3608, "PIN_QUIT.png", "QuitButton");

        /***********************/

        OBJECT_GEN->CreateSprite("PIN_SAVEZONE.png", vec3(-1.4f, -0.7f, 0), vec3(600.f, 300.f, 1.f), 3602);

        if (!APPLICATION->isUsingGamepad)
        {
            flashlight_msg = OBJECT_GEN->CreateAFont(vec3(510.f, 50.0f, 0.f), 0.65f, "Press E: Flash Light", vec3(0.9f, 0.7f, 0.f), 6200, 0.0f);
            isactionHint = true;
        }
        if (APPLICATION->isUsingGamepad)
        {
            flashlight_msg = OBJECT_GEN->CreateAFont(vec3(510.f, 50.0f, 0.f), 0.65f, "Press 'B': Flash Light", vec3(0.9f, 0.7f, 0.f), 6201, 0.0f);
            isactionHint = true;
        }
        flashlight_msg_transform = dynamic_cast<Transform*>(flashlight_msg->GetComponent(CT_TRANSFORM));

        OBJECT_GEN->CreateHud(glm::vec3(640.0f, 30.0f, 0), vec3(40.f, 40.f, 1.f), 3050, "PIN_DIRECTION.png");

        Directiontransform = dynamic_cast<Transform*>(OBJECT_FACTORY->GetObjectID(3050)->GetComponent(CT_TRANSFORM));

        movepaper_transform = dynamic_cast<Transform*>(movepaper->GetComponent(CT_TRANSFORM));
        textbox1_transform = dynamic_cast<Transform*>(textbox1->GetComponent(CT_TRANSFORM));
        textbox2_transform = dynamic_cast<Transform*>(textbox2->GetComponent(CT_TRANSFORM));
        hintbox1_transform = dynamic_cast<Transform*>(hintbox1->GetComponent(CT_TRANSFORM));
        hintbox2_transform = dynamic_cast<Transform*>(hintbox2->GetComponent(CT_TRANSFORM));
        hintbox3_transform = dynamic_cast<Transform*>(hintbox3->GetComponent(CT_TRANSFORM));
        hintbox4_transform = dynamic_cast<Transform*>(hintbox4->GetComponent(CT_TRANSFORM));
        m_savezone_transform = dynamic_cast<Transform*>(m_savezone->GetComponent(CT_TRANSFORM));
        pausebox_transform = dynamic_cast<Transform*>(pausebox->GetComponent(CT_TRANSFORM));
        backtom_transform = dynamic_cast<Transform*>(backtom->GetComponent(CT_TRANSFORM));
        resume_transform = dynamic_cast<Transform*>(resume->GetComponent(CT_TRANSFORM));
        quitButtonTransform = dynamic_cast<Transform*>(quitButton->GetComponent(CT_TRANSFORM));
        h_play_transform = dynamic_cast<Transform*>(h_play->GetComponent(CT_TRANSFORM));

        Playertransform = dynamic_cast<Transform*>(OBJECT_FACTORY->GetObjectID(100)->GetComponent(CT_TRANSFORM));
        st = dynamic_cast<SpriteText*>(ammo_font->GetComponent(CT_SPRITE_TEXT));

        PrintFontCondition = -1;

        DamageWarning = OBJECT_FACTORY->CreateEmptyObject(3502);

        DamageWarningtransform = new Transform();
        DamageWarningtransform->setPosition(glm::vec3(WIDTH / 2, HEIGHT_TEMP / 2 + 50, 0));
        DamageWarningtransform->setScale(glm::vec3(0, 0, 0));

        DamageWarningHud = new Hud();
        DamageWarningHud->LoadTexture("PIN_GETDAMAGE.png");

        DamageWarning->AddComponent(DamageWarningtransform);
        DamageWarning->AddComponent(DamageWarningHud);

        DamageWarning->Init();
        SOUNDMANAGER->play("HEART_BEAT.wav");
    }

    int count = 0;

    void Level1StateUpdate(float dt)
    {
        if (player->is_getdamage)
        {
            DamageWarningHud->Init();
            DamageWarningHud->setBlendAlpha(1.0f);
            DamageWarningtransform->setScale(glm::vec3(WIDTH + 180, HEIGHT_TEMP + 120, 0));
            DamageWarning->AddComponent(DamageWarningtransform);
            DamageWarning->AddComponent(DamageWarningHud);
            player->is_getdamage = false;
        }

        // cheat codes
        const auto height = 720.f;

        if (Input::GetInstance().IsPressed(SDL_SCANCODE_LCTRL) && Input::GetInstance().IsPressed(SDL_SCANCODE_1))
        {
            GRAPHICS->TurnOffSpotLight();
        }
        if (Input::GetInstance().IsPressed(SDL_SCANCODE_LCTRL) && Input::GetInstance().IsPressed(SDL_SCANCODE_2))
        {
            OBJECT_GEN->CreateHud(glm::vec3(50.0f, HEIGHT_TEMP, 0), vec3(50.f, 50.f, 1.f), 9000 + count, "PIN_NUM7.png");
            OBJECT_GEN->CreateHud(glm::vec3(100.0f, HEIGHT_TEMP, 0), vec3(50.f, 50.f, 1.f), 9001 + count, "PIN_NUM2.png");
            OBJECT_GEN->CreateHud(glm::vec3(150.0f, HEIGHT_TEMP, 0), vec3(50.f, 50.f, 1.f), 9002 + count, "PIN_NUM2.png");
            OBJECT_GEN->CreateHud(glm::vec3(200.0f, HEIGHT_TEMP, 0), vec3(50.f, 50.f, 1.f), 9004 + count, "PIN_NUM3.png");
            count += 5;
        }

        if (!ENGINE->isPause)
        {
            if (isTrigger_W == false)
            {
                if (Input::GetInstance().IsTriggered(SDL_SCANCODE_W) || Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_DPAD_UP))
                {
                    OBJECT_FACTORY->Destroy(OBJECT_FACTORY->GetObjectID(3650));
                    isTrigger_W = true;
                }
            }
            if (isTrigger_A == false)
            {
                if (Input::GetInstance().IsTriggered(SDL_SCANCODE_A) || Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_DPAD_LEFT))
                {
                    OBJECT_FACTORY->Destroy(OBJECT_FACTORY->GetObjectID(3652));
                    isTrigger_A = true;
                }
            }
            if (isTrigger_S == false)
            {
                if (Input::GetInstance().IsTriggered(SDL_SCANCODE_S) || Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_DPAD_DOWN))
                {
                    OBJECT_FACTORY->Destroy(OBJECT_FACTORY->GetObjectID(3651));
                    isTrigger_S = true;
                }
            }
            if (isTrigger_D == false)
            {
                if (Input::GetInstance().IsTriggered(SDL_SCANCODE_D) || Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
                {
                    OBJECT_FACTORY->Destroy(OBJECT_FACTORY->GetObjectID(3653));
                    isTrigger_D = true;
                }
            }
            if (isJoystickHint == true)
            {
                if (timer.GetTime() > 5.f)
                {
                    OBJECT_FACTORY->Destroy(OBJECT_FACTORY->GetObjectID(3654));
                    isJoystickHint = false;
                }
            }
        }

        if (isAmmo == false)
        {
            if (m_collision->CircleCircleCollisionCheck(player, ammo1) ||
                m_collision->CircleCircleCollisionCheck(player, ammo2) ||
                m_collision->CircleCircleCollisionCheck(player, ammo3))
            {
                st->setScale(0.5f);
                OBJECT_GEN->CreateHud(glm::vec3(WIDTH / 6 - 50, height / 8, 0), glm::vec3(50, 50, 0), 3700, "PIN_AMMO.png");
                OBJECT_GEN->CreateTextbox(glm::vec3(WIDTH / 6 - 120, height / 3, 0), glm::vec3(150, 100, 0), 3702, "PIN_AMMOLIMIT.png");

                isAmmo = true;
            }
        }

        if (isPistol == false)
        {
            if (m_collision->CircleCircleCollisionCheck(player, pistol))
            {
                if (!APPLICATION->isUsingGamepad)
                {
                    OBJECT_GEN->CreateHud(glm::vec3(WIDTH / 6 - 150, height / 8, 0), glm::vec3(70, 50, 0), 3701, "PIN_PISTOL.png");
                    OBJECT_GEN->CreateSpeechBox(vec3(WIDTH / 2.0f + 40, HEIGHT_TEMP / 2.0f - 50, 0), glm::vec3(WIDTH / 6, HEIGHT_TEMP / 8, 0.f), 3601, "PIN_SPEECHBOX2.png");
                    isPistol = true;
                }
                else if (APPLICATION->isUsingGamepad)
                {
                    OBJECT_GEN->CreateHud(glm::vec3(WIDTH / 6 - 150, height / 8, 0), glm::vec3(70, 50, 0), 3701, "PIN_PISTOL.png");
                    OBJECT_GEN->CreateSpeechBox(vec3(WIDTH / 2.0f + 40, HEIGHT_TEMP / 2.0f - 50, 0), glm::vec3(WIDTH / 6, HEIGHT_TEMP / 8, 0.f), 3601, "PIN_SPEECHBOX3.png");
                    isPistol = true;
                }
            }
        }

        st->setText("Ammo: " + std::to_string(Playertransform->GetOwner()->curr_ammo));

        if (APPLICATION->isUsingGamepad == false)
        {
            m_collision->SaveWallDistance(player);
            GRAPHICS->set_wall_distance((m_collision->Max(player_rigidbody->wall_distance - 0.05f, 0.f)));
        }
        else if (APPLICATION->isUsingGamepad)
        {
            m_collision->SaveWallDistanceForPad(player);
            GRAPHICS->set_wall_distance((m_collision->Max(player_rigidbody->wall_distance - 0.05f, 0.f)));
        }

        if (PlayerController::isDead())
        {
            Playertransform->setPosition(glm::vec3(0, 0, 0));
            PlayerController::player_health = 300;
            player->curr_ammo = JSONREADER->getPlayerAmmo();
            player->curr_Armor = JSONREADER->getPlayerArmor();
        }
        if (m_collision->CircleCircleCollisionCheck(player, OBJECT_FACTORY->GetObjectID(6000)))
        {
            SOUNDMANAGER->play("ITEM_EAT_SOUND.wav");
            OBJECT_FACTORY->Destroy(OBJECT_FACTORY->GetObjectID(6000));
            OBJECT_GEN->CreateHud(glm::vec3(50.0f, HEIGHT_TEMP, 0), vec3(50.f, 50.f, 0.f), 3051, "PIN_NUM7.png");
        }
        if (m_collision->CircleCircleCollisionCheck(player, OBJECT_FACTORY->GetObjectID(6001)))
        {
            SOUNDMANAGER->play("ITEM_EAT_SOUND.wav");
            OBJECT_FACTORY->Destroy(OBJECT_FACTORY->GetObjectID(6001));
            OBJECT_GEN->CreateHud(glm::vec3(100.0f, HEIGHT_TEMP, 0), vec3(50.f, 50.f, 0.f), 3052, "PIN_NUM2.png");
        }
        if (m_collision->CircleCircleCollisionCheck(player, OBJECT_FACTORY->GetObjectID(6002)))
        {
            SOUNDMANAGER->play("ITEM_EAT_SOUND.wav");
            OBJECT_FACTORY->Destroy(OBJECT_FACTORY->GetObjectID(6002));
            OBJECT_GEN->CreateHud(glm::vec3(150.0f, HEIGHT_TEMP, 0), vec3(50.f, 50.f, 0.f), 3053, "PIN_NUM2.png");
        }
        if (m_collision->CircleCircleCollisionCheck(player, OBJECT_FACTORY->GetObjectID(6003)))
        {
            SOUNDMANAGER->play("ITEM_EAT_SOUND.wav");
            OBJECT_FACTORY->Destroy(OBJECT_FACTORY->GetObjectID(6003));
            OBJECT_GEN->CreateHud(glm::vec3(200.0f, HEIGHT_TEMP, 0), vec3(50.f, 50.f, 0.f), 3054, "PIN_NUM3.png");
        }

        random_light1(dt);

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if (Playertransform->GetOwner()->room_number == 1)
        {
            movepaper_transform->setScale(vec3(600, 60, 0));
        }
        else
        {
            movepaper_transform->setScale(vec3(0, 0, 0));
        }
        if (Playertransform->GetOwner()->room_number == 2)
        {
            textbox1_transform->setScale(vec3(600, 60, 0));
        }
        else
        {
            textbox1_transform->setScale(vec3(0, 0, 0));
        }
        if (Playertransform->GetOwner()->room_number == 3)
        {
            hintbox1_transform->setScale(vec3(52, 47, 0));
            textbox2_transform->setScale(vec3(600, 60, 0));
        }
        else
        {
            hintbox1_transform->setScale(vec3(0, 0, 0));
            textbox2_transform->setScale(vec3(0, 0, 0));
        }
        if (Playertransform->GetOwner()->room_number == 4)
        {
            hintbox2_transform->setScale(vec3(52, 47, 0));
        }
        else
        {
            hintbox2_transform->setScale(vec3(0, 0, 0));
        }
        if (Playertransform->GetOwner()->room_number == 5)
        {
            hintbox3_transform->setScale(vec3(52, 47, 0));
            m_savezone_transform->setScale(vec3(400, 50, 0));
        }
        else
        {
            hintbox3_transform->setScale(vec3(0, 0, 0));
            m_savezone_transform->setScale(vec3(0, 0, 0));
        }
        if (Playertransform->GetOwner()->room_number == 8)
        {
            hintbox4_transform->setScale(vec3(52, 47, 0));
        }
        else
        {
            hintbox4_transform->setScale(vec3(0, 0, 0));
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if ((Playertransform->GetOwner()->room_number == 1) ||
            (Playertransform->GetOwner()->room_number == 2) ||
            (Playertransform->GetOwner()->room_number == 8) ||
            (Playertransform->GetOwner()->room_number == 6))
        {
            float degree = 90.f;
            Directiontransform->setPosition(glm::vec3(640.0f, 30.0f, 0));
            Directiontransform->setRotation(glm::vec3(0.f, 0.f, -glm::radians(degree)));
        }
        else if ((Playertransform->GetOwner()->room_number == 3) ||
                 (Playertransform->GetOwner()->room_number == 5) ||
                 (Playertransform->GetOwner()->room_number == 9))
        {
            Directiontransform->setPosition(glm::vec3(1260.0f, 360.0f, 0));
            Directiontransform->setRotation(glm::vec3(0.f, 0.f, 0.f));
        }
        else if (Playertransform->GetOwner()->room_number == 4)
        {
            float degree = 90.f;
            Directiontransform->setPosition(glm::vec3(640.0f, 700.0f, 0));
            Directiontransform->setRotation(glm::vec3(0.f, 0.f, glm::radians(degree)));
        }

        if (player->is_in_Final == true)
        {
            Numpad = OBJECT_GEN->CreateHud(vec3(650, 370, 0), vec3(600, 750, 1.f), 3012, "PIN_NUMPAD.png");
            Num1 = OBJECT_GEN->CreateButton(vec3(450, 250.0f, 0), vec3(150, 150, 0), 3000, "PIN_NUM1.png", "1");
            Num2 = OBJECT_GEN->CreateButton(vec3(650.0f, 250.0f, 0), vec3(150, 150, 0), 3001, "PIN_NUM2.png", "2");
            Num3 = OBJECT_GEN->CreateButton(glm::vec3(850.0f, 250.0f, 0), vec3(150, 150, 0), 3002, "PIN_NUM3.png", "3");
            Num4 = OBJECT_GEN->CreateButton(glm::vec3(450.0f, 400.0f, 0), vec3(150, 150, 0), 3003, "PIN_NUM4.png", "4");
            Num5 = OBJECT_GEN->CreateButton(glm::vec3(650.0f, 400.0f, 0), vec3(150, 150, 0), 3004, "PIN_NUM5.png", "5");
            Num6 = OBJECT_GEN->CreateButton(glm::vec3(850.0f, 400.0f, 0), vec3(150, 150, 0), 3005, "PIN_NUM6.png", "6");
            Num7 = OBJECT_GEN->CreateButton(glm::vec3(450.0f, 550.0f, 0), vec3(150, 150, 0), 3006, "PIN_NUM7.png", "7");
            Num8 = OBJECT_GEN->CreateButton(glm::vec3(650.0f, 550.0f, 0), vec3(150, 150, 0), 3007, "PIN_NUM8.png", "8");
            Num9 = OBJECT_GEN->CreateButton(glm::vec3(850.0f, 550.0f, 0), vec3(150, 150, 0), 3008, "PIN_NUM9.png", "9");
            Num11 = OBJECT_GEN->CreateButton(glm::vec3(450.0f, 700.0f, 0), vec3(150, 150, 0), 3009, "PIN_NUM_STAR.png", "star");
            Num0 = OBJECT_GEN->CreateButton(glm::vec3(650.0f, 700.0f, 0), vec3(150, 150, 0), 3010, "PIN_NUM0.png", "0");
            Num12 = OBJECT_GEN->CreateButton(glm::vec3(850.0f, 700.0f, 0), vec3(150, 150, 0), 3011, "PIN_NUM_HASH.png", "hash");
            Playertransform->setPosition(Playertransform->getPosition() - glm::vec3(0.3f, 0, 0));
            player->is_in_Final = false;
            ENGINE->isPause = true;
        }
        if (Numpad != nullptr)
        {
            if (Input::GetInstance().IsTriggered(SDL_SCANCODE_F) || Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_X))
            {
                Numpad->Destroy(Numpad);
                Numpad = nullptr;
                Num1->Destroy(Num1);
                Num1 = nullptr;
                Num2->Destroy(Num2);
                Num2 = nullptr;
                Num3->Destroy(Num3);
                Num3 = nullptr;
                Num4->Destroy(Num4);
                Num4 = nullptr;
                Num5->Destroy(Num5);
                Num5 = nullptr;
                Num6->Destroy(Num6);
                Num6 = nullptr;
                Num7->Destroy(Num7);
                Num7 = nullptr;
                Num8->Destroy(Num8);
                Num8 = nullptr;
                Num9->Destroy(Num9);
                Num9 = nullptr;
                Num11->Destroy(Num11);
                Num11 = nullptr;
                Num0->Destroy(Num0);
                Num0 = nullptr;
                Num12->Destroy(Num12);
                Num12 = nullptr;
                ENGINE->isPause = false;
                if (FirstNumber)
                {
                    OBJECT_FACTORY->Destroy(FirstNumber);
                    FirstNumber = nullptr;
                }
                if (SecondNumber)
                {
                    OBJECT_FACTORY->Destroy(SecondNumber);
                    SecondNumber = nullptr;
                }
                if (ThirdNumber)
                {
                    OBJECT_FACTORY->Destroy(ThirdNumber);
                    ThirdNumber = nullptr;
                }
                if (ForthNumber)
                {
                    OBJECT_FACTORY->Destroy(ForthNumber);
                    ForthNumber = nullptr;
                }
                GAMELOGIC->INDEX = 0;
            }
        }

        if (Input::GetInstance().IsTriggered(SDL_SCANCODE_E))
        {
            if (isactionHint)
            {
                OBJECT_FACTORY->Destroy(flashlight_msg);
                isactionHint = false;
            }
        }

        if (Numpad) //To check if player is in final zone
        {
            std::string print = "";
            if (PrintFontCondition != (GAMELOGIC->INDEX) - 1)
            {
                switch ((GAMELOGIC->INDEX) - 1)
                {
                    case 0:
                        print = GAMELOGIC->GetSercretNumber[0];
                        FirstNumber = OBJECT_GEN->CreateAFont(glm::vec3(520.f, 580.f, 0.f), 1.2f, print, glm::vec3(0.9f, 0.7f, 0.0f), 6101, 0.f);
                        PrintFontCondition = (GAMELOGIC->INDEX) - 1;
                        break;
                    case 1:
                        print = GAMELOGIC->GetSercretNumber[1];
                        SecondNumber = OBJECT_GEN->CreateAFont(glm::vec3(585.f, 580.f, 0.f), 1.2f, print, glm::vec3(0.9f, 0.7f, 0.0f), 6102, 0.f);
                        PrintFontCondition = (GAMELOGIC->INDEX) - 1;
                        break;
                    case 2:
                        print = GAMELOGIC->GetSercretNumber[2];
                        ThirdNumber = OBJECT_GEN->CreateAFont(glm::vec3(655.f, 580.f, 0.f), 1.2f, print, glm::vec3(0.9f, 0.7f, 0.0f), 6103, 0.f);
                        PrintFontCondition = (GAMELOGIC->INDEX) - 1;
                        break;
                    case -1:
                        print = GAMELOGIC->GetSercretNumber[3];
                        ForthNumber = OBJECT_GEN->CreateAFont(glm::vec3(720.f, 580.f, 0.f), 1.2f, print, glm::vec3(0.9f, 0.7f, 0.0f), 6104, 0.f);
                        PrintFontCondition = (GAMELOGIC->INDEX) - 1;

                        if (GAMELOGIC->CheckSecretNumber())
                        {
                            SDL_HapticRumblePlay(APPLICATION->gControllerHaptic, 10.f, 500);
                            GAMELOGIC->ClearGetSecretNumber();
							SDL_HapticRumblePlay(APPLICATION->gControllerHaptic, 0.7f, 100);
                            GAME_STATE->SetNextState(SL_WIN);
                        }
                        else
                        {
                            SDL_HapticRumblePlay(APPLICATION->gControllerHaptic, 3.f, 100);
                            SOUNDMANAGER->play("BEEP_ERROR.wav");
                            LoseFont = OBJECT_GEN->CreateAFont(glm::vec3(WIDTH / 2.f - 150.f, HEIGHT_TEMP / 2.f - 100.f, 0.f), 0.9f, "Wrong PassWord", glm::vec3(0.9f, 0.7f, 0.0f), 6100, 0.f);
                            GAMELOGIC->ClearGetSecretNumber();
                            OBJECT_FACTORY->Destroy(FirstNumber);
                            OBJECT_FACTORY->Destroy(SecondNumber);
                            OBJECT_FACTORY->Destroy(ThirdNumber);
                            OBJECT_FACTORY->Destroy(ForthNumber);
			    SDL_HapticRumblePlay(APPLICATION->gControllerHaptic, 0.7f, 100);
                        }
                        break;
                    default:
                        break;
                }
            }
            if (LoseFont != nullptr)
            {
                Font_timer += 1;
                if (Font_timer >= 60)
                {
                    LoseFont->Destroy(LoseFont);
                    Font_timer = 0;
                }
            }
        }


        if (Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_START) || Input::GetInstance().IsTriggered(SDL_SCANCODE_ESCAPE))
        {
            if (ENGINE->isPause == false)
            {
                ENGINE->isPause = true;
                APPLICATION->pausePadStatus = 0;
                pausebox_transform->setScale(vec3(WIDTH / 4, HEIGHT_TEMP / 1.4f, 0.f));
                backtom_transform->setScale(vec3(WIDTH / 6, HEIGHT_TEMP / 8, 0.f));
                resume_transform->setScale(vec3(WIDTH / 6, HEIGHT_TEMP / 8, 0.f));
                quitButtonTransform->setScale(vec3(WIDTH / 6, HEIGHT_TEMP / 8, 0.f));
                h_play_transform->setScale(vec3(WIDTH / 6, HEIGHT_TEMP / 8, 0.f));
            }
        }
        if (ENGINE->isPause == false && ENGINE->isResume == true)
        {
            ENGINE->isResume = false;
            pausebox_transform->setScale(vec3(0.f, 0.f, 0.f));
            backtom_transform->setScale(vec3(0.f, 0.f, 0.f));
            resume_transform->setScale(vec3(0.f, 0.f, 0.f));
            quitButtonTransform->setScale(vec3(0.f, 0.f, 0.f));
            h_play_transform->setScale(vec3(0, 0, 0));
        }
    }

    void Level1StateExit(void)
    {
        isTextbox = false;
        isZombie = false;
        isAmmo = false;
        isPistol = false;

        isTrigger_W = false;
        isTrigger_A = false;
        isTrigger_S = false;
        isTrigger_D = false;

        PHYSICS->walls_and_zombies.clear();
        PHYSICS->walls.clear();
        SOUNDMANAGER->stop("BACKGROUND_SOUND.mp3");
        SOUNDMANAGER->stop("THUNDER_SOUND.mp3");
        OBJECT_FACTORY->DestroyAllObjects();
    }

    void Level1StateUnload(void)
    {
    }
    void random_light1(float dt)
    {

        light_timer += 1;
        if (light_timer == 70)
            GRAPHICS->TurnOnSpotLight();
        else if (light_timer == 90)
            GRAPHICS->TurnOffSpotLight();
        else if (light_timer == 100)
            GRAPHICS->TurnOnSpotLight();
        else if (light_timer == 110)
            GRAPHICS->TurnOffSpotLight();
        else if (light_timer == 125)
            GRAPHICS->TurnOnSpotLight();
        else if (light_timer >= 400)
            light_timer = 0;
    }
}
