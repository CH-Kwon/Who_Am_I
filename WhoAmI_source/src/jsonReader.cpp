/**
\file        jsonReader.cpp
\author      SeongHyun Hong
\par         email: tjdgus3174@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "jsonReader.h"
#include <stdlib.h>


namespace FindersEngine
{
    const int kReadBufferSize = 65536;
    jsonReader* JSONREADER = new jsonReader;

    jsonReader::jsonReader()
    {
        JSONREADER = this;
    }
    jsonReader::~jsonReader()
    {
        delete JSONREADER;
    }

    bool jsonReader::read(std::string const& filepath_, Json::Value& data_)
    {
        std::ifstream fileData;
        fileData.open(filepath_, std::ifstream::in);
        if (fileData.is_open())
        {
            fileData >> data_;
            fileData.close();
        }
        return true;
    }
    int jsonReader::ReadJsonEdit()
    {
        read("jsonFile/test2.json", root);
        get_edit_data();
        return 0;
    }
    int jsonReader::ReadJsonLevel1()
    {
        read("jsonFile/EDlevel1.json", root);
        get_edit_data();
        return 0;
    }
    void jsonReader::get_edit_data()
    {
        player_pos.x = root["Player"].get("positionX", 0).asFloat();
        player_pos.y = root["Player"].get("positionY", 0).asFloat();
        player_pos.z = root["Player"].get("positionZ", 0).asFloat();
        player_Health = root["player"].get("Health", 0).asUInt();
        player_ammo = root["player"].get("Ammo", 0).asUInt();

        wall_count = root["Wall"]["WallCount"].get("count", 0).asInt();
        zombie_count = root["zombie"]["zombieCount"].get("count", 0).asInt();
        door_count = root["Door"]["DoorCount"].get("count", 0).asInt();
        ammo_count = root["Ammo"]["AmmoCount"].get("count", 0).asInt();

        //wall
        for (unsigned int i = 1; i <= wall_count; ++i)
        {
            std::string num = std::to_string(i);
            wall_pos.push_back(glm::vec3(root["Wall"]["Wall" + num].get("positionX", 0).asFloat(),
                                         root["Wall"]["Wall" + num].get("positionY", 0).asFloat(),
                                         root["Wall"]["Wall" + num].get("positionZ", 0).asFloat()));
            wall_scale.push_back(glm::vec3(root["Wall"]["Wall" + num].get("scaleX", 0).asFloat(),
                                           root["Wall"]["Wall" + num].get("scaleY", 0).asFloat(),
                                           root["Wall"]["Wall" + num].get("scaleZ", 0).asFloat()));
        }

        //zombie
        for (unsigned int i = 1; i <= zombie_count; ++i)
        {
            std::string num = std::to_string(i);
            zombie_pos.push_back(glm::vec3(root["zombie"]["zombie" + num].get("positionX", 0).asFloat(),
                                           root["zombie"]["zombie" + num].get("positionY", 0).asFloat(),
                                           root["zombie"]["zombie" + num].get("positionZ", 0).asFloat()));
        }

        //door
        for (unsigned int i = 1; i <= door_count; ++i)
        {
            std::string num = std::to_string(i);
            door_pos.push_back(glm::vec3(root["Door"]["Door" + num].get("positionX", 0).asFloat(),
                                         root["Door"]["Door" + num].get("positionY", 0).asFloat(),
                                         root["Door"]["Door" + num].get("positionZ", 0).asFloat()));
            door_scale.push_back(glm::vec3(root["Door"]["Door" + num].get("scaleX", 0).asFloat(),
                                           root["Door"]["Door" + num].get("scaleY", 0).asFloat(),
                                           root["Door"]["Door" + num].get("scaleZ", 0).asFloat()));
            door_type_Is_Horizon.push_back(root["Door"]["Door" + num].get("Type", 0).asInt());
        }

        //ammo
        for (unsigned int i = 1; i <= ammo_count; ++i)
        {
            std::string num = std::to_string(i);
            ammo_pos.push_back(glm::vec3(root["Ammo"]["Ammo" + num].get("positionX", 0).asFloat(),
                                         root["Ammo"]["Ammo" + num].get("positionY", 0).asFloat(),
                                         root["Ammo"]["Ammo" + num].get("positionZ", 0).asFloat()));
            ammo_scale.push_back(glm::vec3(root["Ammo"]["Ammo" + num].get("scaleX", 0).asFloat(),
                                           root["Ammo"]["Ammo" + num].get("scaleY", 0).asFloat(),
                                           root["Ammo"]["Ammo" + num].get("scaleZ", 0).asFloat()));
        }

        pistol_pos = (glm::vec3(root["Pistol"].get("positionX", 1).asFloat(),
                                root["Pistol"].get("positionY", 1).asFloat(),
                                root["Pistol"].get("positionZ", 0).asFloat()));
    }
    glm::vec3 jsonReader::getWallPos(int num) const
    {
        return wall_pos[num];
    }
    glm::vec3 jsonReader::getDoorPos(int num) const
    {
        return door_pos[num];
    }
    glm::vec3 jsonReader::getAmmoPos(int num) const
    {
        return ammo_pos[num];
    }
    glm::vec3 jsonReader::getArmorPos(int num) const
    {
        return armor_pos[num];
    }
    glm::vec3 jsonReader::getZombiePos(int num) const
    {
        return zombie_pos[num];
    }
    glm::vec3 jsonReader::getBasePos(int num) const
    {
        return base_pos[num];
    }
    glm::vec3 jsonReader::getWallScale(int num) const
    {
        return wall_scale[num];
    }
    glm::vec3 jsonReader::getDoorScale(int num) const
    {
        return door_scale[num];
    }
    glm::vec3 jsonReader::getAmmoScale(int num) const
    {
        return ammo_scale[num];
    }
    glm::vec3 jsonReader::getArmorScale(int num) const
    {
        return armor_scale[num];
    }
    glm::vec3 jsonReader::getZombieScale(int num) const
    {
        return zombie_scale[num];
    }
    glm::vec3 jsonReader::getBaseScale(int num) const
    {
        return base_scale[num];
    }

    unsigned int jsonReader::getWallCount(void) const
    {
        return wall_count;
    }
    unsigned int jsonReader::getZombieCount(void) const
    {
        return zombie_count;
    }
    unsigned int jsonReader::getDoorCount(void) const
    {
        return door_count;
    }
    unsigned int jsonReader::getAmmoCount(void) const
    {
        return ammo_count;
    }

    int jsonReader::getDoorType(int num) const
    {
        return door_type_Is_Horizon[num];
    }
    void jsonReader::get_saved_data()
    {
        player_Health = root["player"].get("Health", 0).asUInt();
        player_ammo = root["player"].get("currAmmo", 0).asUInt();
        player_armor = root["player"].get("currArmor", 0).asUInt();
    }
    unsigned jsonReader::getPlayerArmor() const
    {
        return player_armor;
    }

    void jsonReader::savedJsonReader()
    {
        read("jsonFile/Level1_save.json", root);
        get_saved_data();
    }
    unsigned jsonReader::getPlayerAmmo() const
    {
        return player_ammo;
    }
    int jsonReader::jsonReaderMain()
    {
        read("jsonFile/Level1.json", root);
        get_data();

        return 0;
    }

    void jsonReader::get_data()
    {
        hint1_pos.x = root["Hint"]["num7"].get("positionX", 0).asFloat();
        hint1_pos.y = root["Hint"]["num7"].get("positionY", 0).asFloat();
        hint1_pos.z = root["Hint"]["num7"].get("positionZ", 0).asFloat();

        hint2_pos.x = root["Hint"]["num2"].get("positionX", 0).asFloat();
        hint2_pos.y = root["Hint"]["num2"].get("positionY", 0).asFloat();
        hint2_pos.z = root["Hint"]["num2"].get("positionZ", 0).asFloat();

        hint3_pos.x = root["Hint"]["num2_2"].get("positionX", 0).asFloat();
        hint3_pos.y = root["Hint"]["num2_2"].get("positionY", 0).asFloat();
        hint3_pos.z = root["Hint"]["num2_2"].get("positionZ", 0).asFloat();

        hint4_pos.x = root["Hint"]["num3"].get("positionX", 0).asFloat();
        hint4_pos.y = root["Hint"]["num3"].get("positionY", 0).asFloat();
        hint4_pos.z = root["Hint"]["num3"].get("positionZ", 0).asFloat();

        pistol_pos.x = root["Pistol"].get("positionX", 0).asFloat();
        pistol_pos.y = root["Pistol"].get("positionY", 0).asFloat();
        pistol_pos.z = root["Pistol"].get("positionZ", 0).asFloat();
        pistol_damage = root["Pistol"].get("damage", 0).asUInt();

        zombie1_pos.x = root["zombie"]["zombie1"].get("positionX", 0).asFloat();
        zombie1_pos.y = root["zombie"]["zombie1"].get("positionY", 0).asFloat();
        zombie1_pos.z = root["zombie"]["zombie1"].get("positionZ", 0).asFloat();

        zombie2_pos.x = root["zombie"]["zombie2"].get("positionX", 0).asFloat();
        zombie2_pos.y = root["zombie"]["zombie2"].get("positionY", 0).asFloat();
        zombie2_pos.z = root["zombie"]["zombie2"].get("positionZ", 0).asFloat();

        zombie3_pos.x = root["zombie"]["zombie3"].get("positionX", 0).asFloat();
        zombie3_pos.y = root["zombie"]["zombie3"].get("positionY", 0).asFloat();
        zombie3_pos.z = root["zombie"]["zombie3"].get("positionZ", 0).asFloat();

        ammo1_pos.x = root["Ammo"]["Ammo1"].get("positionX", 0).asFloat();
        ammo1_pos.y = root["Ammo"]["Ammo1"].get("positionY", 0).asFloat();
        ammo1_pos.z = root["Ammo"]["Ammo1"].get("positionZ", 0).asFloat();

        ammo2_pos.x = root["Ammo"]["Ammo2"].get("positionX", 0).asFloat();
        ammo2_pos.y = root["Ammo"]["Ammo2"].get("positionY", 0).asFloat();
        ammo2_pos.z = root["Ammo"]["Ammo2"].get("positionZ", 0).asFloat();

        ammo3_pos.x = root["Ammo"]["Ammo3"].get("positionX", 0).asFloat();
        ammo3_pos.y = root["Ammo"]["Ammo3"].get("positionY", 0).asFloat();
        ammo3_pos.z = root["Ammo"]["Ammo3"].get("positionZ", 0).asFloat();

        armor1_pos.x = root["Armor"]["Armor1"].get("positionX", 0).asFloat();
        armor1_pos.y = root["Armor"]["Armor1"].get("positionY", 0).asFloat();
        armor1_pos.z = root["Armor"]["Armor1"].get("positionZ", 0).asFloat();

        armor2_pos.x = root["Armor"]["Armor2"].get("positionX", 0).asFloat();
        armor2_pos.y = root["Armor"]["Armor2"].get("positionY", 0).asFloat();
        armor2_pos.z = root["Armor"]["Armor2"].get("positionZ", 0).asFloat();

        player_pos.x = root["player"].get("positionX", 0).asFloat();
        player_pos.y = root["player"].get("positionY", 0).asFloat();
        player_pos.z = root["player"].get("positionZ", 0).asFloat();


        wall1_pos.x = root["Wall"]["Wall1"].get("positionX", 0).asFloat();
        wall1_pos.y = root["Wall"]["Wall1"].get("positionY", 0).asFloat();
        wall1_pos.z = root["Wall"]["Wall1"].get("positionZ", 0).asFloat();

        wall2_pos.x = root["Wall"]["Wall2"].get("positionX", 0).asFloat();
        wall2_pos.y = root["Wall"]["Wall2"].get("positionY", 0).asFloat();
        wall2_pos.z = root["Wall"]["Wall2"].get("positionZ", 0).asFloat();

        wall3_pos.x = root["Wall"]["Wall3"].get("positionX", 0).asFloat();
        wall3_pos.y = root["Wall"]["Wall3"].get("positionY", 0).asFloat();
        wall3_pos.z = root["Wall"]["Wall3"].get("positionZ", 0).asFloat();

        wall4_pos.x = root["Wall"]["Wall4"].get("positionX", 0).asFloat();
        wall4_pos.y = root["Wall"]["Wall4"].get("positionY", 0).asFloat();
        wall4_pos.z = root["Wall"]["Wall4"].get("positionZ", 0).asFloat();

        wall5_pos.x = root["Wall"]["Wall5"].get("positionX", 0).asFloat();
        wall5_pos.y = root["Wall"]["Wall5"].get("positionY", 0).asFloat();
        wall5_pos.z = root["Wall"]["Wall5"].get("positionZ", 0).asFloat();

        wall6_pos.x = root["Wall"]["Wall6"].get("positionX", 0).asFloat();
        wall6_pos.y = root["Wall"]["Wall6"].get("positionY", 0).asFloat();
        wall6_pos.z = root["Wall"]["Wall6"].get("positionZ", 0).asFloat();

        wall7_pos.x = root["Wall"]["Wall7"].get("positionX", 0).asFloat();
        wall7_pos.y = root["Wall"]["Wall7"].get("positionY", 0).asFloat();
        wall7_pos.z = root["Wall"]["Wall7"].get("positionZ", 0).asFloat();

        wall8_pos.x = root["Wall"]["Wall8"].get("positionX", 0).asFloat();
        wall8_pos.y = root["Wall"]["Wall8"].get("positionY", 0).asFloat();
        wall8_pos.z = root["Wall"]["Wall8"].get("positionZ", 0).asFloat();

        cross_wall_pos.x = root["Wall"]["CrossWall1"].get("positionX", 0).asFloat();
        cross_wall_pos.y = root["Wall"]["CrossWall1"].get("positionY", 0).asFloat();
        cross_wall_pos.z = root["Wall"]["CrossWall1"].get("positionZ", 0).asFloat();

        cross_wall_scale.x = root["Wall"]["CrossWall1"].get("scaleX", 0).asFloat();
        cross_wall_scale.y = root["Wall"]["CrossWall1"].get("scaleY", 0).asFloat();
        cross_wall_scale.z = root["Wall"]["CrossWall1"].get("scaleZ", 0).asFloat();

        horizontal_wall_scale.x = root["Wall"]["Wall1"].get("scaleX", 0).asFloat();
        horizontal_wall_scale.y = root["Wall"]["Wall1"].get("scaleY", 0).asFloat();
        horizontal_wall_scale.z = root["Wall"]["Wall1"].get("scaleZ", 0).asFloat();

        vertical_wall_scale.x = root["Wall"]["Wall5"].get("scaleX", 0).asFloat();
        vertical_wall_scale.y = root["Wall"]["Wall5"].get("scaleY", 0).asFloat();
        vertical_wall_scale.z = root["Wall"]["Wall5"].get("scaleZ", 0).asFloat();

        base1_pos.x = root["BaseTile"]["BaseTile1"].get("positionX", 0).asFloat();
        base1_pos.y = root["BaseTile"]["BaseTile1"].get("positionY", 0).asFloat();
        base1_pos.z = root["BaseTile"]["BaseTile1"].get("positionZ", 0).asFloat();
        base1_scale.x = root["BaseTile"]["BaseTile1"].get("scaleX", 0).asFloat();
        base1_scale.y = root["BaseTile"]["BaseTile1"].get("scaleY", 0).asFloat();
        base1_scale.z = root["BaseTile"]["BaseTile1"].get("scaleX", 0).asFloat();

        door1_pos.x = root["Door"]["Door1"].get("positionX", 0).asFloat();
        door1_pos.y = root["Door"]["Door1"].get("positionY", 0).asFloat();
        door1_pos.z = root["Door"]["Door1"].get("positionZ", 0).asFloat();

        door1_scale.x = root["Door"]["Door1"].get("scaleX", 0).asFloat();
        door1_scale.y = root["Door"]["Door1"].get("scaleY", 0).asFloat();
        door1_scale.z = root["Door"]["Door1"].get("scaleZ", 0).asFloat();

        door2_pos.x = root["Door"]["Door2"].get("positionX", 0).asFloat();
        door2_pos.y = root["Door"]["Door2"].get("positionY", 0).asFloat();
        door2_pos.z = root["Door"]["Door2"].get("positionZ", 0).asFloat();

        door2_scale.x = root["Door"]["Door2"].get("scaleX", 0).asFloat();
        door2_scale.y = root["Door"]["Door2"].get("scaleY", 0).asFloat();
        door2_scale.z = root["Door"]["Door2"].get("scaleZ", 0).asFloat();

        door3_pos.x = root["Door"]["Door3"].get("positionX", 0).asFloat();
        door3_pos.y = root["Door"]["Door3"].get("positionY", 0).asFloat();
        door3_pos.z = root["Door"]["Door3"].get("positionZ", 0).asFloat();

        door3_scale.x = root["Door"]["Door3"].get("scaleX", 0).asFloat();
        door3_scale.y = root["Door"]["Door3"].get("scaleY", 0).asFloat();
        door3_scale.z = root["Door"]["Door3"].get("scaleZ", 0).asFloat();

        door4_pos.x = root["Door"]["Door4"].get("positionX", 0).asFloat();
        door4_pos.y = root["Door"]["Door4"].get("positionY", 0).asFloat();
        door4_pos.z = root["Door"]["Door4"].get("positionZ", 0).asFloat();

        door4_scale.x = root["Door"]["Door4"].get("scaleX", 0).asFloat();
        door4_scale.y = root["Door"]["Door4"].get("scaleY", 0).asFloat();
        door4_scale.z = root["Door"]["Door4"].get("scaleZ", 0).asFloat();

        door5_pos.x = root["Door"]["Door5"].get("positionX", 0).asFloat();
        door5_pos.y = root["Door"]["Door5"].get("positionY", 0).asFloat();
        door5_pos.z = root["Door"]["Door5"].get("positionZ", 0).asFloat();

        door5_scale.x = root["Door"]["Door5"].get("scaleX", 0).asFloat();
        door5_scale.y = root["Door"]["Door5"].get("scaleY", 0).asFloat();
        door5_scale.z = root["Door"]["Door5"].get("scaleZ", 0).asFloat();

        door6_pos.x = root["Door"]["Door6"].get("positionX", 0).asFloat();
        door6_pos.y = root["Door"]["Door6"].get("positionY", 0).asFloat();
        door6_pos.z = root["Door"]["Door6"].get("positionZ", 0).asFloat();

        door6_scale.x = root["Door"]["Door6"].get("scaleX", 0).asFloat();
        door6_scale.y = root["Door"]["Door6"].get("scaleY", 0).asFloat();
        door6_scale.z = root["Door"]["Door6"].get("scaleZ", 0).asFloat();

        door7_pos.x = root["Door"]["Door7"].get("positionX", 0).asFloat();
        door7_pos.y = root["Door"]["Door7"].get("positionY", 0).asFloat();
        door7_pos.z = root["Door"]["Door7"].get("positionZ", 0).asFloat();

        door7_scale.x = root["Door"]["Door7"].get("scaleX", 0).asFloat();
        door7_scale.y = root["Door"]["Door7"].get("scaleY", 0).asFloat();
        door7_scale.z = root["Door"]["Door7"].get("scaleZ", 0).asFloat();

        door8_pos.x = root["Door"]["Door8"].get("positionX", 0).asFloat();
        door8_pos.y = root["Door"]["Door8"].get("positionY", 0).asFloat();
        door8_pos.z = root["Door"]["Door8"].get("positionZ", 0).asFloat();

        door8_scale.x = root["Door"]["Door8"].get("scaleX", 0).asFloat();
        door8_scale.y = root["Door"]["Door8"].get("scaleY", 0).asFloat();
        door8_scale.z = root["Door"]["Door8"].get("scaleZ", 0).asFloat();
    }

    glm::vec3 jsonReader::getDoor8Pos() const
    {
        return door8_pos;
    }
    glm::vec3 jsonReader::getDoor8Scale() const
    {
        return door8_scale;
    }

    glm::vec3 jsonReader::getHint1Pos() const
    {
        return hint1_pos;
    }
    glm::vec3 jsonReader::getHint2Pos() const
    {
        return hint2_pos;
    }
    glm::vec3 jsonReader::getHint3Pos() const
    {
        return hint3_pos;
    }
    glm::vec3 jsonReader::getHint4Pos() const
    {
        return hint4_pos;
    }

    glm::vec3 jsonReader::getDoor1Pos() const
    {
        return door1_pos;
    }
    glm::vec3 jsonReader::getDoor1Scale() const
    {
        return door1_scale;
    }
    glm::vec3 jsonReader::getDoor2Pos() const
    {
        return door2_pos;
    }

    glm::vec3 jsonReader::getDoor2Scale() const
    {
        return door2_scale;
    }
    glm::vec3 jsonReader::getDoor3Pos() const
    {
        return door3_pos;
    }

    glm::vec3 jsonReader::getDoor3Scale() const
    {
        return door3_scale;
    }
    glm::vec3 jsonReader::getDoor4Pos() const
    {
        return door4_pos;
    }

    glm::vec3 jsonReader::getDoor4Scale() const
    {
        return door4_scale;
    }
    glm::vec3 jsonReader::getDoor5Pos() const
    {
        return door5_pos;
    }

    glm::vec3 jsonReader::getDoor5Scale() const
    {
        return door5_scale;
    }
    glm::vec3 jsonReader::getDoor6Pos() const
    {
        return door6_pos;
    }

    glm::vec3 jsonReader::getDoor6Scale() const
    {
        return door6_scale;
    }
    glm::vec3 jsonReader::getDoor7Pos() const
    {
        return door7_pos;
    }

    glm::vec3 jsonReader::getDoor7Scale() const
    {
        return door7_scale;
    }
    glm::vec3 jsonReader::getZombie1Pos() const
    {
        return zombie1_pos;
    }
    glm::vec3 jsonReader::getZombie2Pos() const
    {
        return zombie2_pos;
    }
    glm::vec3 jsonReader::getZombie3Pos() const
    {
        return zombie3_pos;
    }

    glm::vec3 jsonReader::getArmor1Pos() const
    {
        return armor1_pos;
    }
    glm::vec3 jsonReader::getArmor2Pos() const
    {
        return armor2_pos;
    }

    unsigned jsonReader::getPlayerHealth() const
    {
        return player_Health;
    }

    unsigned jsonReader::getPistolDamage() const
    {
        return pistol_damage;
    }

    glm::vec3 jsonReader::getPistolPos() const
    {
        return pistol_pos;
    }

    glm::vec3 jsonReader::getAmmo1Pos() const
    {
        return ammo1_pos;
    }
    glm::vec3 jsonReader::getAmmo2Pos() const
    {
        return ammo2_pos;
    }

    glm::vec3 jsonReader::getAmmo3Pos() const
    {
        return ammo3_pos;
    }

    glm::vec3 jsonReader::getPlayerPos() const
    {
        return player_pos;
    }
    glm::vec3 jsonReader::getWall1Pos() const
    {
        return wall1_pos;
    }
    glm::vec3 jsonReader::getWall2Pos() const
    {
        return wall2_pos;
    }
    glm::vec3 jsonReader::getWall3Pos() const
    {
        return wall3_pos;
    }
    glm::vec3 jsonReader::getWall4Pos() const
    {
        return wall4_pos;
    }
    glm::vec3 jsonReader::getWall5Pos() const
    {
        return wall5_pos;
    }
    glm::vec3 jsonReader::getWall6Pos() const
    {
        return wall6_pos;
    }
    glm::vec3 jsonReader::getWall7Pos() const
    {
        return wall7_pos;
    }
    glm::vec3 jsonReader::getWall8Pos() const
    {
        return wall8_pos;
    }
    glm::vec3 jsonReader::getHorizontalWallScale() const
    {
        return horizontal_wall_scale;
    }
    glm::vec3 jsonReader::getVerticalWallScale() const
    {
        return vertical_wall_scale;
    }
    glm::vec3 jsonReader::getCrossWallPos() const
    {
        return cross_wall_pos;
    }
    glm::vec3 jsonReader::getCrossWallScale() const
    {
        return cross_wall_scale;
    }

    glm::vec3 jsonReader::getBase1Pos() const
    {
        return base1_pos;
    }
    glm::vec3 jsonReader::getBase1Scale() const
    {
        return base1_scale;
    }
    glm::vec3 jsonReader::getBase2Pos() const
    {
        return base2_pos;
    }
    glm::vec3 jsonReader::getBase2Scale() const
    {
        return base2_scale;
    }
    glm::vec3 jsonReader::getBase3Pos() const
    {
        return base3_pos;
    }
    glm::vec3 jsonReader::getBase3Scale() const
    {
        return base3_scale;
    }
    glm::vec3 jsonReader::getBase4Pos() const
    {
        return base4_pos;
    }
    glm::vec3 jsonReader::getBase4Scale() const
    {
        return base4_scale;
    }
    glm::vec3 jsonReader::getBase5Pos() const
    {
        return base5_pos;
    }
    glm::vec3 jsonReader::getBase5Scale() const
    {
        return base5_scale;
    }
    glm::vec3 jsonReader::getBase6Pos() const
    {
        return base6_pos;
    }
    glm::vec3 jsonReader::getBase6Scale() const
    {
        return base6_scale;
    }
    glm::vec3 jsonReader::getBase7Pos() const
    {
        return base7_pos;
    }
    glm::vec3 jsonReader::getBase7Scale() const
    {
        return base7_scale;
    }
    glm::vec3 jsonReader::getBase8Pos() const
    {
        return base8_pos;
    }
    glm::vec3 jsonReader::getBase8Scale() const
    {
        return base8_scale;
    }
    glm::vec3 jsonReader::getBase9Pos() const
    {
        return base9_pos;
    }
    glm::vec3 jsonReader::getBase9Scale() const
    {
        return base9_scale;
    }
}
