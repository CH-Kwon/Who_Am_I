/**
\file        jsonReader.h
\author      SeongHyun Hong
\par         email: tjdgus3174@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#ifndef jsonReader_h
#define jsonReader_h

#include "glm/glm.hpp"
#include "json.h"
#include "writer.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string.h>

namespace FindersEngine
{
    class jsonReader
    {
    public:
        jsonReader();
        ~jsonReader();

        bool read(std::string const& file, Json::Value& data_);

        int jsonReaderMain();
        int ReadJsonEdit();
        int ReadJsonLevel1();
        int ReadJsonLevel2();
        int ReadJsonLevel3();
        void savedJsonReader();
        void get_saved_data();

        glm::vec3 getPlayerPos(void) const;
        glm::vec3 getPistolPos(void) const;
        glm::vec3 getAmmo1Pos(void) const;
        glm::vec3 getAmmo2Pos(void) const;
        glm::vec3 getAmmo3Pos(void) const;

        glm::vec3 getWall1Pos(void) const;
        glm::vec3 getWall2Pos(void) const;
        glm::vec3 getWall3Pos(void) const;
        glm::vec3 getWall4Pos(void) const;
        glm::vec3 getWall5Pos(void) const;
        glm::vec3 getWall6Pos(void) const;
        glm::vec3 getWall7Pos(void) const;
        glm::vec3 getWall8Pos(void) const;

        unsigned getPlayerHealth(void) const;
        unsigned getPistolDamage(void) const;

        glm::vec3 getArmor1Pos(void) const;
        glm::vec3 getArmor2Pos(void) const;

        glm::vec3 getHorizontalWallScale(void) const;
        glm::vec3 getVerticalWallScale(void) const;

        glm::vec3 getCrossWallPos(void) const;
        glm::vec3 getCrossWallScale(void) const;

        glm::vec3 getZombie1Pos(void) const;
        glm::vec3 getZombie2Pos(void) const;
        glm::vec3 getZombie3Pos(void) const;

        glm::vec3 getBase1Pos(void) const;
        glm::vec3 getBase1Scale(void) const;
        glm::vec3 getBase2Pos(void) const;
        glm::vec3 getBase2Scale(void) const;
        glm::vec3 getBase3Pos(void) const;
        glm::vec3 getBase3Scale(void) const;
        glm::vec3 getBase4Pos(void) const;
        glm::vec3 getBase4Scale(void) const;
        glm::vec3 getBase5Pos(void) const;
        glm::vec3 getBase5Scale(void) const;
        glm::vec3 getBase6Pos(void) const;
        glm::vec3 getBase6Scale(void) const;
        glm::vec3 getBase7Pos(void) const;
        glm::vec3 getBase7Scale(void) const;
        glm::vec3 getBase8Pos(void) const;
        glm::vec3 getBase8Scale(void) const;
        glm::vec3 getBase9Pos(void) const;
        glm::vec3 getBase9Scale(void) const;

        glm::vec3 getDoor1Pos(void) const;
        glm::vec3 getDoor1Scale(void) const;

        glm::vec3 getDoor2Pos(void) const;
        glm::vec3 getDoor2Scale(void) const;
        glm::vec3 getDoor3Pos(void) const;
        glm::vec3 getDoor3Scale(void) const;
        glm::vec3 getDoor4Pos(void) const;
        glm::vec3 getDoor4Scale(void) const;
        glm::vec3 getDoor5Pos(void) const;
        glm::vec3 getDoor5Scale(void) const;
        glm::vec3 getDoor6Pos(void) const;
        glm::vec3 getDoor6Scale(void) const;
        glm::vec3 getDoor7Pos(void) const;
        glm::vec3 getDoor7Scale(void) const;
        glm::vec3 getDoor8Pos(void) const;
        glm::vec3 getDoor8Scale(void) const;

        glm::vec3 getHint1Pos(void) const;
        glm::vec3 getHint2Pos(void) const;
        glm::vec3 getHint3Pos(void) const;
        glm::vec3 getHint4Pos(void) const;

        unsigned getPlayerAmmo(void) const;
        unsigned getPlayerArmor(void) const;
        void get_data(void);

        void get_edit_data();

        glm::vec3 getWallPos(int num) const;
        glm::vec3 getDoorPos(int num) const;
        glm::vec3 getAmmoPos(int num) const;
        glm::vec3 getArmorPos(int num) const;
        glm::vec3 getZombiePos(int num) const;
        glm::vec3 getBasePos(int num) const;
        glm::vec3 getWallScale(int num) const;
        glm::vec3 getDoorScale(int num) const;
        glm::vec3 getAmmoScale(int num) const;
        glm::vec3 getArmorScale(int num) const;
        glm::vec3 getZombieScale(int num) const;
        glm::vec3 getBaseScale(int num) const;
        int getDoorType(int num) const;


        unsigned int getWallCount(void) const;
        unsigned int getZombieCount(void) const;
        unsigned int getDoorCount(void) const;
        unsigned int getAmmoCount(void) const;


    private:
        std::string string_;
        Json::Value root;

        glm::vec3 door1_pos;
        glm::vec3 door1_scale;
        glm::vec3 door2_pos;
        glm::vec3 door2_scale;
        glm::vec3 door3_pos;
        glm::vec3 door3_scale;
        glm::vec3 door4_pos;
        glm::vec3 door4_scale;
        glm::vec3 door5_pos;
        glm::vec3 door5_scale;
        glm::vec3 door6_pos;
        glm::vec3 door6_scale;
        glm::vec3 door7_pos;
        glm::vec3 door7_scale;
        glm::vec3 door8_pos;
        glm::vec3 door8_scale;

        glm::vec3 hint1_pos;
        glm::vec3 hint2_pos;
        glm::vec3 hint3_pos;
        glm::vec3 hint4_pos;

        unsigned player_ammo;
        unsigned player_Health;
        unsigned pistol_damage;
        unsigned player_armor;

        glm::vec3 player_pos;
        glm::vec3 zombie1_pos;
        glm::vec3 zombie2_pos;
        glm::vec3 zombie3_pos;
        // Horizontal wall 1~4
        glm::vec3 wall1_pos;
        glm::vec3 wall2_pos;
        glm::vec3 wall3_pos;
        glm::vec3 wall4_pos;

        // Vertical wall 5~8
        glm::vec3 wall5_pos;
        glm::vec3 wall6_pos;
        glm::vec3 wall7_pos;
        glm::vec3 wall8_pos;

        glm::vec3 cross_wall_pos;
        glm::vec3 cross_wall_scale;

        glm::vec3 horizontal_wall_scale;
        glm::vec3 vertical_wall_scale;

        glm::vec3 pistol_pos;
        glm::vec3 ammo1_pos;
        glm::vec3 ammo2_pos;
        glm::vec3 ammo3_pos;
        glm::vec3 armor1_pos;
        glm::vec3 armor2_pos;

        glm::vec3 base1_pos;
        glm::vec3 base1_scale;
        glm::vec3 base2_pos;
        glm::vec3 base2_scale;
        glm::vec3 base3_pos;
        glm::vec3 base3_scale;
        glm::vec3 base4_pos;
        glm::vec3 base4_scale;
        glm::vec3 base5_pos;
        glm::vec3 base5_scale;
        glm::vec3 base6_pos;
        glm::vec3 base6_scale;
        glm::vec3 base7_pos;
        glm::vec3 base7_scale;
        glm::vec3 base8_pos;
        glm::vec3 base8_scale;
        glm::vec3 base9_pos;
        glm::vec3 base9_scale;

        unsigned int wall_count;
        unsigned int zombie_count;
        unsigned int door_count;
        unsigned int ammo_count;

        std::vector<glm::vec3> wall_pos;
        std::vector<glm::vec3> wall_scale;
        std::vector<glm::vec3> door_pos;
        std::vector<glm::vec3> door_scale;
        std::vector<int> door_type_Is_Horizon;
        std::vector<glm::vec3> ammo_pos;
        std::vector<glm::vec3> ammo_scale;
        std::vector<glm::vec3> armor_pos;
        std::vector<glm::vec3> armor_scale;
        std::vector<glm::vec3> zombie_pos;
        std::vector<glm::vec3> zombie_scale;
        std::vector<glm::vec3> base_pos;
        std::vector<glm::vec3> base_scale;
    };
    extern jsonReader* JSONREADER;
}
#endif /* jsonReader_h */
