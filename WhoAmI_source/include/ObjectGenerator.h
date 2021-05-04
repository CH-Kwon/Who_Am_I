/**
\file        ObjectGenerator.h
\author      SeongHyun Hong
\par         email: tjdgus3174@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once

#ifndef OBJECT_GENERATOR_H_
#define OBJECT_GENERATOR_H_

#include "Object.h"
#include "glm/glm.hpp"
#include "Hud.h"
#include <string>

namespace FindersEngine
{
    class ObjectGenerator
    {
    public:
        ObjectGenerator();
        ~ObjectGenerator();

        Object* CreateObject(const std::string& image_name, const glm::vec3& pos, const glm::vec3& scale, ObjectType, ShapeType, unsigned id);
        Object* CreateHint(const std::string& image_name, const glm::vec3& pos, const glm::vec3& scale, ObjectType ot, ShapeType st, unsigned id);
        Object* CreateSprite(const std::string& image_name, const glm::vec3& pos, const glm::vec3& scale, unsigned id);
        Object* CreateWall(const glm::vec3& pos, const glm::vec3& scale, unsigned id);
        Object* CreatePlayer(const glm::vec3& pos, unsigned id);
        Object* CreateBullet(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& bullet_size, unsigned id);
        Object* CreateZombie(const glm::vec3& pos, unsigned id);
        Object* CreateBase(const glm::vec3& pos, const glm::vec3& scale, unsigned id);
        Object* CreateSpeechBox(const glm::vec3& position, const glm::vec3& scale, unsigned id, const std::string& image_name, float lifeTime = 3.0f);
        Object* CreateCollisionHud(const glm::vec3& position, const glm::vec3& scale, unsigned id, const std::string& image_name);
        Object* CreateHud(const glm::vec3& position, const glm::vec3& scale, unsigned id, const std::string& image_name, Layer_Order lo = LO_BASE);
        Object* CreateEye(const glm::vec3& position, const glm::vec3& scale, unsigned id, const std::string& image_name);
        Object* CreateButton(const glm::vec3& position, const glm::vec3& scale, unsigned id, const std::string& image_name, std::string str, Layer_Order lo = LO_BASE);
        // Remind: position offset is Bottom-Left
        Object* CreateAFont(const glm::vec3& pos_offset_bottom_left, float scale, std::string text, const glm::vec3& color, unsigned id, float rotation);
        Object* CreatePausebox(const glm::vec3& position, const glm::vec3& scale, unsigned id, const std::string& image_name);
        Object* CreateTextbox(const glm::vec3& position, const glm::vec3& scale, unsigned id, const std::string& image_name);
        Object* CreateKeyinfo(const glm::vec3& position, const glm::vec3& scale, unsigned id, const std::string& image_name, Layer_Order lo = LO_BASE);
        Object* CreateKeyboardMouse(const glm::vec3& position, const glm::vec3& scale, unsigned id, const std::string& image_name, Layer_Order lo = LO_BASE);

    private:
    };
    extern ObjectGenerator* OBJECT_GEN;
}

#endif
