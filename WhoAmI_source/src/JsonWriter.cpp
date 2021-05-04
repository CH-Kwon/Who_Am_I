/**
\file        jsonWriter.cpp
\author      SeongHyun Hong
\par         email: tjdgus3174@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "JsonWriter.h"
#include <stdlib.h>

namespace FindersEngine
{

    jsonWriter* JSONWRITER = new jsonWriter;

    jsonWriter::jsonWriter()
    {
        JSONWRITER = this;
    }
    jsonWriter::~jsonWriter()
    {
        delete JSONWRITER;
    }
    int jsonWriter::jsonWriterEdit(GameData& data)
    {
        m_Wall.resize(data.Wall_Count);
        m_Zombie.resize(data.Zombie_Count);
        m_Door.resize(data.Door_Count);
        m_Ammo.resize(data.Ammo_Count);


        m_player["positionX"] = data.Player->GetPosition().x;
        m_player["positionY"] = data.Player->GetPosition().y;
        m_player["positionZ"] = data.Player->GetPosition().z;
        m_player["Health"] = 200;
        m_player["Ammo"] = 0;

        m_Wall_Count["count"] = data.Wall_Count;
        m_Zombie_Count["count"] = data.Zombie_Count;
        m_Door_Count["count"] = data.Door_Count;
        m_Ammo_Count["count"] = data.Ammo_Count;

        m_root["Wall"]["WallCount"] = m_Wall_Count;
        m_root["zombie"]["zombieCount"] = m_Zombie_Count;
        m_root["Door"]["DoorCount"] = m_Door_Count;
        m_root["Ammo"]["AmmoCount"] = m_Ammo_Count;


        for (unsigned int i = 0; i < m_Wall.size(); ++i)
        {
            std::string num = std::to_string(i);
            std::string num_plus = std::to_string(i + 1);

            m_Wall[i]["positionX"] = data.Wall[i]->GetPosition().x;
            m_Wall[i]["positionY"] = data.Wall[i]->GetPosition().y;
            m_Wall[i]["positionZ"] = data.Wall[i]->GetPosition().z;
            m_Wall[i]["scaleX"] = data.Wall[i]->GetScale().x;
            m_Wall[i]["scaleY"] = data.Wall[i]->GetScale().y;
            m_Wall[i]["scaleZ"] = data.Wall[i]->GetScale().z;
            m_root["Wall"]["Wall" + num_plus] = m_Wall[i];
        }

        for (unsigned int i = 0; i < m_Zombie.size(); ++i)
        {
            std::string num = std::to_string(i);
            std::string num_plus = std::to_string(i + 1);

            m_Zombie[i]["positionX"] = data.Zombie[i]->GetPosition().x;
            m_Zombie[i]["positionY"] = data.Zombie[i]->GetPosition().y;
            m_Zombie[i]["positionZ"] = data.Zombie[i]->GetPosition().z;
            m_root["zombie"]["zombie" + num_plus] = m_Zombie[i];
        }

        for (unsigned int i = 0; i < m_Door.size(); ++i)
        {
            std::string num = std::to_string(i);
            std::string num_plus = std::to_string(i + 1);

            m_Door[i]["positionX"] = data.Door[i]->GetPosition().x;
            m_Door[i]["positionY"] = data.Door[i]->GetPosition().y;
            m_Door[i]["positionZ"] = data.Door[i]->GetPosition().z;
            m_Door[i]["scaleX"] = data.Door[i]->GetScale().x;
            m_Door[i]["scaleY"] = data.Door[i]->GetScale().y;
            m_Door[i]["scaleZ"] = data.Door[i]->GetScale().z;
            m_Door[i]["Type"] = data.Door[i]->GetObjType();
            m_root["Door"]["Door" + num_plus] = m_Door[i];
        }
        for (unsigned int i = 0; i < m_Ammo.size(); ++i)
        {
            std::string num = std::to_string(i);
            std::string num_plus = std::to_string(i + 1);

            m_Ammo[i]["positionX"] = data.Ammo[i]->GetPosition().x;
            m_Ammo[i]["positionY"] = data.Ammo[i]->GetPosition().y;
            m_Ammo[i]["positionZ"] = data.Ammo[i]->GetPosition().z;
            m_Ammo[i]["scaleX"] = data.Ammo[i]->GetScale().x;
            m_Ammo[i]["scaleY"] = data.Ammo[i]->GetScale().y;
            m_Ammo[i]["scaleZ"] = data.Ammo[i]->GetScale().z;
            m_root["Ammo"]["Ammo" + num_plus] = m_Ammo[i];
        }
        m_pistol["positionX"] = data.Pistol->GetPosition().x;
        m_pistol["positionY"] = data.Pistol->GetPosition().y;
        m_pistol["positionZ"] = data.Pistol->GetPosition().z;
        m_root["Pistol"] = m_pistol;

        m_player["currAmmo"] = data.Player->curr_ammo;

        m_root["Player"] = m_player;

        if (data.Currentlevel == EDLevel1)
            write("jsonFile/EDlevel1.json", m_root);
        else
            write("jsonFile/test2.json", m_root);
        return 0;
    }
    void jsonWriter::write(const std::string& file, const Json::Value& root)
    {
        std::ofstream file_data_;
        file_data_.open(file, std::ios_base::out);

        if (file_data_.is_open())
        {
            file_data_ << root;
            file_data_.close();
        }
    }
    void jsonWriter::addValue(Json::Value& buffer_, const Json::Value* value_)
    {
        buffer_ = value_;
    }

    void jsonWriter::setPlayerData(Transform* player)
    {
        m_player["currAmmo"] = player->GetOwner()->curr_ammo;
        m_player["isPistol"] = player->GetOwner()->is_get_pistol;
        m_player["currArmor"] = player->GetOwner()->curr_Armor;

        m_root["player"] = m_player;
    }

    int jsonWriter::jsonWriterMain()
    {
        write("jsonFile/Level1_save.json", m_root);

        return 0;
    }
}
