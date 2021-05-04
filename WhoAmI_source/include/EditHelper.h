/**
\file        EditHelper.h
\author      jinseob.park
\par         email: 0814owl@gmail.com
\par         course: GAM200
\date        12/15/2017
\brief       MapEdit stage.

*/
#pragma once
#ifndef EDITHELPER_H
#define EDITHELPER_H
#include "glm/glm.hpp"
#include <vector>

const int BaseId = 5001;
const int PlayerId = 100;
const int ZombieId = 1000;
const int PistolId = 2000;
const int AmmoId = 2100;
const int ArmorId = 2200;
const int WallId = 4000;
const int DoorId = 4100;
const int TutorialId = 5000;
const int HPbar_Id = 3500;
const int ArmorbarId = 3501;


namespace FindersEngine
{
    class Object;
    class Transform;
    enum EditMode
    {
        TRANS,
        SCALE_X,
        SCALE_Y,
        ROTATION,
        NONE
    };

    enum LevelEdit
    {
        EDLevel1,
        NONELEVEL
    };

    struct GameData
    {
        LevelEdit Currentlevel = NONELEVEL;
        Object* Player;
        Object* FinalDoor;

        std::vector<Object*> Wall;
        std::vector<Object*> Door;
        std::vector<Object*> Bullet;
        std::vector<Object*> Ammo;
        std::vector<Object*> Zombie;
        Object* Pistol;
        std::vector<Object*> Armor;


        unsigned int Wall_Count = 0;
        unsigned int Zombie_Count = 0;
        unsigned int Door_Count = 0;
        unsigned int Ammo_Count = 0;
    };

    struct EditInfo
    {
        EditMode Mode = NONE;
        bool IsSelect = false;
        glm::vec2 Location = {0, 0};
        int TargetObject = 0;
        int TargetType = 0;
    };

    void InitPlayer(GameData& data);
    void InitFinalDoor(GameData& data);
    void InitWall(GameData& data);
    void InitDoor(GameData& data);
    void InitAmmo(GameData& data);
    void InitZombie(GameData& data);
    void InitPistol(GameData& data);
    void InitArmor(GameData& data);

    void EditZombie(GameData& data);
    void EditDoor(GameData& data);
    void EditWall(GameData& data);
    void EditAmmo(GameData& data);
    void EditPistol(GameData& data);
    void NotPause(void);
    void ModeHelper(void);
    void LevelHelper(GameData& data);
    int RoundInt(float value);
}
#endif