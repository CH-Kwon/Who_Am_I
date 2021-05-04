/**
\file        jsonWriter.h
\author      SeongHyun Hong
\par         email: tjdgus3174@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once

#ifndef jsonWriter_h
#define jsonWriter_h

#include "EditHelper.h"
#include "Object.h"
#include "System.h"
#include "Transform.hpp"
#include "glm/glm.hpp"
#include "json.h"
#include "writer.h"
#include <cstdlib>
#include <fstream>
#include <iostream>

namespace FindersEngine
{
    class jsonWriter
    {
    public:
        jsonWriter();
        ~jsonWriter();

        void write(const std::string& file, const Json::Value& root);

        int jsonWriterMain();

        int jsonWriterEdit(GameData& data);

        void setPlayerData(Transform* player);
        void setPistolPos(glm::vec3);
        void setAmmo1Pos(glm::vec3);
        void setAmmo2Pos(glm::vec3);
        void addValue(Json::Value& buffer_, const Json::Value* value_);

        void set_data(void);

    private:
        Json::Value m_root;
        Json::Value m_player;
        Json::Value m_pistol;

        Json::Value m_Item;

        std::vector<Json::Value> m_Wall;
        std::vector<Json::Value> m_Zombie;
        std::vector<Json::Value> m_Door;
        std::vector<Json::Value> m_Ammo;
        std::vector<Json::Value> m_pistol_pos;
        std::vector<Json::Value> m_ammo1_pos;
        std::vector<Json::Value> m_ammo2_pos;

        Json::Value m_Wall_Count;
        Json::Value m_Zombie_Count;
        Json::Value m_Door_Count;
        Json::Value m_Ammo_Count;
    };
    extern jsonWriter* JSONWRITER;
}
#endif /* jsonWriter_h */
